Explaining The Monty Hall Problem
=================================

------------------------------------------------------------------------

### The Setup

Imagine yourself on Let\'s Make a Deal. Monty Hall has you onstage, and
shows you the proverbial three doors. Behind one of them is a new car,
and behind the other two are goats. He asks you to pick a door to open.
You do so. Monty Hall then opens one of the doors you didn\'t pick to
show you that that door concealed a goat. Of course he can always show
you a goat, regardless of what\'s behind your door. (Assume for now that
when Monty has a choice of doors to open, he picks one at random.) There
are now only two doors left, one of them being the one you picked. Monty
Hall then asks you if you would like to stick with your original choice,
or switch to the remaining door.

The question is this: Does it matter if you switch or not? And if it
does, should you switch?

(If by chance you don\'t already know this puzzle, then I strongly
encourage you to take a moment and figure out the answer for yourself.)

The intuitive response is: No, of course it doesn\'t matter if you
switch. There are two doors, so the odds must be an even fifty-fifty.
The fact that there used to be three doors doesn\'t matter at this
point. It\'s like flipping a coin and having it come up heads nine times
in a row: What are the odds that the next flip will come up heads? The
answer is one in two, because the past events don\'t influence the
present state.

However, this situation happens to be a little different. The correct
answer is that it does make a difference, and that you should adopt a
policy of switching. If you switch doors, the odds of getting the new
car are two in three.

If upon reading the above paragraph, your reaction is to strongly doubt
its veracity (and perhaps even my intelligence), then let me tell you
right now you are in excellent company. You\'re joined not just by the
majority of people with average levels of math education ---
professional mathematicians are just as likely to have that reaction.
Quite a number of them have embarrassed themselves publicly by insisting
that that fifty-fifty answer has to be correct.

What follows is a collection of seven different ways to explain why this
counter-intuitive fact is true. These explanations effectively all say
the same thing, but from different points of view. Most of them will
probably sound unconvincing at first. Our intuition is so sure of
itself, it can be hard to get it to budge. In my experience, when people
guess the wrong answer, they will continue to remain unmoved by
explanations for a while. Eventually they reach a tipping point, and can
start to get a handle on where their intuition has gone astray. My guess
is that explanations don\'t help until after that point has been
reached. Which may be why it\'s always a different explanation that
finally convinces. Whatever the reason, I recommend that you try on all
of the following explanations, in any order you like, until you find one
that feels like it works for you.

(Then, for extra credit, once you feel you\'ve completely aceepted the
explanation, go back and reread the ones that didn\'t convince you, and
try to figure out why.)

### I. The *Reductio ad Absurdum* Explanation

At the very beginning, when you make your first selection, you have a
one in three chance of getting the car. We think that when Monty Hall
opens another door, the odds should go up to one in two, but remember
that Monty can *always* open a door. So imagine that you\'re still
trying to make your first choice. You think to yourself: \"Door \#1 has
a one in three chance of being correct. However, after I announce that
choice, Monty Hall will expose a goat behind one of the other doors, and
at that point the odds of Door \#1 being correct will shoot up to one in
two. However, it now occurs to me that I don\'t have to wait for him to
do this, because I already know for a fact that he will do this. It is
already certain knowledge. So the odds of Door \#1 being right are
already one in two.\" But you can apply the same reasoning to Door \#2
and Door \#3, and get the same result. This will leave you with a total
of 150% for all three possibilities, and this is obviously wrong.
Therefore our assumption that Monty Hall showing us a goat will change
the odds must be wrong. Which means that the door we select must still
have a one in three chance of being the winning door. Since there is
only one other door remaining, the probability of it hiding the car must
be two in three.

### II. The Forced Hand Explanation

At the beginning, when you pick a door for the first time, you have a
one-in-three chance of picking the car, and a two-in-three chance of
picking a goat. What happens next? Assume for the moment that you\'ve
picked the car. Monty Hall therefore can choose either of the two
remaining doors to open, since they both conceal goats, and when you
switch, you are guaranteed to wind up with the other goat. Now instead
assume that you\'ve picked one of the goats to begin with. Monty
doesn\'t have a choice of doors now; he must expose the remaining goat.
So when you switch, you are guaranteed to wind up with the car. It\'s
the only thing left. Since you have a two-thirds chance of picking a
goat at the beginning, always switching gives you the car two-thirds of
the time at the end.

### III. The N Doors Explanation

Imagine that instead of three, there are a hundred doors --- one car and
99 goats. Let\'s say that you pick Door \#34. Monty Hall then opens a
different door to expose a goat, and then offers you the choice to keep
your choice, or switch to one of the remaining 98 doors. Let\'s assume
that you choose to stick with Door \#34. He then exposes another goat,
and then another, and another, and so on, each time offering you the
chance to switch, and every time you turn him down. Finally, he opens a
98th door, showing you a 98th goat. The only doors still closed are Door
\#34, the door you picked, and Door \#78. For the last time, Monty gives
you the option of switching. If you take a moment to think about it,
you\'ll realize that you\'d be a fool not to switch at this point. Odds
are 99% that you started by picking a goat, and thus you have forced
Monty to expose all the remaining goats in order to keep the car
concealed. The odds that the car is *not* behind Door \#78 is therefore
1%. Right? So at that point you switch. But now imagine the same
scenario with only ten doors. After Monty Hall opens eight door and
exposed eight goats, then principle is less pointed but otherwise the
same. The odds are nine in ten in your favor if you switch. Now consider
the case with only five doors \... four doors \... then three doors. The
principle continues to hold: your odds are always increased by
switching.

### IV. The Equivalent Situation Explanation

Imagine instead that first you make your pick of Door \#1, and then,
without opening any doors, Monty Hall asks you if you wish to stick with
your original choice, or switch to Door \#2 *and* Door \#3. That is, if
you switch, you get the car if it\'s behind either of the other two
doors. It\'s pretty obvious in this case that switching doubles your
chances. But this is actually identical to the original problem. The
opening of one of the doors you didn\'t pick can be seen as effectively
\"giving\" you that door.

### V. The Table-Turning Explanation

The key point to realize is that when you switch, you will always switch
to the opposite of what you originally picked. You can\'t switch from a
goat to a goat, because Monty Hall always removes one of the two goats
from consideration before you switch. (And of course you can\'t switch
from a car to a car, because there\'s only one car all along.) No matter
what happens beforehand, at the time of your switch there is one goat
and one car. So, if you start with the car, switching moves you to the
goat, and if you start with a goat, you will switch to the car.
Switching therefore reverses the odds of the original game, putting them
in your favor. Because you have a two-in-three chance of starting with a
goat, you have a two-in-three chance of ending with the car.

### VI. The Probability Table Explanation

Our confusion comes from how we think the probability breaks down. We
tend to imagine the situtation as being something like this:

> Assume for the sake of concreteness that you start by picking Door
> \#1, and Monty Hall chooses Door \#3 to open and expose a goat. The
> possible outcomes from that point are:
>
>   ------ ------ ------ -------------------------------------------------------
>   \#1    \#2    \#3    
>   car    goat   goat   --- you will win if you don\'t switch
>   goat   car    goat   --- you will win if you do switch
>   goat   goat   car    --- impossible, since Monty will never expose the car
>   ------ ------ ------ -------------------------------------------------------

This line of reasoning makes it look like there are only two possible
situations, equally likely, and thus there is a fifty-fifty chance of
winning. But this is faulty, because it fails to take into account that
the door you start with affects the probabilities of what happens next.
Your initial choice affects which door Monty Hall can choose. In fact,
Monty doesn\'t even have a choice most of the time, and the probability
table up above fails to take that imbalance into account. So instead, we
must go back to the point at which you first selected Door \#1, and
break down the possible scenarios from there:

  ------ ------ ------ -----------------------------------------------------------------------------
  \#1    \#2    \#3    
  car    goat   goat   --- Monty can open \#2 or \#3, and (either way) you will lose if you switch
  goat   car    goat   --- Monty must open \#3, and you will win if you switch
  goat   goat   car    --- Monty must open \#2, and you will win if you switch
  ------ ------ ------ -----------------------------------------------------------------------------

Thus we see that a policy of switching gives us the car two times out of
three.

### VII. The Soul of Wit Explanation

The truth is that the door that Monty Hall chooses to open doesn\'t tell
you anything about the door you originally selected --- but it does tell
you something about the door he *didn\'t* open. *couldn\'t* open.

 

------------------------------------------------------------------------

[[Texts](http://www.muppetlabs.com/~breadbox/txt/)]{.small}\
[[Brian Raiter](http://www.muppetlabs.com/~breadbox/)]{.small}
