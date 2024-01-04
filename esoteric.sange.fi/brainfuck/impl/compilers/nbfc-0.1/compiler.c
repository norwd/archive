#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "bf.h"
#include "config.h"
#define VERSION "0.1"

extern FILE *yyin;
extern FILE *yyout;
char *infile;			/* name of the brainfuck file to be compiled */
char *coutfile;	/* name of the generated C file (normally bf.out.c) */
char *outfile;			/* name of the executable */
char compile[256];		/* how the C compiler is called */
char javaoutfile[256]; /* the name of the Java file generated */
int keep = 0;			/* keep the generated source code? */
int verbose = 0;		/* be verbose? */
int java = 0;        /* compile to Java? */
int no_compile = 0; /* don't compile, just generate C or Java code */
void emmit_header ();
void emmit_footer ();
void check_params ();
void usage ();

void
emmit (char *string)
{
  fprintf (yyout, "%s\n", string);
}

void
emmit_header ()
{
  emmit ("/*");
  emmit (" * Generated automatically by the new brainfuck compiler");
  emmit (" */");
  if (!java)
    {
      emmit ("#include <stdio.h>");
      emmit ("int p;");
      emmit ("int array[30000];");
      emmit ("int main(){");
    }
  else
    {
      emmit("import java.io.*;");
      emmit ("public class"); 
      emmit(outfile);
      emmit("{");
      emmit ("public static void putchar(char q) {");
      emmit ("System.out.print(q);");
      emmit ("}");
      emmit ("public static char getchar() throws IOException {");
      emmit ("DataInputStream input = new DataInputStream(System.in);");
      emmit ("return(input.readChar());");
      emmit ("}");
      emmit ("public static void main (String[] argv) throws IOException {");
      emmit ("char p = 0;");
      emmit ("char[] array = new char[30000];");
    }
}

void
emmit_footer ()
{
  if (!java)
    {
      emmit ("return(0);");
      emmit ("}");
    }
  else
    {
      emmit ("}");
      emmit ("}");
    }
  emmit ("/*");
  emmit (" * End of automatically generated code");
  emmit (" */");
  fflush (yyout);
}

void
check_params (argc, argv)
     int argc;
     char *argv[];
{
  signed char c;
  /* get command line options */
  while (1)
    {
      c = getopt (argc, argv, "gcjkvho:");
      if (c == -1)
	break;

      switch (c)
	{
	case 'c':
	  printf ("nbfc -- The new brainfuck compiler\n");
	  printf ("\n");
	  printf ("The following copyright statement covers all of nbfc - either text or\n");
	  printf ("the binary code compiled from the source text.\n");
	  printf ("\n");
	  printf ("Copyright (c) 1999 Jens Ohlig <jo@koeln.ccc.de>\n");
	  printf ("All rights reserved.\n");
	  printf ("\n");
	  printf ("Redistribution and use in source and binary forms, with or without\n");
	  printf ("modification, are permitted provided that the following conditions\n");
	  printf ("are met:\n");
	  printf ("1. Redistributions of source code must retain the above copyright\n");
	  printf ("   notice, this list of conditions and the following disclaimer.\n");
	  printf ("2. Redistributions in binary form must reproduce the above copyright\n");
	  printf ("   notice, this list of conditions and the following disclaimer in the\n");
	  printf ("   documentation and/or other materials provided with the distribution.\n");
	  printf ("\n");
	  printf ("THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND\n");
	  printf ("ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n");
	  printf ("IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n");
	  printf ("ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE\n");
	  printf ("FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n");
	  printf ("DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n");
	  printf ("OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n");
	  printf ("HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n");
	  printf ("LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\n");
	  printf ("OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\n");
	  printf ("SUCH DAMAGE.\n");
	  exit (0);
	case 'h':
	  usage ();
	  exit (0);
	case 'k':
	  keep = 1;
	  break;
	case 'o':
	  outfile = optarg;
	  break;
	case 'v':
	  verbose = 1;
	  break;
   case 'j':
     java =1;
     break;
   case 'g':
     no_compile = 1;
     keep =1;
     break;
	}
    }
}

void
usage ()
{
  printf ("nbfc %s -- The new brainfuck compiler\n", VERSION);
  printf ("Usage:\n");
  printf ("\tnbfc [-o file] [options] file\n");
  printf ("\nYou can give a name for the executable with -o filename.\n");
  printf ("Options:\n");
  printf ("\t-k keep generated intermediate code (C or Java)\n");
  printf ("\t-j generate and compile a Java class instead of a C executable\n");
  printf ("\t-v be verbose\n");
  printf ("\t-g don't compile, just generate intermediate file (C or Java)\n");
  printf ("\t-c display the copying license\n");
  printf ("\t-h display this help\n");
}

int
main (int argc, char **argv)
{
  check_params (argc, argv);
  /* get the file name */
  if ((optind >= argc) || (strcmp (argv[optind], "-") == 0))
    {
      printf ("%s: no input file\n", argv[0]);
      usage ();
      exit (0);
    }
  infile = argv[optind++];
  yyin = fopen (infile, "r");
  if (!yyin) {
		printf ("%s: error opening input file %s\n", argv[0], infile);
      exit (0);
    }              
  coutfile = "bf.out.c";
  if (!outfile)
    outfile = "bf.out";
  if (java)
    {
      strcat(javaoutfile, outfile);
		strcat(javaoutfile, ".java");
      coutfile = javaoutfile;      
    }
  yyout = fopen (coutfile, "w");
  if (!yyout) {
		printf ("%s: error opening output file %s\n", argv[0], outfile);
      exit (0);
    }
  /* parse input and generate C or Java file */
  if (verbose)
    printf ("Emitting header...\n");
  emmit_header ();
  if (verbose)
    printf ("Parsing and generating...\n");
  yyparse ();
  if (verbose)
    printf ("Emitting footer...\n");
  emmit_footer ();
  /* get compiler invocation */
  if (!java)
    {
      strcat (compile, CC);
      strcat (compile, " -o ");
      strcat (compile, outfile);
      strcat (compile, " bf.out.c");
    }
  else
    {
      strcat (compile, JAVAC);
      strcat (compile, " ");
      strcat (compile, coutfile);
    }
  /* compile and remove intermediate file unless we want to keep it */
  if (!no_compile) {
  if (verbose)
    {
      printf ("Compiling...\n");
      printf ("%s\n", compile);
    }
  system (compile);
  }
  if (!keep)
    {
      if (verbose)
	printf ("Deleting intermediate file %s...\n", coutfile);
      unlink (coutfile);
    }
  else
    {
      if (verbose)
	printf ("Keeping intermediate file %s...\n", coutfile);
    }
  if (verbose)
    printf ("Done.\n");
  return (0);
}
