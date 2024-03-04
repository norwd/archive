#define MAXOBJECTS 100

static struct object objects[MAXOBJECTS];
static int nobjects = 0;

struct object *
newobject(char *name)
{
struct object *objp;

if(nobjects >= MAXOBJECTS)
	{
	fprintf(stderr, "too many objects\n");
	exit(1);
	}

objp = &objects[nobjects++];

strcpy(objp->name, name);
objp->lnext = NULL;

return objp;
}
