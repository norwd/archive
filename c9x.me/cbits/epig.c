/*% cc % -o #
 * epig
 * Prints a random epigram
 * from Alan Perlis to the
 * screen, the algorithm
 * used is remarkable.
 * Usefully piped into fmt
 * for your initialization
 * scripts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern char *all[];

int main()
{
	int n;
	char *epig;
	char **p;

	srand(time(0));
	for (p=all, n=1; *p; p++, n++)
		if (rand() % n == 0)
			epig = *p;
	puts(epig);
	return 0;
}

/*

      Epigrams on Programming
      Alan J. Perlis
      Yale University

The phenomena surrounding computers are diverse and
yield a surprisingly rich base for launching metaphors
at individual and group activities. Conversely, classical
human endeavors provide an inexhaustible source of metaphor
for those of us who are in labor within computation. Such
relationships between society and device are not new,
but the incredible growth of the computer's influence
(both real and implied) lends this symbiotic dependency
a vitality like a gangly youth growing out of his clothes
within an endless puberty.

The epigrams that follow attempt to capture some of
the dimensions of this traffic in imagery that sharpens,
focuses, clarifies, enlarges and beclouds our view of this
most remarkable of all mans' artifacts, the computer.

*/

char *all[] = {

"One man's constant is another man's variable.",

"Functions delay binding: data structures induce b"
"inding. Moral: Structure data late in the programm"
"ing process.",

"Syntactic sugar causes cancer of the semi-colons.",

"Every program is a part of some other program and"
" rarely fits.",

"If a program manipulates a large amount of data, "
"it does so in a small number of ways.",

"Symmetry is a complexity reducing concept (co-rou"
"tines include sub-routines); seek it everywhere.",

"It is easier to write an incorrect program than u"
"nderstand a correct one.",

"A programming language is low level when its prog"
"rams require attention to the irrelevant.",

"It is better to have 100 functions operate on one"
" data structure than 10 functions on 10 data struc"
"tures.",

"Get into a rut early: Do the same processes the s"
"ame way. Accumulate idioms. Standardize. The only "
"difference (!) between Shakespeare and you was the"
" size of his idiom list - not the size of his voca"
"bulary.",

"If you have a procedure with 10 parameters, you p"
"robably missed some.",

"Recursion is the root of computation since it tra"
"des description for time.",

"If two people write exactly the same program, eac"
"h should be put in micro-code and then they certai"
"nly won't be the same.",

"In the long run every program becomes rococco - t"
"hen rubble.",

"Everything should be built top-down, except the f"
"irst time.",

"Every program has (at least) two purposes: the on"
"e for which it was written and another for which i"
"t wasn't.",

"If a listener nods his head when you're explainin"
"g your program, wake him up.",

"A program without a loop and a structured variabl"
"e isn't worth writing.",

"A language that doesn't affect the way you think "
"about programming, is not worth knowing.",

"Wherever there is modularity there is the potenti"
"al for misunderstanding: Hiding information implie"
"s a need to check communication.",

"Optimization hinders evolution.",

"A good system can't have a weak command language."
"",

"To understand a program you must become both the "
"machine and the program.",

"Perhaps if we wrote programs from childhood on, a"
"s adults we'd be able to read them.",

"One can only display complex information in the m"
"ind. Like seeing, movement or flow or alteration o"
"f view is more important than the static picture, "
"no matter how lovely.",

"There will always be things we wish to say in our"
" programs that in all known languages can only be "
"said poorly.",

"Once you understand how to write a program get so"
"meone else to write it.",

"Around computers it is difficult to find the corr"
"ect unit of time to measure progress. Some cathedr"
"als took a century to complete. Can you imagine th"
"e grandeur and scope of a program that would take "
"as long?",

"For systems, the analogue of a face-lift is to ad"
"d to the control graph an edge that creates a cycl"
"e, not just an additional node.",

"In programming, everything we do is a special cas"
"e of something more general - and often we know it"
" too quickly.",

"Simplicity does not precede complexity, but follo"
"ws it.",

"Programmers are not to be measured by their ingen"
"uity and their logic but by the completeness of th"
"eir case analysis.",

"The 11th commandment was \"Thou Shalt Compute\" o"
"r \"Thou Shalt Not Compute\" - I forget which.",

"The string is a stark data structure and everywhe"
"re it is passed there is much duplication of proce"
"ss. It is a perfect vehicle for hiding information"
".",

"Everyone can be taught to sculpt: Michelangelo wo"
"uld have had to be taught how not to. So it is wit"
"h the great programmers.",

"The use of a program to prove the 4-color theorem"
" will not change mathematics - it merely demonstra"
"tes that the theorem, a challenge for a century, i"
"s probably not important to mathematics.",

"The most important computer is the one that rages"
" in our skulls and ever seeks that satisfactory ex"
"ternal emulator. The standardization of real compu"
"ters would be a disaster - and so it probably won'"
"t happen.",

"Structured Programming supports the law of the ex"
"cluded muddle.",

"Re graphics: A picture is worth 10K words - but o"
"nly those to describe the picture. Hardly any sets"
" of 10K words can be adequately described with pic"
"tures.",

"There are two ways to write error-free programs; "
"only the third one works.",

"Some programming languages manage to absorb chang"
"e, but withstand progress.",

"You can measure a programmer's perspective by not"
"ing his attitude on the continuing vitality of FOR"
"TRAN.",

"In software systems it is often the early bird th"
"at makes the worm.",

"Sometimes I think the only universal in the compu"
"ting field is the fetch-execute-cycle.",

"The goal of computation is the emulation of our s"
"ynthetic abilities, not the understanding of our a"
"nalytic ones.",

"Like punning, programming is a play on words.",

"As Will Rogers would have said, \"There is no suc"
"h thing as a free variable.\"",

"The best book on programming for the layman is \""
"Alice in Wonderland\"; but that's because it's the"
" best book on anything for the layman.",

"Giving up on assembly language was the apple in o"
"ur Garden of Eden: Languages whose use squanders m"
"achine cycles are sinful. The LISP machine now per"
"mits LISP programmers to abandon bra and fig-leaf."
"",

"When we understand knowledge-based systems, it wi"
"ll be as before - except our finger-tips will have"
" been singed.",

"Bringing computers into the home won't change eit"
"her one, but may revitalize the corner saloon.",

"Systems have sub-systems and sub-systems have sub"
"-systems and so on ad infinitum - which is why we'"
"re always starting over.",

"So many good ideas are never heard from again onc"
"e they embark in a voyage on the semantic gulf.",

"Beware of the Turing tar-pit in which everything "
"is possible but nothing of interest is easy.",

"A LISP programmer knows the value of everything, "
"but the cost of nothing.",

"Software is under a constant tension. Being symbo"
"lic it is arbitrarily perfectible; but also it is "
"arbitrarily changeable.",

"It is easier to change the specification to fit t"
"he program than vice versa.",

"Fools ignore complexity. Pragmatists suffer it. S"
"ome can avoid it. Geniuses remove it.",

"In English every word can be verbed. Would that i"
"t were so in our programming languages.",

"Dana Scott is the Church of the Lattice-Way Saint"
"s.",

"In programming, as in everything else, to be in e"
"rror is to be reborn.",

"In computing, invariants are ephemeral.",

"When we write programs that \"learn\", it turns o"
"ut we do and they don't.",

"Often it is means that justify ends: Goals advanc"
"e technique and technique survives even when goal "
"structures crumble.",

"Make no mistake about it: Computers process numbe"
"rs - not symbols. We measure our understanding (an"
"d control) by the extent to which we can arithmeti"
"ze an activity.",

"Making something variable is easy. Controlling du"
"ration of constancy is the trick.",

"Think of all the psychic energy expended in seeki"
"ng a fundamental distinction between \"algorithm\""
" and \"program\".",

"If we believe in data structures, we must believe"
" in independent (hence simultaneous) processing. F"
"or why else would we collect items within a struct"
"ure? Why do we tolerate languages that give us the"
" one without the other?",

"In a 5 year period we get one superb programming "
"language. Only we can't control when the 5 year pe"
"riod will begin.",

"Over the centuries the Indians developed sign lan"
"guage for communicating phenomena of interest. Pro"
"grammers from different tribes (FORTRAN, LISP, ALG"
"OL, SNOBOL, etc.) could use one that doesn't requi"
"re them to carry a blackboard on their ponies.",

"Documentation is like term insurance: It satisfie"
"s because almost no one who subscribes to it depen"
"ds on its benefits.",

"An adequate bootstrap is a contradiction in terms"
".",

"It is not a language's weaknesses but its strengt"
"hs that control the gradient of its change: Alas, "
"a language never escapes its embryonic sac.",

"It is possible that software is not like anything"
" else, that it is meant to be discarded: that the "
"whole point is to always see it as soap bubble?",

"Because of its vitality, the computing field is a"
"lways in desperate need of new cliches: Banality s"
"oothes our nerves.",

"It is the user who should parametrize procedures,"
" not their creators.",

"The cybernetic exchange between man, computer and"
" algorithm is like a game of musical chairs: The f"
"rantic search for balance always leaves one of the"
" three standing ill at ease.",

"If your computer speaks English it was probably m"
"ade in Japan.",

"A year spent in artificial intelligence is enough"
" to make one believe in God.",

"Prolonged contact with the computer turns mathema"
"ticians into clerks and vice versa.",

"In computing, turning the obvious into the useful"
" is a living definition of the word \"frustration\""
".",

"We are on the verge: Today our program proved Fer"
"mat's next-to-last theorem!",

"What is the difference between a Turing machine a"
"nd the modern computer? It's the same as that betw"
"een Hillary's ascent of Everest and the establishm"
"ent of a Hilton hotel on its peak.",

"Motto for a research laboratory: What we work on "
"today, others will first think of tomorrow.",

"Though the Chinese should adore APL, it's FORTRAN"
" they put their money on.",

"We kid ourselves if we think that the ratio of pr"
"ocedure to data in an active data-base system can "
"be made arbitrarily small or even kept small.",

"We have the mini and the micro computer. In what "
"semantic niche would the pico computer fall?",

"It is not the computer's fault that Maxwell's equ"
"ations are not adequate to design the electric mot"
"or.",

"One does not learn computing by using a hand calc"
"ulator, but one can forget arithmetic.",

"Computation has made the tree flower.",

"The computer reminds one of Lon Chaney - it is th"
"e machine of a thousand faces.",

"The computer is the ultimate polluter. Its feces "
"are indistinguishable from the food it produces.",

"When someone says \"I want a programming language"
" in which I need only say what I wish done,\" give"
" him a lollipop.",

"Interfaces keep things tidy, but don't accelerate"
" growth: Functions do.",

"Don't have good ideas if you aren't willing to be"
" responsible for them.",

"Computers don't introduce order anywhere as much "
"as they expose opportunities.",

"When a professor insists computer science is X bu"
"t not Y, have compassion for his graduate students"
".",

"In computing, the mean time to failure keeps gett"
"ing shorter.",

"In man-machine symbiosis, it is man who must adju"
"st: The machines can't.",

"We will never run out of things to program as lon"
"g as there is a single program around.",

"Dealing with failure is easy: Work hard to improv"
"e. Success is also easy to handle: You've solved t"
"he wrong problem. Work hard to improve.",

"One can't proceed from the informal to the formal"
" by formal means.",

"Purely applicative languages are poorly applicabl"
"e.",

"The proof of a system's value is its existence.",

"You can't communicate complexity, only an awarene"
"ss of it.",

"It's difficult to extract sense from strings, but"
" they're the only communication coin we can count "
"on.",

"The debate rages on: Is PL/I Bachtrian or Dromeda"
"ry?",

"Whenever two programmers meet to criticize their "
"programs, both are silent.",

"Think of it! With VLSI we can pack 100 ENIACs in "
"1 sq.cm.",

"Editing is a rewording activity.",

"Why did the Roman Empire collapse? What is the La"
"tin for office automation?",

"Computer Science is embarrassed by the computer.",

"The only constructive theory connecting neuroscie"
"nce and psychology will arise from the study of so"
"ftware.",

"Within a computer natural language is unnatural.",

"Most people find the concept of programming obvio"
"us, but the doing impossible.",

"You think you know when you learn, are more sure "
"when you can write, even more when you can teach, "
"but certain when you can program.",

"It goes against the grain of modern education to "
"teach children to program. What fun is there in ma"
"king plans, acquiring discipline in organizing tho"
"ughts, devoting attention to detail and learning t"
"o be self-critical?",

"If you can imagine a society in which the compute"
"r-robot is the only menial, you can imagine anythi"
"ng.",

"Programming is an unnatural act.",

"Adapting old programs to fit new machines usually"
" means adapting new machines to behave like old on"
"es.",

"In seeking the unattainable, simplicity only gets"
" in the way.",

"If there are epigrams, there must be meta-epigram"
"s.",

"Epigrams are interfaces across which appreciation"
" and insight flow.",

"Epigrams parametrize auras.",

"Epigrams are macros, since they are executed at r"
"ead time.",

"Epigrams crystallize incongruities.",

"Epigrams retrieve deep semantics from a data base"
" that is all procedure.",

"Epigrams scorn detail and make a point: They are "
"a superb high-level documentation.",

"Epigrams are more like vitamins than protein.",

"Epigrams have extremely low entropy.",

"The last epigram? Neither eat nor drink them, snu"
"ff epigrams.",

0

};
