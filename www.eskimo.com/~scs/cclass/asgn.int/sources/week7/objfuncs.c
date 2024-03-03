#include <stdio.h>
#include <string.h>
#include "game.h"
#include "cmdtab.h"

int hammerfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int toolfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int cutfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int playfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int lockfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int keyfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int showerfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int swordfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int wastebarrelfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);
int hazmatsuitfunc(struct actor *player, struct object *objp,
					struct sentence *cmd);

int hammerfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "break") != 0)
		return CONTINUE;
	if(objp != cmd->xobject)
		return CONTINUE;

	if(cmd->object == NULL)
		{
		printf("You must tell me what to break.\n");
		return FAILURE;
		}
	if(!contains(player->contents, cmd->xobject))
		{
		printf("You have no %s.\n", cmd->xobject->name);
		return FAILURE;
		}

	setattr(cmd->object, "broken");
	printf("Oh, dear.  Now the %s is broken.\n", cmd->object->name);

	return SUCCESS;
}

int toolfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "fix") != 0)
		return CONTINUE;
	if(objp != cmd->xobject)
		return CONTINUE;

	if(cmd->object == NULL)
		{
		printf("You must tell me what to fix.\n");
		return FAILURE;
		}
	if(!hasattr(cmd->object, "broken"))
		{
		printf("The %s is not broken.\n", cmd->object->name);
		return FAILURE;
		}
	if(!contains(player->contents, cmd->xobject))
		{
		printf("You have no %s.\n", cmd->xobject->name);
		return FAILURE;
		}

	unsetattr(cmd->object, "broken");
	printf("Somehow you manage to fix the %s.\n", cmd->object->name);

	return SUCCESS;
}

int cutfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "cut") != 0)
		return CONTINUE;
	if(objp != cmd->xobject)
		return CONTINUE;

	if(cmd->object == NULL)
		{
		printf("You must tell me what to cut.\n");
		return FAILURE;
		}
	if(!contains(player->contents, cmd->xobject))
		{
		printf("You have no %s.\n", cmd->xobject->name);
		return FAILURE;
		}
	if(!hasattr(cmd->object, "soft"))
		{
		printf("I don't think you can cut the %s with the %s.\n",
					cmd->object->name, cmd->xobject->name);
		return FAILURE;
		}

	setattr(cmd->object, "cutinhalf");

	printf("The %s is now cut in two.\n", cmd->object->name);

	return SUCCESS;
}

int playfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "play") != 0)
		return CONTINUE;
	if(objp != cmd->object)
		return CONTINUE;

	if(!hasattr(cmd->object, "immobile"))
		{
		if(!contains(player->contents, cmd->object))
			{
			printf("You don't have the %s.\n", cmd->object->name);
			return FAILURE;
			}
		}

	printf("You're not quite ready for Carnegie hall,\n");
	printf("but you do manage to force out a recognizable tune.\n");

	return SUCCESS;
}

int lockfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "lock") != 0 && strcmp(cmd->verb, "unlock") != 0)
		return CONTINUE;
	if(objp != cmd->object)
		return CONTINUE;
	if(cmd->preposition == NULL || strcmp(cmd->preposition, "with") != 0 ||
			cmd->xobject == NULL)
		{
		printf("You must tell me what to %s with.\n", cmd->verb);
		return FAILURE;
		}
	if(!hasattr(cmd->object, "lock"))
		{
		printf("You can't lock the %s.\n", cmd->object->name);
		return FAILURE;
		}
	if(Isopen(cmd->object))
		{
		printf("The %s is open.\n", cmd->object->name);
		return FAILURE;
		}
	if(!contains(player->contents, cmd->xobject))
		{
		printf("You don't have the %s.\n", cmd->xobject->name);
		return FAILURE;
		}
	if(!hasattr(cmd->xobject, "key"))
		{
		printf("The %s won't %s the %s.\n",
				cmd->xobject->name, cmd->verb, objp->name);
		return FAILURE;
		}

	if(strcmp(cmd->verb, "lock") == 0)
		{
		if(hasattr(cmd->object, "locked"))
			{
			printf("The %s is already locked.\n", cmd->object->name);
			return FAILURE;
			}

		setattr(cmd->object, "locked");
		printf("The %s is now locked.\n", cmd->object->name);
		return SUCCESS;
		}
	else if(strcmp(cmd->verb, "unlock") == 0)
		{
		if(!hasattr(cmd->object, "locked"))
			{
			printf("The %s is already unlocked.\n", cmd->object->name);
			return FAILURE;
			}

		unsetattr(cmd->object, "locked");
		printf("The %s is now unlocked.\n", cmd->object->name);

		return SUCCESS;
		}

	/* shouldn't get here */
	return CONTINUE;
}

int keyfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "lock") != 0 && strcmp(cmd->verb, "unlock") != 0)
		return CONTINUE;
	if(objp != cmd->xobject)
		return CONTINUE;
	if(cmd->object == NULL)
		{
		printf("You must tell me what to %s.\n", cmd->verb);
		return FAILURE;
		}
	if(!hasattr(cmd->object, "lock"))
		{
		printf("You can't %s the %s.\n", cmd->verb, cmd->object->name);
		return FAILURE;
		}
	if(Isopen(cmd->object))
		{
		printf("The %s is open.\n", cmd->object->name);
		return FAILURE;
		}
	if(!contains(player->contents, cmd->xobject))
		{
		printf("You don't have the %s.\n", cmd->xobject->name);
		return FAILURE;
		}

	if(strcmp(cmd->verb, "lock") == 0)
		{
		if(hasattr(cmd->object, "locked"))
			{
			printf("The %s is already locked.\n", cmd->object->name);
			return FAILURE;
			}

		setattr(cmd->object, "locked");
		printf("The %s is now locked.\n", cmd->object->name);
		return SUCCESS;
		}
	else if(strcmp(cmd->verb, "unlock") == 0)
		{
		if(!hasattr(cmd->object, "locked"))
			{
			printf("The %s is already unlocked.\n", cmd->object->name);
			return FAILURE;
			}

		unsetattr(cmd->object, "locked");
		printf("The %s is now unlocked.\n", cmd->object->name);

		return SUCCESS;
		}

	/* shouldn't get here */
	return CONTINUE;
}

int showerfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "take") != 0)
		return CONTINUE;
	if(objp != cmd->object)
		return CONTINUE;

	printf("After spending 20 luxurious minutes in the shower,\n");
	printf("singing three full-length show tunes, and using up\n");
	printf("all the hot water, you emerge clean and refreshed.\n");

	return SUCCESS;
}

int swordfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "take") != 0)
		return CONTINUE;
	if(objp != cmd->object)
		return CONTINUE;
	printf("As you pick it up, the sword briefly glows blue.\n");
	return CONTINUE;
}

int wastebarrelfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	struct object *hazmatsuit;

	if(strcmp(cmd->verb, "take") != 0)
		return CONTINUE;
	if(objp != cmd->object)
		return CONTINUE;

	hazmatsuit = findobject(player, "suit");
	if(hazmatsuit == NULL || !contains(player->contents, hazmatsuit))
		{
		printf("The container is far too dangerous to pick up.\n");
		return FAILURE;
		}

	return CONTINUE;
}

int hazmatsuitfunc(struct actor *player, struct object *objp,
					struct sentence *cmd)
{
	if(strcmp(cmd->verb, "wear") != 0)
		return CONTINUE;
	if(objp != cmd->object)
		return CONTINUE;
	/* implicitly pick up, if necessary */
	if(!contains(player->contents, cmd->object))
		{
		if(!takeobject(player, cmd->object))
			return FAILURE;
		}
	printf("You feel much safer wearing the bright yellow Hazmat suit.\n");
	return SUCCESS;
}


struct cmdtab objfuncs[] =
	{
	"hammerfunc",	hammerfunc,
	"toolfunc",	toolfunc,
	"cutfunc",	cutfunc,
	"playfunc",	playfunc,
	};

#define Sizeofarray(a) (sizeof(a) / sizeof(a[0]))

int nobjfuncs = Sizeofarray(objfuncs);
