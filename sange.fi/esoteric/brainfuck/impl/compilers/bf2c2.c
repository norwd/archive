/*
  Brainfuck to C

  Converts any brainfuck program to ANSI C source file.
  (c) 2003 Jean-Yves Lamoureux


  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include <stdio.h>

// Making it a bit portable for the 6502 interpreter
#define BYTE unsigned char
#define WORD unsigned short
// Official brainfuck memory size
#define MAX_SIZE 30000
#define MAX_PROG_SIZE 10000

BYTE memory[MAX_SIZE];
BYTE stack[MAX_PROG_SIZE];
WORD curPtr;

int main(int argc, char *argv[])
{
  WORD i=0, size=0;
  FILE *fp;
  
  if(argc!=2)
    {
      printf("You must supply a program file\n");
      return -1;
    }

  
  /* Reads text file containing the programm */
  fp = fopen(argv[1], "r");
  while((!feof(fp))&&(i<MAX_PROG_SIZE)) 
    { 
      stack[i] = fgetc(fp); 
      if((stack[i]!=10) && (stack[i]!=13)&& (stack[i]!=' ')) 
	{
	  i++;
	} 
    }
  size=i-1;
  for(i=0;i<MAX_SIZE;i++)
    {
      memory[i] = 0;
    }
  
  i=0;
  curPtr=0;
  

  printf("#include <stdio.h>\n");
  printf("#define BYTE unsigned char\n");
  printf("#define WORD unsigned short\n");
  printf("#define MAX_SIZE %d /* Official brainfuck memory size */\n", MAX_SIZE);
  printf("#define MAX_PROG_SIZE %d\n", MAX_PROG_SIZE);
  printf("BYTE memory[MAX_SIZE];\n");
  printf("BYTE stack[MAX_PROG_SIZE];\n");
  printf("WORD curPtr=0;\n");
  printf("int main(void)\n{\n");


  for(i=0;i<size;i++)
    {    
      switch(stack[i])
	{
	case '>':
	  printf("curPtr++;\n");
	  break;
	case '<':
	  printf("curPtr--;\n");
	  break;
	case '+':
	  printf("memory[curPtr]++;\n");
	  break;
	case '-':
	  printf("memory[curPtr]--;\n");
	  break;
	case '.':
	  printf("printf(\"%%c\",  memory[curPtr]);\n");
	  break;
	case ',':
	  printf("memory[curPtr] = getchar();");
	  break;
	case '[':
	  printf("while(memory[curPtr]!=0){\n");
	  break;
	case ']':
	  printf("}\n");
	  break;


	default:
	  break;
	}

 

    }
  
  printf("return 0;\n}\n");
  return 0;
}







