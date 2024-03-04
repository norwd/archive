%{
/*    Burroughs-esque Naked Lunch filter	From jcp@gnu.ai.mit.edu Thu Nov 24 12:48:58 PST 1994
            To compile: lex nl.l

                        cc -o nl lex.yy.c -ll
        */

        char buf[128];
%}
%a 3000
%e 3000
%p 5000
%n 3000
%%
" bag "		printf( " enema ");
" blood "	printf( " blood brothers in the same dirty needle ");
" blood "	printf( " purulent stringy discharge streaked with blood and putrid lymph ");
" blue "	printf( " supra blue gravitational fields ");
" boy"		printf( " dancing boys strip-tease with intestines");
" cloth"	printf( " handkerchief with come on it");
" control "	printf( " complete hypnotic control - the subject will come at his whistle, shit on the floor ");
" cop "		printf( " soft-spoken country sheriffs with something black and menacing in old eyes color of a faded grey flannel shirt ");
" cut "		printf( " perform appendectomy with a rusty sardine can on ");
" dick "	printf( " narcotics dick in a white trench coat ");
" doctor "	printf( " croaker ");
" down "	printf( " down through condoms and orange peels, mosaic of floating newspapers, down into the silent black ooze with gangsters in concrete, and pistols pounded flat to avoid the probing finger of prurient ballistics experts ");
" drugs "	printf( " drugs remain am essential tool of the interrogator in his assault on the subject's personal identity ");
" fat "		printf( " fat-removing molecule of junk ");
" feel "	printf( " feel that suppurated swelling in my groin where I got the lymphogranulomas ");
" finger "	printf( " probing finger of prurient ballistic experts ");
" girl"		printf( " gash");
" go "		printf( " dart up your prick or your asshole or a woman's cunt faute de mieux ");
" hole "	printf( " obscene, festering mouth waiting for unspeakable congress with the dropper ");
" line "	printf( " cord of rancid jissom ");
" look "	printf( " look down at my filthy trousers, haven't been changed in months ");
" LSD "		printf( " mescaline, LSD6, deteriorated adrenalin and harmaline ");
" many "	printf( " many a latent homosexual was carried out in a straightjacket when they planted vaseline in his ass ");
" milk "	printf( " Klim-a horrible form of powdered milk tasting like rancid chalk ");
" morning "	printf( " junk-sick morning ");
" person"	printf( " most humiliating search of his naked person on which they make sneering and derogatory comment");
" police "	printf( " nigger-killing sheriffs ");
" president "	printf( " President is a junky but can't take it directly because of his position ");
" push "	printf( " push my hand severing the patient's femoral artery ");
" replace "	printf( " cut the cocaine with Saniflush ");
" round "	printf( " round, disk mouth lined with sensitive, erectile hairs ");
" sex "		printf( " perform all kinda awful sex acts in return for junk ");
" shit "	printf( " shit in his teeth giving rise to stubborn cases of halitosis ");
" stuff "	printf( " orgone ");
" them "	printf( " phantom porters sweeping out dusty halls with a slow old man's hand ");
" they "	printf( " spectral janitors, grey as ashes ");
" took "	printf( " stole an opium suppository out of my grandmother's ass ");
" touch "	printf( " palpate my internal haemorrhoids ");
" tube "	printf( " tube of vaseline ");
" waiting "	printf( " waiting for the Man ");
" wet "		printf( " wet all over like with green slime ");
" woman "	printf( " female agent who forgot her real identity ");
" women "	printf( " women stick severed genitals in their cunts, grind, bump and flick ");
"gays "		printf( " homosexual tourists with horrible knowing smiles showing the Nodic skull beneath in double exposure ");
"in the "	printf( "in the coal bin all cocks are alike ");
"mother"	printf( "mum");
%%
