//numHandCards

#include "dominion.h"
#include <stdio.h>

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

	int num = numHandCards(&g);
	myassert(num == 5, "5 cards test");
	
	checkasserts();
	return 0;
}