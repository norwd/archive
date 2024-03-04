else if(strcmp(verb, "open") == 0)
	{
	if(objp == NULL)
		{
		printf("You must tell me what to open.\n");
		return FALSE;
		}
	if(Isopen(objp))
		{
		printf("The %s is already open.\n", objp->name);
		return FALSE;
		}
	if(!(objp->attrs & CLOSABLE))
		{
		printf("You can't open the %s.\n", objp->name);
		return FALSE;
		}
	objp->attrs |= OPEN;
	printf("The %s is now open.\n", objp->name);
	}
else if(strcmp(verb, "close") == 0)
	{
	if(objp == NULL)
		{
		printf("You must tell me what to close.\n");
		return FALSE;
		}
	if(!(objp->attrs & CLOSABLE))
		{
		printf("You can't close the %s.\n", objp->name);
		return FALSE;
		}
	if(!Isopen(objp))
		{
		printf("The %s is already closed.\n", objp->name);
		return FALSE;
		}
	objp->attrs &= ~OPEN;
	printf("The %s is now closed.\n", objp->name);
	}
else if(strcmp(verb, "put") == 0)
	{
	if(objp == NULL)
		{
		printf("You must tell me what to put.\n");
		return FALSE;
		}
	if(!contains(player->contents, objp))
		{
		printf("You don't have the %s.\n", objp->name);
		return FALSE;
		}
	if(cmd->preposition == NULL || strcmp(cmd->preposition, "in") != 0 ||
			cmd->xobject == NULL)
		{
		printf("You must tell me where to put the %s.\n",
							objp->name);
		return FALSE;
		}
	if(!Iscontainer(cmd->xobject))
		{
		printf("You can't put things in the %s.\n",
							cmd->xobject->name);
		return FALSE;
		}
	if((cmd->xobject->attrs & CLOSABLE) && !Isopen(cmd->xobject))
		{
		printf("The %s is closed.\n", cmd->xobject->name);
		return FALSE;
		}
	if(!putobject(player, objp, cmd->xobject))
		{
		/* shouldn't happen */
		printf("You can't put the %s in the %s!\n",
			objp->name, cmd->xobject->name);
		return FALSE;
		}
	printf("Now the %s is in the %s.\n",
			objp->name, cmd->xobject->name);
	}
