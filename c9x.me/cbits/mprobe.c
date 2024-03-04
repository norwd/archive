#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/select.h>

typedef struct Box Box;

struct Box {
	char *file;
	int watch;
	int new;
	int old;
	int tot;
};

enum {
	Nbox = 100,
	F_O = 1,
	F_N = 2,
	F_R = 4,
};

char box_lo[] =
"                \n"
"                \n"
"                \n"
"   ----------.  \n"
"  |      MAIL|  \n"
"  | O-----   |  \n"
"  |      #   |  \n"
"  `-----+--+-'  \n"
"        |  |    \n"
"        |  |    \n"
"        |  |    \n"
"        |  |    \n"
"        |  |    \n"
"================\n"
;

char box_hi[] =
"                \n"
"    ##          \n"
"    |           \n"
"   -|--------.  \n"
"  | |    MAIL|  \n"
"  | O        |  \n"
"  |          |  \n"
"  `-----+--+-'  \n"
"        |  |    \n"
"        |  |    \n"
"        |  |    \n"
"        |  |    \n"
"        |  |    \n"
"================\n"
;

Box box[Nbox];
int nbox;
int notfd;

void
die(char *s)
{
	fprintf(stderr, "dying: %s\n", s);
	exit(1);
}

int
scan(Box *b)
{
	static char
		from[] = "\nFrom ",
		status[] = "\nStatus: ";
	char *p;
	int c, c1, n, o, t, flag;
	FILE *f;

	f = fopen(b->file, "r");
	if (!f)
		return -1;

	p = &from[1];
	n = 0;
	o = 0;
	t = 0;

	for (;;) {
		while (*p) {
			c = getc(f);
			if (c == EOF)
				goto Done;
			if (c != *p++) {
				p = from;
				if (c == *p)
					p++;
			}
		}
		t++;
		p = status;
		c1 = 0;
		while (*p && (c1 != '\n' || c != '\n')) {
			c1 = c;
			c = getc(f);
			if (c == EOF)
				goto Done;
			if (c != *p++)
				p = status;
		}
		if (*p == 0) {
			flag = 0;
			while ((c = getc(f)) != '\n')
				switch (c) {
				case 'N':
					flag |= F_N;
					break;
				case 'O':
					flag |= F_O;
					break;
				case 'R':
					flag |= F_R;
					break;
				}
			if (flag & F_N)
				n++;
			if (!(flag & F_R) && (flag & F_O))
				o++;
		} else
			/* no Status means new */
			n++;
		p = from;
	}

Done:
	fclose(f);
	b->new = n;
	b->old = o;
	b->tot = t;
	return 0;
}

void
watch(Box *b)
{
	b->watch = inotify_add_watch(notfd, b->file, IN_MODIFY);
	if (b->watch == -1)
		die("inotify_add_watch failed");
}

void
init(int ac, char *av[])
{
	static char buf[512];
	Box *b;
	int a;

	notfd = inotify_init();
	if (notfd == -1)
		die("inotify_init failed");

	if (ac == 1) {
		ac = 2;
		av[1] = "%";
	}
	for (a = 1; a < ac; a++) {
		if (nbox == Nbox)
			die("too many mailboxes watched");
		b = &box[nbox++];
		if (strcmp(av[a], "%") == 0) {
			sprintf(buf, "/var/mail/%s", getenv("USER"));
			b->file = buf;
		} else
			b->file = av[a];
		watch(b);
		scan(b);
	}
}

int
main(int ac, char *av[])
{
	Box *b;
	fd_set fs;
	struct inotify_event ev;
	int n;

	init(ac, av);
	for (;;) {
		printf("\x1b[;H\x1b[2J");
		n = 0;
		for (b = box; b != &box[nbox]; b++)
			n += b->new;
		if (n)
			puts(box_hi);
		else
			puts(box_lo);
		for (b = box; b != &box[nbox]; b++)
			printf("%2d new %2d old %4d tot    %s\n",
				b->new, b->old, b->tot, b->file);
		FD_ZERO(&fs);
		FD_SET(notfd, &fs);
		if (select(notfd+1, &fs, 0, 0, 0) == -1) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			die("select failed");
		}
		read(notfd, &ev, sizeof ev);
		for (b = box; b->watch != ev.wd; b++)
			;
		if (ev.mask & IN_IGNORED)
			watch(b);
		scan(b);
	}
}
