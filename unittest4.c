//buyCard function

#include <stdio.h>
#include "dominion.h"
#include <assert.h>
#include <stdlib.h>

int failed = 0;

int myassert(int b,char* msg) {
	if(b == 0) {
		printf("FAILED ASSERTION: %s\n", msg);
		failed = 1;
	}
	return 0;
}

void checkasserts() {
	if (!failed) {
		printf("ALL TESTS SUCCESSFULLY COMPLETED.\n");
	}
}

int main(){
	
	struct gameState g;
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};				
	
	initializeGame(2, k, 5, &g);
	
	myassert(buyCard(1, &g) == 0, "should be valid operation, buy 1");
	myassert(buyCard(69, &g) == -1, "should fail, if you see this, fix it");

	checkasserts();
	return 0;
	
}