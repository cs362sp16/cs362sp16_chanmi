//kingdomCards

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

int main(){
	int *array = kingdomCards(1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	int i;
	for(i = 0; i < 10; i++)
	myassert(array[i] == 1,"kingdoms are 1");
	free(array);
	checkasserts();
	return 0;
}