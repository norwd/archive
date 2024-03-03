struct cmdtab
	{
	char *name;
	int (*func)();
	};

extern struct cmdtab *findcmd(char *, struct cmdtab [], int);
