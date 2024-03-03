#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "game.h"

/*
 *  Interpret an object script.
 *  For now, only handles commands of the form
 *	<verb> <object> WITH <tool>
 *  The script may be attached to either the oblect or the tool.
 *
 *  Algorithm: Scan through script, searching for entry point
 *  matching verb.  If not found, we can't handle this verb;
 *  return CONTINUE so that others may have a go.
 *  If found, proceed to interpret (that portion of) script.
 */

/* lexter token values: */

#define EOFTOK		(-1)
#define ERRORTOK	0
#define NUMBER		1
#define STRING		2
#define ENTRY		3
#define MESSAGE		4
#define RETURN		5
#define CSETOBJSTATE	6
#define SETOBJSTATE	7
#define CLROBJSTATE	8
#define SETTOOLSTATE	9
#define CLRTOOLSTATE	10
#define CHKOBJQUAL	11
#define CHKTOOLQUAL	12
#define CHKTOOLSTATE	13
#define CHKNTOOLSTATE	14

static char lexval[100];		/* value return from lexer */

static void lexinit(char *);
static int lex(void);

interp(struct actor *actp, struct object *object,
					struct sentence *cmd)
{
int tok;
char *attr;

if(cmd->preposition == NULL || strcmp(cmd->preposition, "with") != 0
					|| cmd->xobject == NULL)
	{
	/* not a sentence we can handle */
	return CONTINUE;
	}

if(object->script == NULL)
	return CONTINUE;

lexinit(object->script);

/* search for entry point */

while((tok = lex()) != EOFTOK)
	{
	if(tok != ENTRY)
		continue;
	tok = lex();
	if(tok != STRING)
		{
		fprintf(stderr, "error in script\n");
		return ERROR;
		}
	if(strcmp(lexval, cmd->verb) == 0)
		break;
	}

if(tok == EOFTOK)
	return CONTINUE;

/* found it; now interpret */

while((tok = lex()) != EOFTOK)
	{
	/*
	 *  clumsy common case --
	 *  get attribute argument for attr-checking/setting ops
	 */

	if(tok == CSETOBJSTATE || tok == SETOBJSTATE || tok == CLROBJSTATE
		|| tok == SETTOOLSTATE || tok == CLRTOOLSTATE || tok == CHKOBJQUAL
		|| tok == CHKTOOLQUAL || tok == CHKTOOLSTATE || tok == CHKNTOOLSTATE)
		{
		int tok2 = lex();
		if(tok2 != STRING)
			{
			fprintf(stderr, "error in script\n");
			return ERROR;
			}
		attr = lexval;
		}

	switch(tok)
		{
		case CSETOBJSTATE:
			/* set an attribute of the object, if it isn't set already */
			if(hasattr(cmd->object, attr))
				{
				printf("The %s is already %s.\n",
					cmd->object->name, attr);
				return FAILURE;
				}
			else	{
				setattr(cmd->object, attr);
				}
			break;

		case SETOBJSTATE:
			/* set an attribute of the object */
			setattr(cmd->object, attr);
			break;

		case CLROBJSTATE:
			/* clear an attribute of the object */
			unsetattr(cmd->object, attr);
			break;

		case SETTOOLSTATE:
			/* set an attribute of the tool */
			setattr(cmd->xobject, attr);
			break;

		case CLRTOOLSTATE:
			/* clear an attribute of the tool */
			unsetattr(cmd->xobject, attr);
			break;

		case CHKOBJQUAL:
			/* check a permanent attribute of the object */
			if(!hasattr(cmd->object, attr))
				{
				printf("You can't %s the %s.\n",
					cmd->verb, cmd->object->name);
				return FAILURE;
				}
			break;

		case CHKTOOLQUAL:
			/* check a permanent attribute of the tool */
			if(!hasattr(cmd->xobject, attr))
				{
				printf("You can't %s things with a %s.\n",
					cmd->verb, cmd->xobject->name);
				return FAILURE;
				}
			break;

		case CHKTOOLSTATE:
			/* check a temporary attribute of the tool */
			if(!hasattr(cmd->xobject, attr))
				{
				printf("The %s isn't %s enough to %s.\n",
					cmd->xobject->name, attr, cmd->verb);
				return FAILURE;
				}
			break;

		case CHKNTOOLSTATE:
			/* check a negated temporary attribute of the tool */
			if(hasattr(cmd->xobject, attr))
				{
				printf("The %s is too %s to %s.\n",
					cmd->xobject->name, attr, cmd->verb);
				return FAILURE;
				}
			break;

		case MESSAGE:
			/* print a message */
			tok = lex();
			if(tok != STRING)
				{
				fprintf(stderr, "error in script\n");
				return ERROR;
				}
			printf("%s\n", lexval);
			break;

		case ERRORTOK:
			fprintf(stderr, "error in script\n");
			return ERROR;

		case RETURN:
			/* return from the script */
			tok = lex();
			if(tok != NUMBER)
				{
				fprintf(stderr, "error in script\n");
				return ERROR;
				}
			return atoi(lexval);
		}
	}

/* script completed without internal RETURN */

return SUCCESS;
}

static char *lexp;

/* Initialize the lexical analyzer with a new script. */

static void
lexinit(char *script)
{
lexp = script;
}

/*
 *  Lexical analyzer for scripts.
 *  Returns EOFTOK, STRING, NUMBER, or various keyword tokens.
 *  For STRING and NUMBER, particular value is returned
 *  (always as string) in file-global variable lexval.
 */

static int
lex(void)
{
char *p = lexval;

while(*lexp == ' ' || *lexp == '\t' || *lexp == '\n')
	lexp++;

if(isalpha(*lexp))
	{
	while(isalnum(*lexp))
		*p++ = *lexp++;
	*p = '\0';
	if(strcmp(lexval, "entry") == 0)
		return ENTRY;
	else if(strcmp(lexval, "csetobjstate") == 0)
		return CSETOBJSTATE;
	else if(strcmp(lexval, "setobjstate") == 0)
		return SETOBJSTATE;
	else if(strcmp(lexval, "clrobjstate") == 0)
		return CLROBJSTATE;
	else if(strcmp(lexval, "settoolstate") == 0)
		return SETTOOLSTATE;
	else if(strcmp(lexval, "clrtoolstate") == 0)
		return CLRTOOLSTATE;
	else if(strcmp(lexval, "chkobjqual") == 0)
		return CHKOBJQUAL;
	else if(strcmp(lexval, "chktoolqual") == 0)
		return CHKTOOLQUAL;
	else if(strcmp(lexval, "chktoolstate") == 0)
		return CHKTOOLSTATE;
	else if(strcmp(lexval, "chkntoolstate") == 0)
		return CHKNTOOLSTATE;
	else if(strcmp(lexval, "message") == 0)
		return MESSAGE;
	else if(strcmp(lexval, "return") == 0)
		return RETURN;
	else	return ERRORTOK;
	}
else if(isdigit(*lexp))
	{
	while(isdigit(*lexp))
		*p++ = *lexp++;
	*p = '\0';
	return NUMBER;
	}
else if(*lexp == '"')
	{
	lexp++;
	while(*lexp != '"' && *lexp != '\0')
		*p++ = *lexp++;
	if(*lexp != '\0')
		lexp++;
	*p = '\0';
	return STRING;
	}
else if(*lexp == '\0')
	return EOFTOK;
else	return ERRORTOK;
}
