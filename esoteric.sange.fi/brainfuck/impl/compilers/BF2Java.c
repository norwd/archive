/*
 * BF2Java
 * Copyright (C) 2003 Thomas Cort
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*
 * Program Name:  BF2Java
 * Version:       1.0
 * Date:          2003-03-18
 * Description:   Converts Brainfuck source to Java source
 * License:       GPL
 * Web page:      http://www.brainfuck.ca
 * Download:      http://www.brainfuck.ca/BF2Java.c
 * Source Info:   http://www.brainfuck.ca/downloads.html
 * Latest Ver:    http://www.brainfuck.ca/downloads.html
 * Documentation: None
 * Help:          tom@brainfuck.ca
 * Developement:  tom@brainfuck.ca
 * Bugs:          tom@brainfuck.ca
 * Maintainer:    Thomas Cort <tom@brainfuck.ca>
 * Developer:     Thomas Cort <tom@brainfuck.ca>
 * Interfaces:    Command Line
 * Source Lang:   C
 * Build Prereq:  None
 * Related Progs: BF2C
 * Category:      Software Development > Programming language conversion
 */

#include<stdio.h>

int main(int argc, char **argv) {

  int args,        /* index of current argument  */
      pc,          /* program counter            */
      prog_len;    /* length of program          */
  int p[32768];    /* storage space for the prog */

  FILE *stream, *fopen();

  /* For every arguement do some interpreting */
  /* Each arguement should be a filename      */
  for (args = 1; args < argc; args++) {

    /* Open da file */
    stream = fopen(argv[args], "r");

    prog_len = 0;
    
    /* read the file and store it in p[] */
    for (pc = 0; pc < 32768 && (p[pc] = getc(stream)) != EOF; pc++)
      prog_len++;

    /* reset the program counter */
    pc = 0;

    fclose(stream);

    /* print the program headers */
    printf("import java.io.BufferedReader;\nimport java.io.InputStreamReader;\n\npublic class output {\n\n  public static void putchar(byte c) {\n    byte [] out = {c};\n    String s = new String(out);    System.out.print(s);  }\npublic static byte getchar() {\n  BufferedReader Stream = \n    new BufferedReader(new InputStreamReader(System.in));\n  try {\n    String str = Stream.readLine();\n    byte [] in = str.getBytes();\n    return in[0];\n  } catch (Exception e) {\n    throw new Error(\"Input Parse Error\");\n}\n}\n\n public static void main(String [] args) {\n  int pc = 0;\n  byte[] x = new byte[32768];\n");

    /* visit every element that has part of the bf program in it */
    for(pc = 0; pc < prog_len; pc++) {

      /* '+' */
      if      (p[pc] == 43) printf("x[pc]++;\n");

      /* '-' */
      else if (p[pc] == 45) printf("x[pc]--;\n");

      /* '.' */
      else if (p[pc] == 46) printf("putchar(x[pc]);\n");

      /* ',' */
      else if (p[pc] == 44) printf("x[pc] = getchar();\n");

      /* '>' */
      else if (p[pc] == 62) printf("pc++;\n");

      /* '<' */
      else if (p[pc] == 60) printf("pc--;\n");

      /* '[' */
      else if (p[pc] == 91) printf("while(x[pc] != 0) {\n");

      /* ']' */
      else if (p[pc] == 93) printf("}\n");

    }  
    printf("\n}\n}\n");  
  }

  return 0;
}
