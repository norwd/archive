/*% clang -Wall -o # %
 * calc
 * Small desktop calculator.
 * It uses the Shunting-yard algorithm of
 * E. Dijkstra to parse arithmetic expressions
 * and prints the result of the computation.
 * Computations are performed on integers,
 * operations available are + - * / % and
 * parenthesis.
 */
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

enum {
	Stacklen = 32,
	Linelen = 512
};

jmp_buf boom;
int prec[] = {
	['+'] = 1, ['-'] = 1,
	['*'] = 2, ['/'] = 2,
	['%'] = 3,
	['('] = 0
};
char ops[Stacklen];
long long st[Stacklen];
int opi, sti;

void
panic(const char *s)
{
	fputs(s, stderr);
	fputc('\n', stderr);
	exit(1);
}

void
err(const char *s)
{
	printf("?%s\n", s);
	longjmp(boom, 1);
}

void
evalop(char o)
{
	if (sti < 2)
		err("Args.");
	switch (o) {
	case '%':
		st[sti-2] = st[sti-2] % st[sti-1];
	case '/':
		st[sti-2] = st[sti-2] / st[sti-1];
		break;
	case '*':
		st[sti-2] = st[sti-2] * st[sti-1];
		break;
	case '-':
		st[sti-2] = st[sti-2] - st[sti-1];
		break;
	case '+':
		st[sti-2] = st[sti-2] + st[sti-1];
		break;
	case '(':
		panic("evalop: '('");
		break;
	default:
		panic("evalop1: ?");
		break;
	}
	sti--;
}

void
pushop(char o)
{
	if (opi >= Stacklen)
		err("Stack overflow.");
	ops[opi++] = o;
}

void
pushn(long long l)
{
	if (sti >= Stacklen)
		err("Stack overflow.");
	st[sti++] = l;
}

long long
eval(char *s)
{
	char *c;

	opi = sti = 0;
	while (*s)
		switch (*s) {
		case '\n':
		case ' ':
			s++;
			continue;
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
			while (opi>0 && prec[ops[opi-1]]>prec[*s])
				evalop(ops[--opi]);
		case '(':
			pushop(*s++);
			continue;
		case ')':
			while (opi>0 && ops[opi-1]!='(')
				evalop(ops[--opi]);
			if (!opi)
				err("Unbalanced parens.");
			--opi, s++;
			continue;
		default:
			if (*s>='0' && *s<='9') {
				pushn(strtoull(s, &c, 10));
				s = c;
				continue;
			}
			err("Invalid char.");
		}
	while (opi) {
		if (ops[opi-1] == '(')
			err("Unbalanced parens.");
		evalop(ops[--opi]);
	}
	return sti ? st[0] : 0;
}

int
main(void)
{
	char line[Linelen];

	setjmp(boom);
	for (;;) {
		if (!fgets(line, Linelen, stdin))
			break;
		printf("↳ %lld\n", eval(line));
	}
	exit(0);
}
