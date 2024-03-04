/*% cc -o # %
 * subs [N]
 * Print all substrings of length N.
 * If N is not specified, it defaults
 * to two.  If N is greater than 16,
 * the program will not work.
 */
#include<stdio.h>
#include<stdlib.h>
int main(int ac, char *av[]) {
	char s[16], *p=s;
	int m=av[1]?atoi(av[1]):2, i=m;
	for(;;) {
		if (m<=0 || (*p++ = getchar()) == EOF)
			exit(0);
		if (p-s>=m)
			p=s;
		if (--i>0)
			continue;
		for(i=m; i; i--)
			putchar(s[((p-s)+(m-i))%m]);
		putchar('\n');
	}
}
