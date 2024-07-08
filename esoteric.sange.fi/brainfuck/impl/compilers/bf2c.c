/* Thu Aug 02 2001 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BS 2<<16

FILE *in,
     *out;
int spaces = 2,
    inc    = 1,
    i      = 0,
    ret[],
    *c;

int main ( int argc, char** argv )
{
  if ( !(argc > 1 ) ) {
    printf( "usage: bf2c inputfile outputfile\n"
            "       inputfile contains the bf-code\n"
            "       outputs will be written to outputfile\n"
            "       else stdout is used\n"
            "--- [2001, Erdal Karaca (SYS64738)]\n"
    );
    return 1;
  }

  if ( (in = fopen( argv[1], "rb"  )) && (out = fopen( argv[2], "w+b" ))  ) {
    long  l = time( NULL );
    fprintf ( out, "%s%s%s",
              "/*\n"
              " * file generated on ",
              asctime( localtime( &l ) ),
              " * by bf2c, the bf to c converter\n"
              " * [2001] Erdal Karaca (SYS64738)\n"
              " */\n"
              "#include <stdio.h>\n"
              "#define BS 2<<16\n"
              "\n"
              "int p = 0, i = 0;\n"
              "int a[BS];\n\n"
              "int main( int argc, char** argv ) {\n"
              "  while ( i < BS ) { a[i] = 0; i++; }\n"
              "  i = 0;\n"
    );
    fflush( out );
    c = malloc( BS * sizeof (unsigned char) );

    /* non-bf-characters need to be deleted */
    while ( (*c = getc( in )) != -1 ) {
      switch ( *c ) {
        case '+': case '-': case '.': case ',': case '<': case '>': case '[': case ']':
             c++; i++;
      }
    }
    c -= i;

    while ( *c > 0 ) {
      switch ( *c ) {
        case '+':
             while ( *c++ == '+' ) if ( *c == '+' ) inc++; else break;
             fprintf( out, "%s%s%d%s", repeat( " ", spaces ), "a[p] += ", inc, ";\n" );
             inc = 1;
             break;
        case '-':
             while ( *c++ > 0 ) if ( *c == '-' ) inc++; else break;
             fprintf( out, "%s%s%d%s", repeat( " ", spaces ), "a[p] -= ", inc, ";\n" );
             inc = 1;
             break;
        case '<':
             while ( *c++ > 0 ) if ( *c == '<' ) inc++; else break;
             fprintf( out, "%s%s%d%s", repeat( " ", spaces ), "p -= ", inc, ";\n" );
             inc = 1;
             break;
        case '>':
             while ( *c++ > 0 ) if ( *c == '>' ) inc++; else break;
             fprintf( out, "%s%s%d%s", repeat( " ", spaces ), "p += ", inc, ";\n" );
             inc = 1;
             break;
        case '[':
             fprintf( out, "%s%s", repeat( " ", spaces ), "while( a[p] ) {\n" );
             spaces += 2;
             c++;
             break;
        case ']':
             spaces -= 2;
             fprintf( out, "%s%s", repeat( " ", spaces ), "}\n" );
             c++;
             break;
        case '.':
             while ( *c++ > 0 ) if ( *c == '.' ) inc++; else break;
             fprintf( out, "%s%s%d%s", repeat( " ", spaces ), "for ( i = ", inc, " - 1; i >= 0; i-- ) putchar( a[p] );\n" );
             inc = 1;
             break;
        case ',':
             while ( *c++ > 0 ) if ( *c == ',' ) inc++; else break;
             fprintf( out, "%s%s%d%s", repeat( " ", spaces ), "for ( i = ", inc, " - 1; i >= 0; i-- ) a[p] = getchar();\n" );
             inc = 1;
             break;
        default:
             c++;
             break;
      }
      fflush( out );
    }
    fprintf( out, "  free( a );\n" );
    fprintf( out, "  return 0;\n" );
    fprintf( out, "}\n" );
    fflush( out );
    fclose( in );
    fclose( out );
    free( ret );
    free( c );
  }
  else {
    printf( "couldn't open files... quitting..." );
    return 1;
  }
  return 0;
}

char* repeat ( char* c, int x ) {
  ret[ strlen( c ) * x ];
  strcpy( ret, c );
  x--;
  while ( x ) {
    strcat( ret, c );
    x--;
  }
  return ret;
}
