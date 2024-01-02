/*
 * ubrowse.c: Display the Unicode character set in a table.
 *
 * Copyright (C) 2013-2022 Brian Raiter <breadbox@muppetlabs.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include <wchar.h>
#include <locale.h>
#include <getopt.h>
#include <unistd.h>
#include <ncurses.h>
#include "data.h"

/* The value of the highest possible Unicode codepoint.
 */
static unsigned int const lastucharval = 0x0010FFFF;

/* Online help for program invocation.
 */
static char const *yowzitch[] = {
    "Usage: ubrowse [OPTIONS] [CHAR | CODEPOINT | STRING]",
    "Display Unicode characters in a scrolling table.",
    "",
    "  -a, --accent=CH   Specify codepoint CH to use when rendering combining",
    "                    accent characters (default is U+00B7).",
    "  -A, --noaccent    Suppress display of combining accent characters.",
    "  -i, --input       Display names of codepoints from standard input",
    "                    (default when output is not a terminal).",
    "      --help        Display this online help.",
    "      --version     Display version information.",
    "",
    "CHAR is a literal character with which to initialize the list position.",
    "CODEPOINT is specified as a hex value, optionally prefixed with \"U+\".",
    "STRING is a substring to search for in the codepoint names.",
    "",
    "Use \"?\" while the program is running to see a list of key commands.",
};

/* Version information.
 */
static char const *vourzhon[] = {
    "ubrowse: Unicode character set browser, version 1.8",
    "Copyright (C) 2013-2022 by Brian Raiter <breadbox@muppetlabs.com>",
    "This is free software; you are free to change and redistribute it.",
    "There is NO WARRANTY, to the extent permitted by law."
};

/* Array marking the blocks in the block list that are devoid of
 * printable characters. Created by emptyblocksinit().
 */
static unsigned char *emptyblocks;

/* The current number of columns in the table.
 */
static int columncount = 2;

/* A vaguely comfortable default column width that the program will
 * use as a minimum.
 */
static int const mindefaultcolumnwidth = 32;

/* An absolute minimum columns width that the user cannot go below.
 */
static int const mincolumnwidth = 8;

/* The size of the terminal (and thus the size of the table).
 */
static int xtermsize, ytermsize, lastrow;

/* Combining characters are displayed by combining them with this
 * character (by default the middle-dot, to make the placement clear).
 */
static wchar_t accentchar = 0x00B7;

/* If false, combining characters are not displayed.
 */
static int showcombining = TRUE;

/* If true, then instead of enabling curses, characters from stdin are
 * echoed to stdout along with their Unicode names.
 */
static int readstdin = FALSE;

/* If false, the user has explicitly selected the number of columns,
 * and the program should not modify it carelessly.
 */
static int resetcolumncount = TRUE;

/*
 * Lookup functions
 */

/* A variant of strstr() that doesn't depend on NUL terminators. (This
 * is basically an implementation of the nonstandard memmem()
 * function.)
 */
static char *strstrlen(char const *string, int size,
                       char const *substring, int subsize)
{
    char const *p;

    while ((p = memchr(string, *substring, size))) {
        size -= p - string;
        string = p;
        if (size < subsize)
            break;
        if (memcmp(string, substring, subsize) == 0)
            return (char*)string;
        ++string;
        --size;
    }
    return NULL;
}

/* Find the codepoint with the value uchar in the charlist array and
 * return its index. If uchar doesn't map to a defined codepoint,
 * return the nearest one.
 */
static int lookupchar(int uchar)
{
    int top, bottom, n;

    top = 0;
    bottom = charnames.listsize - 1;
    while (bottom - top > 1) {
        n = (top + bottom) / 2;
        if (charlist[n].uchar < uchar)
            top = n;
        else if (charlist[n].uchar > uchar)
            bottom = n;
        else
            return n;
    }
    return uchar - charlist[top].uchar < charlist[bottom].uchar - uchar ?
                top : bottom;
}

/* Return the index of the (nearest) codepoint that is charoffset away
 * from the current codepoint, as indicated by pos (or to the next
 * codepoint, if it is more than charoffset away).
 */
static int offsetchar(int pos, int charoffset)
{
    int newpos;

    newpos = lookupchar(charlist[pos].uchar + charoffset);
    if (newpos == pos && pos > 0 && pos < charnames.listsize - 1)
        newpos += charoffset < 0 ? -1 : +1;
    return newpos;
}

/* Return the index of the next name in the heap that contains the
 * given substring. The return value is negative if the substring
 * cannot be found. If substring is NULL, the previously saved search
 * string is reused.
 */
static int searchnameheap(char const *substring, int startpos, int direction,
                          namelist const *names)
{
    char const *p;
    int len, pos;

    if (!substring) {
        if (!*names->lastsearch)
            return -1;
        substring = names->lastsearch;
    }
    len = strlen(substring);

    pos = startpos;
    for (;;) {
        pos += direction;
        if (pos >= names->listsize)
            pos = 0;
        else if (pos < 0)
            pos = names->listsize - 1;
        p = names->heap + names->list[pos].offset;
        if (strstrlen(p, names->list[pos].size, substring, len)) {
            if (substring != names->lastsearch && len < maxsearchstringlen)
                strcpy(names->lastsearch, substring);
            return pos;
        }
        if (pos == startpos)
            return -1;
    }
}

/* Go through each block in the block list and mark the ones that
 * don't contain any valid or displayable codepoints.
 */
static void emptyblocksinit(void)
{
    int i, n;

    if (emptyblocks)
        return;
    emptyblocks = malloc(blocknames.listsize);
    for (i = 0 ; i < blocknames.listsize ; ++i) {
        n = lookupchar(blocklist[i].from);
        if (charlist[n].uchar >= blocklist[i].from &&
                        charlist[n].uchar <= blocklist[i].to)
            emptyblocks[i] = FALSE;
        else if (n + 1 < charnames.listsize &&
                        charlist[n + 1].uchar >= blocklist[i].from &&
                        charlist[n + 1].uchar <= blocklist[i].to)
            emptyblocks[i] = FALSE;
        else
            emptyblocks[i] = TRUE;
    }
}

/* Parse a string containing a hex value representing a Unicode
 * codepoint and return its index. -1 is returned if the string's
 * contents are not valid.
 */
static int readuchar(char const *input)
{
    unsigned long value;
    char *p;

    if (input[0] == 'U' && input[1] == '+')
        input += 2;
    value = strtoul(input, &p, 16);
    if (*p || p == input || (value == ULONG_MAX && errno == ERANGE))
        return -1;
    if (value > (unsigned long)lastucharval)
        return -1;
    return lookupchar((int)value);
}

/* If str points to a string containing a single codepoint (according
 * to the current locale), read the codepoint and return its index.
 * Otherwise the string contains either zero or at least two
 * codepoints, in which case -1 is returned.
 */
static int readsinglecharstring(char const *str)
{
    int ch = EOF;
    char junk;

    if (*str && sscanf(str, "%lc%c", &ch, &junk) != 2 && ch != EOF)
        return lookupchar(ch);
    return -1;
}

/*
 * Echo mode
 */

/* Instead of displaying a table, this function reads characters from
 * standard input and echoes them back to standard output, one per
 * line, with the codepoint's full name displayed alongside.
 */
static void showinputchars(void)
{
    char buf[16];
    wint_t wch;
    int width, n;

    for (;;) {
        wch = getwchar();
        if (wch == WEOF)
            return;
        n = lookupchar(wch);
        if (wch != charlist[n].uchar)
            continue;
        sprintf(buf, "U+%04X", wch);
        width = wcwidth(wch);
        if (width > 0)
            printf("%lc%*s", wch, 4 - width, "");
        else if (charlist[n].combining && showcombining)
            printf("%lc%lc   ", accentchar, wch);
        else
            printf("    ");
        printf("%-10s%.*s\n", buf, charnames.list[n].size,
                              charnames.heap + charnames.list[n].offset);
    }
}

/*
 * Curses-specific functions
 */

/* This callback ensures that ncurses shuts down cleanly at exit.
 */
static void shutdown(void)
{
    if (!isendwin())
        endwin();
}

/* Display an error message and exit the program.
 */
static void die(char const *fmt, ...)
{
    va_list     args;

    shutdown();
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
    va_end(args);
    exit(EXIT_FAILURE);
}

/* Alter the number of columns according to a user request.
 */
static void changecolumncount(int delta)
{
    columncount += delta;
    if (columncount < 1)
        columncount = 1;
    else if (columncount > (xtermsize - 1) / (mincolumnwidth + 1))
        columncount = (xtermsize - 1) / (mincolumnwidth + 1);
    resetcolumncount = FALSE;
}

/* Get the dimensions of the terminal. The bottommost row is not used
 * by the table. If the user hasn't explicitly set a column count,
 * then choose one based on the terminal's width.
 */
static void measurescreen(void)
{
    getmaxyx(stdscr, ytermsize, xtermsize);
    lastrow = ytermsize - 1;
    if (resetcolumncount) {
        columncount = xtermsize / mindefaultcolumnwidth;
        if (columncount < 1)
            columncount = 1;
    }
}

/* Initialize ncurses.
 */
static int ioinit(void)
{
    atexit(shutdown);
    if (!initscr())
        return FALSE;
    measurescreen();
    nonl();
    noecho();
    keypad(stdscr, TRUE);

    return TRUE;
}

/* Translate a key event from ncurses. Special keys that represent
 * controls are translated to appropriate ASCII equivalents. If the
 * terminal is resized, the function automatically updates the
 * variables defining the display area.
 */
static int translatekey(int key)
{
    if (key == KEY_RESIZE) {
        measurescreen();
        return '\f';
    }
    switch (key) {
      case KEY_LEFT:            return 'h';
      case KEY_DOWN:            return 'j';
      case KEY_UP:              return 'k';
      case KEY_RIGHT:           return 'l';
      case ' ':                 return 'f';
      case KEY_NPAGE:           return 'f';
      case KEY_PPAGE:           return 'b';
      case KEY_BACKSPACE:       return 'b';
      case '\b':                return 'b';
      case '\177':              return 'b';
      case KEY_ENTER:           return '\n';
      case '\r':                return '\n';
      case KEY_F(1):            return '?';
      case '\003':              return 'Q';
      case '\027':              return 'Q';
    }
    return tolower(key);
}

/* Wait for the user to press a key and return, or exit if ctrl-C is
 * pressed.
 */
static void anykey(void)
{
    mvaddstr(lastrow, 0, "[Press any key to continue]");
    clrtoeol();
    if (getch() == '\003')
        exit(EXIT_SUCCESS);
}

/* Display a string of text at the given position. If the text is too
 * long to fit on a single line, it is broken at a word boundary. (The
 * text is assumed to only use a single ASCII space between words.)
 * The return value is the y-value of the line immediately following
 * the end of the displayed text.
 */
static int drawtext(int y, int x, char const *text, int size)
{
    int n;

    while (size) {
        if (size <= xtermsize - x) {
            mvaddnstr(y++, x, text, size);
            break;
        }
        for (n = xtermsize - x ; n ; --n)
            if (text[n] == ' ')
                break;
        if (n == 0) {
            n = xtermsize - x;
            mvaddnstr(y++, x, text, n);
            text += n;
            size -= n;
        } else {
            mvaddnstr(y++, x, text, n);
            text += n + 1;
            size -= n + 1;
        }
    }
    return y;
}

/*
 * User interface functions
 */

/* Allow the user to input a string. The first parameter supplies the
 * input buffer that will receive the string. The second parameter
 * gives the buffer length. prompt provides a string that will appear
 * in front of the input. The last parameter provides a callback that
 * returns a true value to permit a character to be added to the input
 * string. The return value is the length of the user's input, or -1
 * if no input was retrieved.
 */
static int doinputui(char *input, int inputsize, char const *prompt,
                     int (*validchar)(int))
{
    int promptlen;
    int inputlen, inputmax;
    int done = FALSE;
    int ch;

    promptlen = strlen(prompt);
    mvaddstr(lastrow, 0, prompt);
    clrtoeol();
    inputlen = 0;
    inputmax = xtermsize - promptlen;
    if (inputmax > inputsize - 1)
        inputmax = inputsize - 1;
    while (!done) {
        ch = getch();
        if (ch == ERR)
            return -1;
        if (validchar(ch)) {
            if (inputlen < inputmax) {
                input[inputlen++] = ch;
                echochar(ch);
            } else {
                beep();
            }
        } else {
            if (ch == killchar())
                ch = '\025';
            switch (ch) {
              case KEY_ENTER:
              case '\r':
              case '\n':
                done = TRUE;
                break;
              case KEY_BACKSPACE:
              case '\010':
              case '\177':
                if (inputlen) {
                    --inputlen;
                    move(lastrow, promptlen + inputlen);
                    clrtoeol();
                } else {
                    beep();
                }
                break;
              case '\025':
                inputlen = 0;
                move(lastrow, promptlen);
                clrtoeol();
                break;
              case '\007':
                move(lastrow, 0);
                clrtoeol();
                return -1;
              case KEY_RESIZE:
                measurescreen();
                inputmax = xtermsize - promptlen;
                if (inputmax > inputsize - 1)
                    inputmax = inputsize - 1;
                if (inputlen >= inputmax)
                    inputlen = inputmax;
                mvaddstr(lastrow, 0, prompt);
                addnstr(input, inputlen);
                clrtoeol();
                break;
            }
        }
    }
    input[inputlen] = '\0';
    return inputlen;
}

/* Allow the user to input a string and search for it in the given
 * name heap. If repeat is nonzero, then no prompt is shown and
 * instead the previous search is repeated. The function alerts the
 * user if the string could not be found.
 */
static int searchui(int index, int repeat, namelist const *names)
{
    char searchstring[256];
    int i, n;

    if (repeat) {
        i = searchnameheap(NULL, index, repeat, names);
    } else {
        n = doinputui(searchstring, sizeof searchstring, "/", isprint);
        if (n < 0)
            return index;
        if (n == 0) {
            i = searchnameheap(NULL, index, +1, names);
            if (i < 0)
                return index;
        } else {
            while (n--)
                searchstring[n] = tolower(searchstring[n]);
            i = searchnameheap(searchstring, index, +1, names);
        }
    }

    if (i < 0) {
        beep();
        return index;
    }
    return i;
}

/* Get a string from the user containing a hexadecimal number and
 * return the index for that codepoint. If the user doesn't enter a
 * valid codepoint number, they are alerted and the original index is
 * returned.
 */
static int jumpui(int index)
{
    char buf[7];
    int n;

    n = doinputui(buf, sizeof buf, "U+", isxdigit);
    if (n < 0)
        return index;
    n = readuchar(buf);
    if (n < 0) {
        beep();
        return index;
    }
    return n;
}

/* Display the Unicode version the program was built with. Alert if no
 * version string is available.
 */
static void showversion(void)
{
    if (unicodeversion && *unicodeversion) {
        mvaddstr(lastrow, 0, "Unicode version ");
        addstr(unicodeversion);
        (void)getch();
    } else {
        beep();
    }
}

/* Display a brief description of the key commands.
 */
static void showblockhelptext(void)
{
    static char const *helptext[] = {
        "Spc     Move forward one screenful   Bkspc  Move back one screenful",
        "Down/J  Move forward one row         Up/K   Move back one row",
        "}       Move to end of list          {      Move to top of list",
        "Enter   Visit the selected block     /      Search for text in name",
        "N       Repeat the last search       P      Repeat search backwards",
        "V       Display Unicode version      ?      Display this help text",
        "Ctrl-L  Redraw the screen            Q      Cancel and return"
    };

    int i;

    for (i = 0 ; i < (int)(sizeof helptext / sizeof *helptext) ; ++i) {
        move(i, 0);
        clrtoeol();
        addstr("   ");
        addstr(helptext[i]);
    }
    move(i, 0);
    clrtoeol();
    anykey();
}

/* Display a full screen's worth of the block table, centered as
 * closely as possible on the selected entry.
 */
static void drawblocklist(int selected)
{
    char frombuf[8], tobuf[8];
    int namesize, top, i;

    top = selected - ytermsize / 2;
    if (top < 0)
        top = 0;
    if (top + lastrow > blocknames.listsize)
        top = blocknames.listsize - lastrow;
    namesize = xtermsize - 32;

    erase();
    for (i = top ; i < blocknames.listsize && i < top + lastrow ; ++i) {
        if (i == selected)
            attron(A_STANDOUT);
        if (emptyblocks[i])
            attron(A_DIM);
        sprintf(frombuf, "%04X", blocklist[i].from);
        sprintf(tobuf, "%04X", blocklist[i].to);
        mvprintw(i - top, 4, "%6s ..%6s  %-*s",
                 frombuf, tobuf, namesize, blocklist[i].displayname);
        attrset(A_NORMAL);
        if (emptyblocks[i])
            addstr(" [empty]");
    }
    mvaddstr(lastrow, 0, "Character Blocks");
    refresh();
}

/* Render the display of the block table and alter it in response to
 * keystrokes from the user. If the user presses enter the function
 * returns and moves the character display to that block. The user can
 * also quit this function, in which case the existing position in the
 * character table is returned.
 */
static int blockselectui(int startindex)
{
    int index, done, i;

    emptyblocksinit();
    for (i = 0 ; i < blocknames.listsize ; ++i)
        if (blocklist[i].to >= charlist[startindex].uchar)
            break;
    index = i;
    done = FALSE;
    while (!done) {
        if (index < 0)
            index = 0;
        if (index >= blocknames.listsize)
            index = blocknames.listsize - 1;
        drawblocklist(index);
        switch (translatekey(getch())) {
          case 'j':     ++index;                                        break;
          case 'k':     --index;                                        break;
          case 'f':     index += ytermsize - 1;                         break;
          case 'b':     index -= ytermsize - 1;                         break;
          case '{':     index = 0;                                      break;
          case '}':     index = blocknames.listsize;                    break;
          case '/':     index = searchui(index, 0, &blocknames);        break;
          case 'n':     index = searchui(index, +1, &blocknames);       break;
          case 'p':     index = searchui(index, -1, &blocknames);       break;
          case '?':     showblockhelptext();                            break;
          case 'v':     showversion();                                  break;
          case '\f':    clearok(stdscr, TRUE);                          break;
          case 'q':     return startindex;
          case '\002':  return startindex;
          case '\007':  return startindex;
          case 'Q':     exit(EXIT_SUCCESS);
          case '\n':
            if (emptyblocks[index])
                beep();
            else
                done = TRUE;
            break;
        }
    }
    return lookupchar(blocklist[index].from);
}

/* Display a screen showing various encodings for a single character.
 * The character is also displayed as bold and unbold, as many
 * terminals actually use a different font for these, which can mean
 * that the character can have a notably different appearance in each.
 */
static int showcharinfo(int index)
{
    unsigned char utf8[8];
    wchar_t wch[3];
    cchar_t cch;
    char const *name;
    int namesize, utf8size;
    int uchar;
    int i, y;

    uchar = charlist[index].uchar;
    name = charnames.heap + charnames.list[index].offset;
    namesize = charnames.list[index].size;

    if (charlist[index].combining) {
        wch[0] = ' ';
        wch[1] = uchar;
        wch[2] = L'\0';
    } else {
        wch[0] = uchar;
        wch[1] = L'\0';
    }

    if (uchar < 0x0080) {
        utf8[0] = uchar;
        utf8size = 1;
    } else {
        utf8[0] = 0x80 | (uchar & 0x3F);
        if (uchar < 0x0800) {
            utf8[1] = 0xC0 | ((uchar >> 6) & 0x1F);
            utf8size = 2;
        } else {
            utf8[1] = 0x80 | ((uchar >> 6) & 0x3F);
            if (uchar < 0x00010000) {
                utf8[2] = 0xE0 | ((uchar >> 12) & 0x0F);
                utf8size = 3;
            } else {
                utf8[2] = 0x80 | ((uchar >> 12) & 0x3F);
                utf8[3] = 0xF0 | ((uchar >> 18) & 0x07);
                utf8size = 4;
            }
        }
    }

    clear();
    setcchar(&cch, wch, 0, 0, NULL);
    mvadd_wch(1, 1, &cch);
    setcchar(&cch, wch, A_BOLD, 0, NULL);
    mvadd_wch(1, 32, &cch);
    mvprintw(3, 0, "U+%04X", uchar);
    move(3, 10);
    y = drawtext(3, 10, name, namesize) + 1;
    mvaddstr(y++, 0, "       UTF-16: ");
    if (uchar < 0x00010000)
        printw("0x%04X", uchar);
    else
        printw("0x%04X 0x%04X", 0xD800 | ((uchar - 0x00010000) >> 10),
                                0xDC00 | ((uchar - 0x00010000) & 0x03FF));
    mvaddstr(y++, 0, "        UTF-8:");
    for (i = utf8size ; i-- ; )
        printw(" 0x%02X", utf8[i]);
    mvaddstr(y++, 0, "C octal UTF-8: ");
    for (i = utf8size ; i-- ; )
        printw("\\%03o", utf8[i]);
    mvprintw(y++, 0, "   XML entity: &#%u;", uchar);
    i = wcwidth(uchar);
    if (i < 0)
        mvaddstr(y, 0, "        width: n/a");
    else
        mvprintw(y, 0, "display width: %d", i);

    anykey();
    clearok(stdscr, TRUE);
    return index;
}

/* Display the index-th character at location (y, x) using colwidth
 * cells. The official name is rendered first, with the actual glyph
 * displayed at the rightmost position. (Note that wcwidth(3) is used
 * to determine how many cells the glyph occupies. Some terminals
 * and/or terminal fonts do not 100% adhere to what this function
 * reports. It is used because there is currently no alternative.)
 */
static int drawentry(int y, int x, int colwidth, int index)
{
    static wchar_t const ellipsis[] = { (wchar_t)0x2026, L'\0' };
    char buf[8];
    wchar_t wch[3];
    cchar_t cch;
    char const *name;
    int width, size, n;

    if (colwidth < mincolumnwidth)
        return FALSE;
    n = sprintf(buf, " %04X", charlist[index].uchar);
    mvaddstr(y, x, buf + n - 5);
    width = wcwidth(charlist[index].uchar);
    if (width < 0)
        width = 0;
    if (charlist[index].combining && showcombining && width == 0)
        width = 1;
    if (n + 3 < colwidth) {
        addch(' ');
        name = charnames.heap + charnames.list[index].offset;
        size = charnames.list[index].size;
        n = colwidth - 7 - width;
        if (n >= size) {
            addnstr(name, size);
        } else if (n > 6) {
            addnstr(name, n / 2);
            setcchar(&cch, ellipsis, 0, 0, NULL);
            add_wch(&cch);
            n -= n / 2 + 1;
            addnstr(name + size - n, n);
        } else {
            setcchar(&cch, ellipsis, 0, 0, NULL);
            add_wch(&cch);
            if (n > 1)
                addnstr(name + size - n + 1, n - 1);
        }
    }
    if (width == 0)
        return TRUE;
    if (charlist[index].combining && showcombining) {
        wch[0] = accentchar;
        wch[1] = charlist[index].uchar;
        wch[2] = L'\0';
    } else {
        wch[0] = charlist[index].uchar;
        wch[1] = L'\0';
    }
    setcchar(&cch, wch, 0, 0, NULL);
    mvadd_wch(y, x + colwidth - width, &cch);
    return TRUE;
}

/* Display a full screen's worth of the character table, starting with
 * the character given by index. The range of displayed codepoints is
 * shown on the bottommost line of the terminal.
 */
static int drawtable(int index)
{
    int colwidth = xtermsize / columncount;
    int i = index;
    int y, x;

    erase();
    for (x = 0 ; x <= xtermsize - colwidth ; x += colwidth) {
        for (y = 0 ; y < lastrow ; ++y)
            drawentry(y, x, colwidth - 1, i++);
        refresh();
    }
    mvprintw(lastrow, 0, "[%04X - %04X]",
             charlist[index].uchar, charlist[i - 1].uchar);
    refresh();
    return i;
}

/* Display a brief description of the key commands.
 */
static void showmainhelptext(void)
{
    static char const *helptext[] = {
        "Spc     Move forward one screenful   Bkspc  Move back one screenful",
        "Right/L Move forward one column      Left/H Move back one column",
        "Down/J  Move forward one row         Up/K   Move back one row",
        "}       Move forward by U+1000       {      Move back by U+1000",
        "[       Add another column           ]      Reduce number of columns",
        "U/S     Go to a specific codepoint   Ctrl-B View the list of blocks",
        "I       Show info for top codepoint  /      Search for text in name",
        "N       Repeat the last search       P      Repeat search backwards",
        "V       Display Unicode version      ?      Display this help text",
        "Ctrl-L  Redraw the screen            Q      Exit the program"
    };

    int i;

    for (i = 0 ; i < (int)(sizeof helptext / sizeof *helptext) ; ++i) {
        move(i, 0);
        clrtoeol();
        addstr("   ");
        addstr(helptext[i]);
    }
    move(i, 0);
    clrtoeol();
    anykey();
}

/* Render a view of the character table as per the user's keyboard
 * input. Other inputs can temporarily move into other UIs. Return
 * when the user requests to leave the program.
 */
static void mainui(int index)
{
    int tablesize;

    for (;;) {
        if (index < 0)
            index = 0;
        tablesize = (ytermsize - 1) * columncount;
        if (index > charnames.listsize - tablesize)
            index = charnames.listsize - tablesize;
        drawtable(index);
        clearok(stdscr, TRUE);
        switch (translatekey(getch())) {
          case 'j':     ++index;                                        break;
          case 'k':     --index;                                        break;
          case 'l':     index += ytermsize - 1;                         break;
          case 'h':     index -= ytermsize - 1;                         break;
          case 'f':     index += tablesize;                             break;
          case 'b':     index -= tablesize;                             break;
          case '}':     index = offsetchar(index, +0x1000);             break;
          case '{':     index = offsetchar(index, -0x1000);             break;
          case '/':     index = searchui(index, 0, &charnames);         break;
          case 'n':     index = searchui(index, +1, &charnames);        break;
          case 'p':     index = searchui(index, -1, &charnames);        break;
          case 'u':     index = jumpui(index);                          break;
          case 's':     index = jumpui(index);                          break;
          case '\002':  index = blockselectui(index);                   break;
          case '[':     changecolumncount(+1);                          break;
          case ']':     changecolumncount(-1);                          break;
          case 'i':     showcharinfo(index);                            break;
          case '?':     showmainhelptext();                             break;
          case 'v':     showversion();                                  break;
          case '\f':    clearok(stdscr, TRUE);                          break;
          case 'q':     return;
          case 'Q':     exit(EXIT_SUCCESS);
        }
    }
}

/*
 * Top-level functions
 */

/* Parse the command-line arguments. The return value is the initial
 * codepoint specified on the command line, or 0 if no initial
 * codepoint was present. If the command line was invalid, the
 * function quits the program.
 */
static int readcmdline(int argc, char *argv[])
{
    static char const *optstring = "a:Ai";
    static struct option options[] = {
        { "accent", required_argument, NULL, 'a' },
        { "noaccent", no_argument, NULL, 'A' },
        { "input", no_argument, NULL, 'i' },
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { 0, 0, 0, 0 }
    };
    char const *str;
    int ch, i;

    readstdin = !isatty(0);
    while ((ch = getopt_long(argc, argv, optstring, options, NULL)) != EOF) {
        switch (ch) {
          case 'a':
            if (optarg[1] == '\0') {
                accentchar = optarg[0];
            } else {
                accentchar = readuchar(optarg);
                if (accentchar < 0)
                    die("invalid accent character value: \"%s\"", optarg);
                accentchar = charlist[accentchar].uchar;
            }
            break;
          case 'A':
            showcombining = FALSE;
            break;
          case 'i':
            readstdin = TRUE;
            break;
          case 'h':
            for (i = 0 ; i < (int)(sizeof yowzitch / sizeof *yowzitch) ; ++i)
                puts(yowzitch[i]);
            exit(EXIT_SUCCESS);
          case 'v':
            for (i = 0 ; i < (int)(sizeof vourzhon / sizeof *vourzhon) ; ++i)
                puts(vourzhon[i]);
            exit(EXIT_SUCCESS);
          default:
            die("Try --help for more information.");
        }
    }
    ch = 0;
    if (optind < argc) {
        str = argv[optind];
        ch = readsinglecharstring(str);
        if (ch < 0) {
            ch = readuchar(str);
            if (ch < 0) {
                ch = searchnameheap(str, 0, +1, &charnames);
                if (ch < 0)
                    die("Invalid start value: \"%s\".", argv[optind]);
            }
        }
        ++optind;
    }
    if (optind < argc)
        die("Bad command-line argument.\nTry --help for more information.");
    return ch;
}

/* Run the program.
 */
int main(int argc, char *argv[])
{
    int startpos;

    setlocale(LC_ALL, "");
    startpos = readcmdline(argc, argv);
    if (readstdin) {
        showinputchars();
        return 0;
    }

    ioinit();
    mainui(startpos);
    return 0;
}
