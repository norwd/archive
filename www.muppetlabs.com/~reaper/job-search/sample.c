/**********************************************************************
 *
 *	cards.c - shuffle 6 decks of cards together.
 *
 *	this program is currently in a version that shuffles 312 cards
 *	(6 decks of 52 cards) in preparation for a blackjack playing
 *	program.  it is using the following algorithm: create an ordered
 *	deck, with cards ordered as 2's, then 3's, etc, for a regular
 *	deck, then repeat this 6 times; that information is stored in a
 *	linked list, and the shuffling function iterates through that
 *	list, to construct a regular array of cards.  as a card is
 *	selected from the linked list, it is deleted, eliminating the
 *	possibility that the random function can choose its 'location'
 *	again.
 *
 *	at the moment, all it practically does is to shuffle the cards,
 *	then print out the shuffled deck with a slightly ridiculous
 *	printing routine...
 *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/********************************************************************/
/* data types */
struct card
{
	char * num;	/* the number of the card (1, 10, ace, etc.) */
	char * suit;	/* the suit of the card (spades, clubs, etc.) */
	int val;	/* the numerical value of the card (K == 10, 
				A == 11 or 1, etc.) */
};

struct link
{
	struct card this_card;	/* the card in question */
	struct link *next_link;	/* the next link in the chain */
};

/********************************************************************/
/* function prototypes */
void init_deck (struct card *);
void pretty_print (struct card);

/********************************************************************/
/* these are lookup arrays, so we can index commonly referenced variables */
static char suits[4][10] = {"Hearts","Clubs","Diamonds","Spades"};
static char cards[13][6] = {"2","3","4","5","6","7","8","9","10",
			"Jack","Queen","King","Ace"};
static int values[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/********************************************************************/
/* the main function! */

void main(int argc, char * argv[])
{
	/* initialize stuff */

	int i;
	struct card deck[312]; 
	srand(getpid());
	
	init_deck(&deck[0]);

	/* print out the deck of shuffled cards */

		for (i=0; i<312; i++)
		{
			pretty_print (deck[i]);
		}
}

/********************************************************************/
/* other functions */

void init_deck (struct card * deck)
{
	int i,j,k,randval;
	/* struct card deck[312]; */
	struct link *first_ptr = NULL;
	struct link *this_link; 
	struct link *this_one, *prev_one, *next_one;


	/* first, create the linked list */
	for (i=0; i<6; i++)
	{
		for (j=0; j<13; j++)
		{
			for (k=0; k<4; k++)
			{
				this_link = (struct link *)
					malloc(sizeof(struct link));

				this_link->this_card.num = cards[j];
				this_link->this_card.suit = suits[k];
				this_link->this_card.val = values[j];

				this_link->next_link = first_ptr;
				first_ptr = this_link;
			} /* for k... */
		} /* for j... */
	} /* for i... */

	/* now, shuffle that deck into array 'deck' */
	for (i=311; i>=2; i--)
	{
		randval = (rand() % (i-1));
		prev_one = first_ptr;

		for (j=0; j<randval; j++)
		{
			prev_one = prev_one->next_link;
		}

		this_one = prev_one->next_link;
		next_one = this_one->next_link;

		deck[i] = this_one->this_card;

		prev_one->next_link = next_one;

		free (this_one);
	}

	/* note that the previous loop went from 311 to 2; the final two
	 * had to be done by hand in order to get the references right
	 * (and to keep the random function from messing up).  it's also
	 * about 2000 times quicker than putting an if..then statement
	 * inside the for loop to catch the final two cases. */

	deck[1] = next_one->this_card;
	free (next_one);
	deck[0] = prev_one->this_card;
	free (prev_one);

	return;
}

void pretty_print (struct card this_card)
{
	printf("This is a %s of %s, worth %d points.\n",
			this_card.num, this_card.suit, this_card.val);
}

