//whoseTurn

#include <stdio.h>
#include "dominion.h"
#include <assert.h>
#include <stdlib.h>

int failed = 0;

int myassert(int b,char* msg) {
	if (b == 0) {
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

int main() {
	struct gameState g;
	
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
		outpost,baron,tribute};
	
	initializeGame(2, k, 5, &g);

	g.whoseTurn = 11;
	myassert(whoseTurn(&g)==11,"11 players");
	g.whoseTurn = 2;
	myassert(whoseTurn(&g)==2,"2 players");

	checkasserts();
	return 0;
}