
%e 2000
%p 5000
%n 1000
%k 500
%a 4000
%o 2000
BW [      ]
EW [      .,;!?]

%{
     char buf[128];
	int censor_count;
	int line_count;
%}

%%
"[Ff][Uu][Cc][Kk] "		go_s();
[Ff][Uu][Cc][Kk][Ee][Dd]	go();
[Ff][Uu][Cc][Kk][Ii][Nn][Gg]	go();
"[Ff][Uu][Cc][Kk][Ii][Nn]'"	go();
[Ff][Uu][Cc][Kk]		go();
"[Dd][Aa][Mm][Nn] "		go_s();
[Dd][Aa][Mm][Nn][Ee][Dd]	go();
[Dd][Aa][Mm][Nn][Ii][Nn][Gg]	go();
[Dd][Aa][Mm][Nn]		go();
[Dd][Aa][Mm][Mm][Ii][Tt]	go();
"[Ss][Hh][Ii][Tt] "		go_s();
[Ss][Hh][Ii][Tt][Tt][Yy]	go();
[Ss][Hh][Ii][Tt]		go();
"[Gg][Oo][Dd] "			go_s();
[Gg][Oo][Dd][Dd][Aa][Mm][Nn]	go();
[Gg][Oo][Dd][Dd][Aa][Mm]	go();
[Gg][Oo][Dd][Aa][Mm][Nn]	go();
[Gg][Oo][Dd]			go();
"[Aa][Ss][Ss] "			go_s();
[Aa][Ss][Ss]-[Hh][Oo][Ll][Ee]	go();
[Aa][Ss][Ss][Hh][Oo][Ll][Ee]	go();
[Aa][Ss][Ss]			go();
"[Aa][Rr][Ss][Ee] "		go_s();
[Aa][Rr][Ss][Ee][Hh][Oo][Ll][Ee]	go();
[Aa][Rr][Ss][Ee]-[Hh][Oo][Ll][Ee]	go();
[Aa][Rr][Ss][Ee]		go();
"[Pp][Ii][Ss][Ss] "		go_s();
[Pp][Ii][Ss][Ss][Ee][Dd]	go();
[Pp][Ii][Ss][Ss]		go();
[Nn][Ii][Gg][Gg][Aa][Rr][Dd][Ll][Yy]	go();

.              printf(yytext);
\n             eolfunc();

%%

/* Censortron v0.1 */
/* Ian Johnston */
/* May 28, 1996 */

/* This is in the public domain. Do with it as you will. */

go()
{
	printf("[Censored]");
	censor_count++;
}

go_s()
{
	printf("[Censored] ");
	censor_count++;
}

eolfunc()
{
	printf("\n");
	line_count++;
}

main()
{
char *line; 
char * word_c;
char * word_l;

    while(line = (char *) yylex())
	continue;

	if (censor_count == 1) { word_c = "word"; }
	else { word_c = "words"; }

	word_l = (line_count == 1) ? "line" : "lines";

	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("Censortron found %d offensive %s in %d %s.\n", 
		censor_count, word_c, line_count, word_l);
	if ((line_count/censor_count) < 10)
	{
		printf("Please clean up your language.\n");
	}
	if ((line_count/censor_count) < 5)
	{
		printf("Your account details have been sent to the authorities.\n");
	}
}

