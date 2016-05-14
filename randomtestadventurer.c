#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define RUNS 10

int failed = 0;

//ADVENTURER CARD

int myassert(int b,int a,char* msg, int i) {
	if (b != a) {
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

int main(int argc, char *argv[]) {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};

	int i, j, n, current, players, seed, beforeTreasure,afterTreasure, r;
	struct gameState state;

	if (argc >= 2){
		seed = atoi(argv[1]);
	}
	else{
		seed = 42;
	}
	
	for(i = 0; i < RUNS; i++){
		
		players = rand() % MAX_PLAYERS + 1;
		initializeGame(players, k, seed, &state);
		
		for(j = 0; j < players; j++){
			state.deckCount[j] = rand() % MAX_DECK;
			state.handCount[j] = rand() % MAX_HAND;
			state.discardCount[j] = rand() % MAX_DECK;
			
			state.hand[j][0] = adventurer;
			beforeTreasure = 0;
			afterTreasure = 0;
			
			//find treasure cards in hand
			for(int n = 0; n < state.handCount[j]; n++){
				current = state.hand[j][n];
				if(current == gold || current == silver || current == copper){
					beforeTreasure++;
				}
			}
			
			r = playCard(0,0,0,0,&state);	//return value
			
			//find treasure cards in hand after playing the card
			for(int n = 0; n < state.handCount[j]; n++){
				current = state.hand[j][n];
				if(current == gold || current == silver || current == copper){
					afterTreasure++;
				}
			}

			myassert(beforeTreasure+2,afterTreasure,"treasure before and after are equal",i);
			myassert(r,0,"return value was -1, most likely will see this with other error because not enough treasures in deck",i);
			
			
			endTurn(&state);
		}
		
		
	}
	checkasserts();
	return 0;
}