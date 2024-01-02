/*
 * data.h: Declarations of objects holding the Unicode data.
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

#ifndef _data_h_
#define _data_h_

/* The position of a name in a string heap.
 */
typedef struct nameinfo {
    unsigned int offset:24;     /* offset of name in heap */
    unsigned int size:8;        /* length of name */
} nameinfo;

/* Data providing a list of names stored in a string heap.
 */
typedef struct namelist {
    int listsize;               /* the number of names in the list */
    char *lastsearch;           /* provides a buffer to hold a search string */
    char const *heap;           /* the complete heap of strings */
    nameinfo const list[];      /* the position of each name in the heap */
} namelist;

/* Data stored for each character/codepoint.
 */
typedef struct charinfo {
    unsigned int uchar:21;      /* the codepoint value */
    unsigned int combining:1;   /* true if this is a combining character */
} charinfo;

/* Data stored for each block.
 */
typedef struct blockinfo {
    char const *displayname;    /* official block name */
    unsigned int from;          /* first codepoint in the block */
    unsigned int to;            /* last codepoint in the block */
} blockinfo;

/* The complete list of Unicode characters. (The charlist array is the
 * same size as the charnames' list array.)
 */
extern namelist const charnames;
extern charinfo const charlist[];

/* The complete list of blocks of Unicode characters. (The blocklist
 * array has the same size as the blockname's list array.)
 */
extern namelist const blocknames;
extern blockinfo const blocklist[];

/* The size of the buffer where search strings are stored.
 */
extern int const maxsearchstringlen;

/* The Unicode version string.
 */
extern char const *unicodeversion;

#endif
