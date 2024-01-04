#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//**************************************************************************/
//*                                                                        */ 
//*           Converts BrainF*cked Code to Human-Readable C Code           */
//*                                                                        */ 
//**************************************************************************/


// Put leading indentation...
void PutIndent(int indent) {
	int i;

	for (i = 0; i <= indent; ++i)
		printf("    ");
}

// Put consolidated code for sequences of  "+", "-", "<", and ">"
// Returns next character (which is not part of the sequence) or EOF
int PutConsolidatedCode(int opcode, 
						int indent, 
						char *instructions, 
						char *instructionm) {
	int c;
	int n = 1;
					
	c = getchar();
	while (c == opcode || c == 10 || c == 13) {
		if (c == opcode)
		    ++n;
					
		c = getchar();
	}

	PutIndent(indent);

	if (n == 1)
		printf("%s;\n", instructions);
	else
		printf("%s%d;\n", instructionm, n);

	return c;
}

// Put "regular" code (".", ",", "[", and "]") with indentation...
// Returns next character or EOF
int PutCode(int indent, char *instruction) {
	PutIndent(indent);
	puts(instruction);

	return getchar();
}

// Build comment line(s) out of non-BF code characters...
// Returns next (non-comment) character or EOF
int PutComment(int c) {
	int n = 0, 
		i = 0,
		lf = 0;

	puts("/*");
	putchar(c);

	c = getchar();
	while (c >= 0 && !strchr("<>[]+-,.", c)) {
		if (c == 10 || c == 13) {
			if (c == 10)
				++lf;
		}
		else if (c != ' ') {
			if (lf) {
				if (lf > 2)
					lf = 2;

				for (i = 0; i < lf; ++i)
					puts("");

				lf = 0;
			}
			else {
				if (n > 2)
					n = 2;

				for (i = 0; i < n; ++i)
					putchar(' ');
			}

			n = 0;

			putchar(c);
		}
		else
			++n;

		c = getchar();
	}

	puts("\n*/");

	return c;
}

int main(int argc, char **argv) {
    int c;
	int indent = 0;

	// Put standard output program header code...
	puts("#include <stdio.h>\n"
		 "#include <stdlib.h>\n\n"
		 "int a[9999];\n\n"
         "int main(int argc, char **argv) {\n"
         "    int *p = a;\n\n"
		 "    /* Start of Brain-F*cked Translated Code... */");

	// Process BF code
	c = getchar();	
	while (c >= 0) {
        switch(c) {
			case '>':
				c = PutConsolidatedCode(c, indent, "++p", "p += ");
				break;

			case '<':
				c = PutConsolidatedCode(c, indent, "--p", "p -= ");
				break;

			case '+':
				c = PutConsolidatedCode(c, indent, "++(*p)", "(*p) += ");
				break;

			case '-':
				c = PutConsolidatedCode(c, indent, "--(*p)", "(*p) -= ");
				break;

			case '.':
				c = PutCode(indent, "putchar(*p);");
				break;

			case ',':
				c = PutCode(indent, "*p = getchar();");
				break;

			case '[':
				c = PutCode(indent, "while (*p) {");
				++indent;
				break;

			case ']':
				--indent;
				if (indent < 0) {
					puts("\n\n/* Error in Brain-F*cked Source Code:  unmatched Brainf*cked \"]\" instruction! */\n");

					c = getchar();
				}
				else
					c = PutCode(indent, "}");
				break;

			case ' ':
			case 10:
			case 13:
				// Skip over blanks, carriage returns, and linefeeds...
				c = getchar();
				break;

			default:
				// Build a comment out of any other chars in the input stream...
				c = PutComment(c);
        }
    }

	// Put standard C-program trailer code...
	PutIndent(indent);
	puts("/* End of Brain-F*cked Translated Code... */\n");

	if (indent > 0) {
		printf("/* Error in Brain-F*cked Source Code:  %d unmatched Brainf*cked \"[\" instructions! */\n\n", indent);

		/* Make progam compilable... */
		while (indent) {
			--indent;

			PutIndent(indent);
			puts("}");
		}
	}
	else if (indent < 0)
		printf("\n\n/* Error in Brain-F*cked Source Code:  There were %d unmatched Brainf*cked \"]\" instructions! */\n\n", -indent);

	PutIndent(indent);
	printf("return 0;\n"
           "}\n");

	// Exit stage right!
	return 0;
}
