/*
 *  Text-based dungeon/adventure game, for the
 *  UW Experimental College course in Intermediate C Programming
 *
 *  Copyright 1999 Steve Summit
 *  scs@eskimo.com
 */

#include <stdio.h>
#include <unistd.h>
#include "game.h"

#define MAXLINE 100

struct actor *players = NULL;

void newconnection(int);
int ngetline(struct actor *, char [], int);
void closeconnection(struct actor *);

void fdenqueue(int fd, int which);
void fddequeue(int fd, int which);
void selectwrapper(void);
int fdready(int fd, int which);

extern int socksetup(int);
extern int sockaccept(int sock, struct sockaddr_in **clientp);

domultiplayer()
{
int sock;
struct sockaddr_in *clientp;
int msgsock;
struct actor *actp, *nextactp;

sock = socksetup(4001);
fdenqueue(sock, 0);

while(1)
	{
	selectwrapper();

	if(fdready(sock, 0))
		newconnection(sock);

	for(actp = players; actp != NULL; actp = nextactp)
		{
		nextactp = actp->next;	/* grab first, in case this one disconnects */

		if(fdready(actp->remotefd, 0))
			{
			char line[MAXLINE];
			struct sentence cmd;

			if(ngetline(actp, line, MAXLINE) == EOF)
				{
				closeconnection(actp);
				continue;
				}

			if(!parseline(actp, line, &cmd))
				continue;

			docommand(actp, &cmd);
			}
		}
	}
}

void newconnection(int sock)
{
actor *actp;
static int nplayers = 0;
int msgsock = sockaccept(sock, NULL);
fdenqueue(msgsock, 0);

actp = new actor;

actp->remotefd = msgsock;

sprintf(actp->name, "player %d", ++nplayers);

actp->next = players;
players = actp;

gotoroom(actp, getentryroom());
listroom(actp);
}

int ngetline(struct actor *actp, char line[], int max)
{
int r;
/* XXX assumes line-at-a-time telnet */
r = read(actp->remotefd, line, max-1);
if(r <= 0)
	return EOF;

line[r] = '\0';
return r;
}

#include <stdarg.h>

void output(struct actor *actp, char *msg, ...)
{
char tmpbuf[200];	/* XXX */
va_list argp;
va_start(argp, msg);
vsprintf(tmpbuf, msg, argp);
va_end(argp);
write(actp->remotefd, tmpbuf, strlen(tmpbuf));
}

void closeconnection(actor *actp)
{
actor **actpp;

fddequeue(actp->remotefd, 0);
close(actp->remotefd);

/* delete from list of all players */

for(actpp = &players; *actpp != NULL; actpp = &(*actpp)->next)
	{
	if(*actpp == actp)
		{
		*actpp = (*actpp)->next;
		break;
		}
	}

if(actp->contents != NULL)
	{
	/* leave actor's possessions in room */
	room *roomp = (room *)actp->container;	/* XXX assumes actor not in vehicle or container */
	object *lp2;
	for(lp2 = actp->contents; lp2->lnext != NULL; lp2 = lp2->lnext)
		;
	lp2->lnext = roomp->contents;
	roomp->contents = actp->contents;
	}

/* remove from game (wherever actor is) */
transferobject(actp, NULL);

delete actp;
}


#include <sys/time.h>
#include <sys/types.h>

fd_set fdsets[3], fdcopies[3];
int maxfd = 0;

#define Max(a, b) ((a) > (b) ? (a) : (b))

void
fdenqueue(int fd, int which)
{
FD_SET(fd, &fdsets[which]);
maxfd = Max(maxfd, fd);
}

void
fddequeue(int fd, int which)
{
FD_CLR(fd, &fdsets[which]);
/* decrement maxfd? */
}

void
selectwrapper()
{
int i;
struct timeval tv;

for(i = 0; i < 3; i++)
	fdcopies[i] = fdsets[i];

tv.tv_sec = 1;
tv.tv_usec = 0;

select(maxfd+1, &fdcopies[0], &fdcopies[1], &fdcopies[2], &tv);
}

int
fdready(int fd, int which)
{
return FD_ISSET(fd, &fdcopies[which]);
}
