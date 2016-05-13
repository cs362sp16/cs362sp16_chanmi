#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define RUNS 100

int main(int argc, char *argv[]) {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
		sea_hag, tribute, smithy};

	int i, j, players, seed;
	struct gameState state;

	if (argc >= 2){
		seed = atoi(argv[1]);
	}
	else{
		seed = rand();
	}
	
	for(i = 0; i < RUNS; i++){
		players = rand() % 6 + 1;
		initializeGame(players, k, seed, &state);
		for(j = 0; j < players; j++){
			state.deckCount[i] = rand() % MAX_DECK;
			state.handCount[i] = rand() % MAX_HAND;
		}
		playCard(0,1,1,1,&state);
	}
	
	printf("Tests Complete\n");

	return 0;
}