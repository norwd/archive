#include <stdio.h>
#include <stdlib.h>


int getcols()
{
    char *str;
    int cols;

    str = getenv("COLUMNS");

    if (str != 0)
        cols = atoi(str);
    else
        cols = 80;

    return cols;
}

void trim(int cols, FILE *in, FILE *out)
{
    int colsinline = 0;
    int ch;

    while(!feof(in))
    {
        ch = getc(in);
        if (ch == EOF)
            break;
        if (colsinline < cols)
            putc(ch, out);
            /*fprintf(out, "cil: %i. char: %c\n",
                    colsinline, (char) ch);*/
        ++colsinline;
        if ('\n' == ch)
        {
            if (colsinline > cols)
                putc(ch, out);
            colsinline = 0;
        }
    }
}

int main(int argc, char **argv)
{
    int cols = 0;

    if (argc > 1)
        cols = atoi(argv[1]);

    if (cols < 1)
        cols = getcols();

    trim(cols, stdin, stdout);

    return 0;
}
