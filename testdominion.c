#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 1

int containsCard(int *array, int card) {
	int i;
	for(i = 0; i < 10; i++) {
		if (array[i] == card)
		return 1;
	}
	return 0;
}

int main() {
	printf("Running testdominion.c\n");

	srand(42);
	int j;
	for(j = 0; j < MAX_TESTS; j++) {

		int amountKingdomCards;
		int kingdomCards[10];
		int i;
		for(i = 0; i < amountKingdomCards; i++) {
			kingdomCards[i] = -1;
		}

		//get unique random kindom cards
		int randomKingCard;
		int amountKings = 0;
		while(amountKings < 10) {
			randomKingCard = (rand() % 20) + 7;

			if(containsCard(kingdomCards, randomKingCard))
			continue;

			kingdomCards[amountKings] = randomKingCard;
			amountKings = amountKings + 1;
		}
		printf("\n\n----------NEW TEST----------\n");
		printf("Kingdom cards: ");
		for(i = 0; i < 10; i++) {
			printf("%d ", kingdomCards[i]);
		}
		printf("\n");


		//get 2-4 random players
		int amountPlayers = rand() % 3;
		amountPlayers = amountPlayers + 2;
		printf("Amount players: %d\n", amountPlayers);


		newGame();
		//initialize the game
		struct gameState state;
		struct gameState *g = &state;
		int players[g->numPlayers];
		int seed = rand();		//pick random seed
		printf("Random seed: %d\n", seed);
		int returnValue = initializeGame(amountPlayers, kingdomCards, seed, &state);
		//if failed to intialize game...
		if (returnValue == -1) {
			printf("failed to initialize game\n");
			printf("Seed value: %d\n Amount players: %d\n", seed, amountPlayers);
		}


		//report supply counts
		printf("Initial supply counts: ");
		for(i = 0; i < (treasure_map+1); i++) {
			printf("card %d : %d, ", i, state.supplyCount[i]);
		}
		printf("\n");

		//play the game...
		int totalTurns = 0;
		while(!isGameOver(&state)) {
			int currentPlayer = whoseTurn(&state);
			printf("\n\nCurrent player: %d\n", currentPlayer);

			int randomAction;
			int money = 0;
			int amountAction = 0;

			for(i = 0; i < numHandCards(&state); i++) {


				if(handCard(i, &state) == gold) {
					money = money + 3;
					printf("Playing gold card to calculate money\n");
					playCard(i, -1, -1, -1, &state);
				}
				else if(handCard(i, &state) == silver) {
					money = money + 2;
					printf("Playing silver card to calculate money\n");
					playCard(i, -1, -1, -1, &state);
				}
				else if(handCard(i, &state) == copper) {
					money = money + 1;
					printf("Playing copper card to calculate money\n");
					playCard(i, -1, -1, -1, &state);
				}
				else if(handCard(i, &state) >= 7)
				amountAction++;

			}

			printf("Total money now: %d\n", money);
			//if we have any action cards in hand...
			if(amountAction > 0) {
				//May randomly play ONE action card or not!
				int randomVal =  rand() % numHandCards(&state);
				randomAction = handCard(randomVal, &state);

				if(randomAction >= 7) {
					playCard(randomAction, -1, -1, -1, &state);
					printf("Played: %d, Position: %d\n", randomAction, randomVal);
				}
				else
				printf("Decided not to play action card\n");
			}
			else
			printf("No action cards in hand\n");

			//randomly go into buy phase on a 50-50 chance
			int playersChoice = rand() % 5;
			int buyResult = 0;
			int cardToBuy;
			if(playersChoice != 4) {
				//only buy a card if you can afford the one you want
				cardToBuy = rand() % 27;
				buyResult = buyCard(cardToBuy, &state);
			}
			if(buyResult != (-1)) {
				printf("Bought card: %d\n", cardToBuy);
			}
			else
			printf("Decided not to buy this turn\n");

			printf("Discard count: %d\n", state.discardCount[currentPlayer]);
			printf("Deck count: %d\n", state.discardCount[currentPlayer]);
			printf("Cards in hand: %d\n", numHandCards(&state));
			totalTurns = totalTurns + 1;
			endTurn(&state);
		}

		printf("Total turns of all players: %d \n", totalTurns);
		for(i = 0; i < amountPlayers; i++) {
			printf("Player %d ended with score %d\n", i, scoreFor(i, &state));
		}
		getWinners(players,&state);
		printf("Test complete\n");

	}
	return 0;
}