/*% cc -Wall -o # %
 * avltest
 * AVL testing program.
 */
#include <stdio.h>
#include <string.h>
#include "avl.c"

void
putavl(struct N *n)
{
	if (!n) {
		printf("{}");
		return;
	}
	printf("{ bal=%d, l=", (int)n->bal);
	putavl(n->n[0]);
	printf(", p='%s', r=", (char *)n->p);
	putavl(n->n[1]);
	printf(" }");
}

char *
avls(struct N *n, char *s)
{
	if (!n) {
		*s=0;
		return s;
	}
	s=avls(n->n[0], s);
	strcpy(s, n->p);
	s[1]=' ';
	return avls(n->n[1], s+2);
}

int
main(void)
{
	char *strs[] = { "a", "b", "c", "d", "e", "f", "g",
	                 "h", "i", "j", "k", "l", "m", "n",
	                 "o", "p", "q", "r", "s", "t", "u",
	                 "v", "w", "x", "y", "z" };
	int rtest[] = { 0, 2, 1 },
	    ltest[] = { 2, 0, 1 };
	char s[53];
	int i;
	struct Tree *t;

	/* Test all 4 possible cases at
	 * insertion time.
	 */
	t=avlnew((int (*)(void *, void *))strcmp);
	for (i=0; i<sizeof strs/sizeof strs[0]; i++) {
		avlins(strs[i], t);
		avls(t->root, s);
		printf("%s\n", s);
	}
	avlfree(t);

	t=avlnew((int (*)(void *, void *))strcmp);
	while (--i>=0) {
		avlins(strs[i], t);
		avls(t->root, s);
		printf("%s\n", s);
	}
	avlfree(t);

	t=avlnew((int (*)(void *, void *))strcmp);
	for (i=0; i<sizeof rtest/sizeof rtest[0]; i++) {
		avlins(strs[rtest[i]], t);
		putavl(t->root), puts("");
	}
	avlfree(t);

	t=avlnew((int (*)(void *, void *))strcmp);
	for (i=0; i<sizeof ltest/sizeof ltest[0]; i++) {
		avlins(strs[ltest[i]], t);
		putavl(t->root), puts("");
	}
	avlfree(t);

	return 0;
}
