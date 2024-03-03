/*
 *  Text-based dungeon/adventure game, for the
 *  UW Experimental College course in Intermediate C Programming
 *
 *  Copyright 1996-1999 Steve Summit
 *  scs@eskimo.com
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>

#define MAXNAME 20	/* maximum length of object or room name */

struct actor;
struct sentence;

class object
	{
public:
	object(const char *);
	~object(void);

	char name[MAXNAME];
	struct list *attrs;
	object *contents;
	object *container;
	int (*func)(struct actor *, struct object *, struct sentence *);
	char *script;
	object *lnext;			/* next in list of contained objects */
					/* (i.e. in this object's container) */
	};
#define Iscontainer(o) hasattr(o, "container")
#define Isopen(o) hasattr(o, "open")

class actor : public object
	{
public:
	actor();
	};

#define NEXITS 4

class room : public object
	{
public:
	room(const char *);

	room *exits[NEXITS];
	};

/* direction indices in exits array: */

#define NORTH		0
#define SOUTH		1
#define EAST		2
#define WEST		3

struct list
	{
	char *item;
	struct list *next;
	};

struct sentence
	{
	char *verb;
	struct object *object;
	char *preposition;
	struct object *xobject;	/* object of preposition */
	};

/* status return value for commands: */

#define FAILURE		0	/* command completed unsuccessfully */
#define SUCCESS		1	/* command completed successfully */
#define CONTINUE	2	/* command not completed */
#define ERROR		3	/* internal error */

extern int parseline(struct actor *actor, char *, struct sentence *);
extern docommand(struct actor *, struct sentence *);

extern int readdatafile(void);
extern int dumpdata(char *);

extern struct object *newobject(char *);
extern struct object *findobject(struct actor *, char *);
extern int contains(struct object *, struct object *);
extern int takeobject(struct actor *, struct object *);
extern int dropobject(struct actor *, struct object *);
extern int putobject(struct actor *, struct object *, struct object *);
extern int transferobject(object *, object *);
extern void listobjects(actor *, object *);
extern void dumpobjects(FILE *);
extern int obj_indexof(struct object *);
extern int hasattr(struct object *, char *);
extern void setattr(struct object *, char *);
extern void unsetattr(struct object *, char *);

extern struct room *newroom(char *);
extern struct room *findroom(char *);
extern struct room *getentryroom(void);
void listroom(struct actor *);
extern int gotoroom(struct actor *, struct room *);
extern void dumprooms(FILE *);


extern int interp(struct actor *, struct object *, struct sentence *);

#endif
