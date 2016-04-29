//gardens

#include "dominion_helpers.h"
#include "dominion.h"
#include <stdio.h>
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

	cardEffect(gardens,0,0,0,&g,0,0);
	myassert(scoreFor(0,&g)>0,"score should be more than 0");

	checkasserts();
	return 0;
}