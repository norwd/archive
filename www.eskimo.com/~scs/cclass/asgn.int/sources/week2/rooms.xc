#define MAXROOMS 100

static struct room rooms[MAXROOMS];
static int nrooms = 0;

struct room *
newroom(char *name)
{
struct room *roomp;
int i;

if(nrooms >= MAXROOMS)
	{
	fprintf(stderr, "too many rooms\n");
	exit(1);
	}

roomp = &rooms[nrooms++];

strcpy(roomp->name, name);
roomp->contents = NULL;
for(i = 0; i < NEXITS; i++)
	roomp->exits[i] = NULL;

return roomp;
}

struct room *
findroom(char *name)
{
int i;

for(i = 0; i < nrooms; i++)
	{
	if(strcmp(rooms[i].name, name) == 0)
		return &rooms[i];
	}

return NULL;
}

struct room *
getentryroom(void)
{
if(nrooms == 0)
	return NULL;
return &rooms[0];	/* temporary */
}
