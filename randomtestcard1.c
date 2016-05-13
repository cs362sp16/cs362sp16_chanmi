#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUNS 50

int failed = 0;

int myassert(int b,char* msg) {
	if (b == -1) {
		printf("FAILED ASSERTION: %s\n",msg);
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
	int seed;
	int i, j;
	time_t t;
	
	if (argc >= 2){
		seed = atoi(argv[1]);
	}
	else{
		seed = 42;
	}
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
	sea_hag, tribute, smithy};
	
	struct gameState *state;
	for (i = 0; i < RUNS; i++) {
		state = newGame();
		initializeGame(2, k, seed, state);

		j = cardEffect(smithy, 0, 0, 0, state, 0, 0);

		myassert(j,"smithy fail");
	}
	checkasserts();
	return 0;
}