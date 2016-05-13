#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion_helpers.h"

#define RUNS 50

int failed = 0;

int myassert(int b,int a,char* msg, int i) {
	if (b == a) {
		printf("run %i, FAILED ASSERTION: %s\n",i,msg);
		failed = 1;
	}
	return 0;
}

void checkasserts() {
	if (!failed) {
		printf ("TEST SUCCESSFULLY COMPLETED.\n");
	}
} 

int main(int argc, char* argv[]) {
	int seed, r;
	int i, j, beforeHand;
	time_t t;
	int players = rand() % MAX_PLAYERS + 1;
		
	seed = atoi(argv[1]);
	
	
	//seed = 42;
	
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};
	
	struct gameState state;
	//loop runs
	for (i = 0; i < RUNS; i++) {
		//state = newGame();
		initializeGame(2, k, seed, &state);

		//loop players
		for(j = 0; j < players; j++){
			state.handCount[j] = rand() % MAX_HAND;
			state.deckCount[j] = rand() % MAX_DECK;
			
			beforeHand = state.deckCount[j];
			
			state.hand[j][0] = smithy;
			r = playCard(0,0,0,0,&state);
			endTurn(&state);
			
			
			myassert(state.handCount[j],beforeHand,"didnt add cards",i);
			myassert(state.handCount[j],beforeHand+2,"didnt add 3 cards",i);
			myassert(r, -1, "return value fail", i);
			
		}
	}
	checkasserts();
	return 0;
}