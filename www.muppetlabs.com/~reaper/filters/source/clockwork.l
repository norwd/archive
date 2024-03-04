%{
/*   A Clockwork Orange	From jcp@gnu.ai.mit.edu Thu Nov 24 12:48:58 PST 1994
To compile: save this filter to aco.l
            lex aco.l
             cc -o aco lex.yy.c -ll
	To use:
                      aco < your_text_file 
			or   blah | aco
                    
a few cute examples of what the droogies on IRC are saying:

<joshua> it's easy once you, oh my little brothers can do it, doing blerp
blerp blerp the moloko plus the first time is maybe real savage like
<Lightning blerp blerp blerp> piglet2 writes some preachy real horrorshow cal..
<texx> apparently the moloko plus wasnt badiwad enough  thou globby bottle 
of cheap stinking chip-oil  little Alex was a serial killer but being blerp 
blerp blerp gay they wanted to make an even big burley bastardger case about it
<Amnesty> we are about ready for a bit of twenty-to-one to go to I was not
wakened when I gave orders for wakening. :)
<Amnesty> some preachytimes difficult to do if the nice warm vibraty feeling 
grumbling all through your guttiwuts is real horrorshow <grin>

*/

        char buf[128];
%}
%a 3000
%e 3000
%p 5000
%n 3000
%%
"come"         printf( "come and get one in the  yarbles" );
"mother"       printf( "mum" );
"girl"         printf( "weepy young devochka" );
"brother"      printf( "o my little brother" );
"good"         printf( "real horrorshow" );
"clear"        printf( "clear as an ummudied lake" );
"clean"        printf( "clear as  an azure sky of deepest summer" );
"strike"       printf( "out out out" );
"record"       printf( "fuzzie warbles" );
"hear"         printf( "hear angel trumpets  and devil trombones" );
"hard"         printf( "real savage like" );
"big"          printf( "big burley bastard" );
"job"          printf( "racket" );
"sorry"        printf( "appy polly loggies" );
"mouth"        printf( "shut your filthy hole" );
"sad"          printf( "real weepy and likesorry" );
"head"         printf( "pain in the gulliver" );
"indeed"       printf( "this sarcasm, if i may call it such, does not become you" );
"I am"         printf( "as I am your droog and leader" );
"sleep"        printf( "I was not wakened when I gave orders for wakening" );
"no more"      printf( "no more picking on Dim" );
"new"          printf( "what's all this about a new way" );
"car"          printf( "Durango 95" );
"feel better"  printf( "I was  cured alright" );
"violence"     printf( "he resisted his lawful arrestors" );
"fight"        printf( "a nozh scrap anyime you say" );
"balls"        printf( "great bolshy yarblockos" );
"ready"        printf( "ready for a bit of twenty-to-one" );

"top"          printf( "height of fashion" );
"see"          printf( "viddy" );
"God"          printf( "Bog" );
"book"         printf( "the property of the municipality" );
"teeth"        printf( "false zoobies" );
"hit"          printf( "tolchocked" );
"sing"         printf( "blerp blerp blerp" );
"you old"      printf( "globby bottle of cheap stinking chip-oil" ); 
"police"       printf( "millicents" );
"sex"          printf( "nice warm vibraty feeling  grumbling all through your guttiwuts" );
"key"          printf( "clack clack clakity clackclack" );
"little"       printf( "malenky bit" );
"word"         printf( "slavos" );
"eye"          printf( "glazzie" );
"friend"       printf( "droogie" );
"him"          printf( "alex" );
"her"          printf( "the devochka" );
"just"         printf( "just a matter of speech" );
"women"        printf( "baboochkas" );
"money"        printf( "pretty polly" );
%%
