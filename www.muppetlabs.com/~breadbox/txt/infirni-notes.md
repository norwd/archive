Notes on Writing a Monovocalic Sonnet
-------------------------------------

------------------------------------------------------------------------

I encountered Giuseppe Varaldo\'s sonnet while reading Douglas
Hofstadter\'s \"Le Ton Beau de Marot\". Hofstadter describes Varaldo\'s
collection of sonnets, each one employing a single vowel whilst
summarizing a famous literary work in fourteen lines, and provides a few
examples. (Varaldo\'s work immediately reminded me of \"Shrinklits\",
and I was pleasantly surprised when Hofstadter mentioned this little
book a few pages later.) Having never seen a monovocalic work of any
length before, I was quite taken with the idea. It seemed formidable
enough, however, to discourage me from sitting down and trying to write
one myself.

But later on in the book Hofstadter, while discussing works that he or
other people consider to be \"untranslatable\", comments that
translating Varaldo\'s sonnets in the usual sense of the word *and*
retaining their monovocal nature might well be impossible. But, he
continued, by enlarging the concept of translation, so as to simply
require a monovocalic sonnet that summarized the same literary work,
then it would very likely be possible, and that he could even \"dimly
imagine\" it being done.

Well, I could not help but read that comment as a gauntlet thrown down
at my feet. I thought about it and decided that it wouldn\'t be as hard
as Hofstadter was implying.

It\'s entirely possible that I wouldn\'t have gotten started if I had
had a more accurate feeling for the difficulty of the task.

I quickly saw that I needed to select my vowel before doing anything
else. For some reason I was drawn to using *i*. Why I don\'t know.
Choosing *a* would have allowed me to refer to Satan, as well as
allowing \"stars\" as the final word. Choosing *e* would have permitted
me to name Hell, and would have given me more freedom with tenses. I
knew that by sticking with *i*, I would have to stay in the present
tense. *i*\'s only real benefit was being able to name Virgil. What I
really wanted, of course, was to be able to name Dante, and so perhaps I
felt that having access to the first person would be the next best
thing. Then, of course, I suddenly realized that I could name Dante,
after a fashion, by referring to him as Pilgrim. That decided it for me
at once. This discovery boosted my confidence in myself, and I set to
work.

My first sally eventually stalled, however. I began by casting about in
my mind for available words that met the constraint and seemed like they
could be useful. I pulled out my copy of \"The Inferno\" and reread it
to refresh my memory as to the major events of the story, and to look
for inspiration. (Doing this gave me Dis, the city in Hell, among other
words.) At some point I hit upon \"pinpricks\", and realized that
\"night\'s shining pinpricks\" would be an acceptable way to mention
stars at the end of the sonnet.

Eventually I realized that there were far more words available to me
than I could dredge up by my undirected musings, and so I sat down at my
computer and typed in a command, something I should have done at the
outset:

> `$ grep -v '[aeouy]' dict.txt > i.txt`

There were only a couple thousand words. That gave me pause. (Later I
went back to ferret out the words that included *y* as a consonant.
There were less than twenty, and \"yip\" and \"yipping\" were the only
ones I had ever heard before.)

After working on it for a couple of weeks, my collection of words with
potential had grown, and I had managed to assemble a small set of
phrases and sentence fragments. I also had several words that weren\'t
necessarily appropriate, but were too tempting not to consider.

Here\'s a sizeable excerpt of what my notes looked like at that point:

> chiming in\
> swimming in shit\
> stiff with fright\
> first in his trips\
> first third in his trip\
> it is writ\
> drinking it in\
> stinking clinging mists
>
> binding blinding biting fighting smiting\
> kicking pricking\
> hiking striking\
> slitting\
> stinging\
> whipping\
> itching\
> illing
>
> ripping limbs\
> stripping skin\
> crisping in kilns within Dis
>
> Stingings, whirling winds, mirings in filth,\
> Dis with its stinking clinging stifling thick mists,\
> spirits crisping in kilns within,\
> Smiling, driving, grinning imps with whips, striping spirit skins
>
> tristichs
>
> It isn\'t inviting, this whirlwind filmic flight.

I actually had quite a fair bit of material. However, it was all in
little pieces. I had a terrible time trying to find ways to put the
fragments together. Furthermore, I realized that I had given very little
thought to the other constraint \-- the fact that this was supposed to
be a sonnet. Not only did I need to stick to a decent meter, this thing
would need to rhyme! When I started taking that into account, I got
discouraged. I briefly considered just trying to do a sonnet without
rhymes, but quickly decided that would be tantamount to giving up.

It felt as if I had taken a piece or two from a hundred different jigsaw
puzzles, and was now trying to find ways to fit them together in hopes
that a coherent picture would emerge by itself at the end. That wasn\'t
going to happen. Most of the pieces didn\'t fit together in the first
place, and where they did the pictures on the fragments didn\'t match.

I wound up setting the project aside for a while. However, my pride
would not let me back down so easily. Especially since I knew from past
experience that finding rhymes isn\'t intrinsically hard; it just takes
time and effort. I thought about purchasing a rhyming dictionary, but
realized that I would have to weed out 99% of the words.

Finally, I decided (or realized) that there was only one good way to
proceed. Biting the bullet, I sat down with my list of 2000+ words, and
classified them all by rhyme, using a representation I invented as I
went along. I made myself include every last one of the words on my
list, even ones I felt sure I would never want to use. After all, you
never know.

It took nearly a week to complete this, with a fat dictionary at hand.
(The number of words for which I was unclear on the exact pronounciation
or the correct stress pattern was humbling.) When I was done, my file
looked like this:

  ----------- --- ---------
  bi              igh
  bib             ibb
  bibb            ibb
  bibbing         ibbing
  bibbs           ibbs
  bibs            ibbs
  bid             idd
  bidding         idding
  biddings        iddings
  biding          iding
  bids            idds
  ----------- --- ---------

Certain words have more than one stressed syllable which both need to
match sometimes in order to be a proper rhyme, and I notated these words
like this:

  ------------- --- ------------
  hind              eind
  hinds             einds
  hindsight         eind-ight
  hindsights        eind-ights
  ------------- --- ------------

Once I had finished that onerous task, I put together a simple Perl
script, which I reproduce here:

    #!/usr/bin/perl -w
    use strict;
    my (%dict, %index);
    open DICT, "./ir.txt" or die $!;
    while (<DICT>) {
        my ($a, $b) = split;
        $index{$a} = $b;
        push @{$dict{$b}}, $a;
    }
    my $nm = join "-", map { $_ eq "-" ? "" : $index{$_} || die "?:$_\n" } @ARGV;
    exit unless exists $dict{$nm};
    my @add;
    foreach (keys %dict) { push @add, @{$dict{$_}} if /-$nm$/ }
    $_ = join " ", sort @{$dict{$nm}};
    $_ .= " (@{[sort @add]})" if @add;
    print "$_\n";

With this, I could now look up any of my words to find its rhymes:

` $ ./irhyme tricks  bricks chicks clicks cricks dicks fix flicks hicks ichs immix infix kicks licks micks mix nicks nix picks pics pix pricks ricks schriks shticks sicks sics six slicks snicks spicks spics spiks stichs sticks stricks thicks ticks tics tricks wicks (dikdiks dipsticks lipsticks niblicks nitpicks pickwicks picnics pigsticks pinpricks)`

(The parentheses indicate words that have another stressed syllable, and
so may or may not be acceptable, depending on the context and meter.)

Of course, just having gone through the entire list of words in that
fashion was equally helpful, if not more so. I had a lot more of my
available vocabulary fresh in my mind, and I was starting to come up
with some plausible rhyme pairs. I began to look for rhymes for words in
the larger fragments I had managed to compose.

It was here that I finally took the important step of abandoning most of
my favorite fragments for lack of rhyming words that fit with the
subject matter, or for lack of rhyming words that could be positioned at
the end of a line without sounding awkward, or sometimes simply for a
lack of rhyming words. Once I was willing to consider leaving out
anything I had already composed, I was able to start seeing which pieces
really could work together, and where.

Having gotten past that hurdle, I began to have problems with one of my
noteable weaknesses \-- namely, that my sense of meter is not
particularly developed. Iambic pentameter probably suffers the worst of
all at my hands. First the iambs start to melt away as
half-unconsciously I begin squeezing in more and more unstressed
syllables. This then leads to a blurring of my sense of which syllables
can and can\'t get away with being unstressed. At some point I sit up
and realize that for quite a while now I\'ve been trying to write in
sort of a jittery tetrameter, loaded down with enough unstressed
syllables to fool me into thinking that I have five feet in every line.
Anyway, after considering my options, I decided that I would be doomed
if I didn\'t just give in to my natural inclination from the start, and
write it in a tetrameter, with the majority of syllables being
unstressed.

The second stanza was the first one to achieve a semblance of
completion. (This one has most of the words that I wanted to include for
the sheer felicitiousness that made them available to me at all.) When I
had that more or less put together, I began to worry about the second
half, where I had to produce not one but two rhyming triplets. And for
one of them I was already committed to \"pinpricks\" as the rhyme. I had
plenty of rhymes for -icks, but very few lended themselves to the
subject at hand. Finally, one day it occurred to me that I could use
\"Nick\'s\" \-- as in Old Nick. I wasn\'t thrilled with it, for normally
one would never refer to Dante\'s Lucifer as Nick. But I was desperate
by this point, so I compromised. Soon after that I came up with
\"childish tricks\", referring to the episode where Virgil and Dante
have to evade some demons with evil intentions.

Meanwhile the first stanza began to come into focus. The first line I
had composed quite early on, and it seemed to work well. I didn\'t have
to sweat too much to fill in the other three lines.

I was working on a stanza devoted to describing some of the damned and
their various punishments, when I suddenly realized that there wasn\'t
anywhere to put it. Without noticing, I had already selected the subject
matter of all fourteen lines! It\'s too bad, really, for I think the
biggest failing of my sonnet (aside from the uneven meter, perhaps) is
the absence of any description of what Dante actually sees, which is the
whole point of the story and constitutes the bulk of the original work.
But I couldn\'t really make room for it without losing something that
seemed critical to the flow I already had. There is, after all, only so
much you can cover in fourteen lines of tetrameter.

Finally understanding that I had almost completed my quest, I put the
pieces I had into place to see what was still missing. The biggest hole
was the first two lines of the final stanza. I worked on that one for a
while, trying to describe the pair\'s unexpected exit from Hell in two
measly lines, with the end words of each stanza already set in stone.
But by day\'s end I had a complete sonnet. And after playing with it for
another couple of hours without finding any way to improve it, I was
finally ready to call it finished.

------------------------------------------------------------------------

\
[[Sonnet](http://www.muppetlabs.com/~breadbox/txt/infirni.html)]{.small}\
[[Texts](http://www.muppetlabs.com/~breadbox/txt/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
