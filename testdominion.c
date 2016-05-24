#include "dominion.h"
#include "stdlib.h"
#include "stdio.h"

#define RUNS 1

//checkpoint randoKings

int main(int argc, char** argv){
	int seed, i, j, returnVal;
	
	int count = 0;
	int try;
	int unique;
	
	if(argc > 2)
	seed = atoi(argv[1]);
	else
	seed = 42;
	srand(seed);
	
	//checkpoint seed

	for (j = 0; j < RUNS; j++){
		int totalPlayers = rand() % 3 + 2;
		int k[10];
		for (i = 0; i < 10; i++)
		k[i] = 0;
		
		//pick 10 random and unique cards
		while (count < 10){
			unique = 0;
			try = (rand() % (treasure_map - adventurer)) + adventurer;
			for (i = 0; i < 10; i++){
				if (k[i] == try)
				unique = 1;
			}
			if (unique != 1){
				k[count] = try;
				count++;
			}
		}

		struct gameState state;

		initializeGame(totalPlayers, k, seed, &state);

		char *readName[treasure_map+1] = {"curse","estate","duchy",
			"province","copper","silver","gold","adventurer","councilroom",
			"feast","gardens","mine","remodel","smithy","village","baron","greathall",
			"minion","steward","tribute","ambassador","cutpurse","embargo","outpost",
			"salvager","seahag","treasuremap"};

		printf("Starting game; \n%i total players; \nKingdoms: ", totalPlayers);
		
		for (i = 0; i < 10; i++)
		printf("%s ",readName[k[i]]);
		printf("\n");
		
		//game loop
		while(!isGameOver(&state)){

			printf("\nPlayer %i's turn-----------------\n",whoseTurn(&state)+1);
			printf("Hand count: %i\n",state.handCount[whoseTurn(&state)]);

			//action phase
			int handCount = state.handCount[whoseTurn(&state)];
			for (i = 0; i < handCount; i++){
				int actCard = state.hand[whoseTurn(&state)][i];
				if(actCard >= adventurer && actCard <= treasure_map){

					printf("%i tries %s from hand position %i\n",whoseTurn(&state)+1,readName[actCard],i);
					returnVal = 0;
					switch (actCard){
					case adventurer:
						returnVal = playCard(i,0,0,0,&state);
					case gardens:
						returnVal = playCard(i,0,0,0,&state);
					case smithy:
						returnVal = playCard(i,0,0,0,&state);
					case village:
						returnVal = playCard(i,0,0,0,&state);
					case great_hall:
						returnVal = playCard(i,0,0,0,&state);
					case tribute:
						returnVal = playCard(i,0,0,0,&state);
					case cutpurse:
						returnVal = playCard(i,0,0,0,&state);
					case outpost:
						returnVal = playCard(i,0,0,0,&state);
					case sea_hag:
						returnVal = playCard(i,0,0,0,&state);
					case treasure_map:
						returnVal = playCard(i,0,0,0,&state);
					}

					if (returnVal == -1)
					;
			//		printf("Can't play that card\n");
					else {
						printf("%s was played\n",readName[actCard]);
						break;
					}
				}
			}

			//victory/money card
			if (rand() % 10 == 1){
				for (i = 6; i > 1; i--){
					returnVal = buyCard(i, &state);
				//	printf("%i attempts to buy: %s\n",whoseTurn(&state)+1,readName[i]);

					if (returnVal == -1)
						;
				//	printf("Purchase did not go through\n");
					else{
						printf("%s bought\n",readName[i]);
						break;
					}
				}
			}
			//kingdom card
			else {
				for (i = 0; i < 5; i++){
					int j = rand() % 10;
					returnVal = buyCard(k[j], &state);
				//	printf("%i attempts to buy %s\n",whoseTurn(&state)+1,readName[k[j]]);

					if (returnVal == -1)
						;
				//	printf("Purchase failed\n");
					else{
						printf("Bought: %s\n",readName[k[j]]);
						break;
					}
				}
			}
			printf("\nGamestate values--\n");
			printf("coins: %i\n",state.coins);
			printf("numBuys: %i\n",state.numBuys);
			printf("handCount: %i\n",state.handCount[whoseTurn(&state)]);
			printf("deckCount: %i\n",state.deckCount[whoseTurn(&state)]);
			printf("handCount: %i\n",state.discardCount[whoseTurn(&state)]);
			printf("playedCardCount: %i\n",state.playedCardCount);
			//printf("outpostsPlayed: %i\n",state.outpostPlayed);
			shuffle(whoseTurn(&state),&state);
			endTurn(&state);
		}

		// Print the players' scores
		for(i = 0; i < totalPlayers; i++){
			printf("%i's score: %i\n",i+1,scoreFor(i, &state));
		}

		// Print the winners
		int w[MAX_PLAYERS];
		getWinners(w, &state);
		printf("winners as determined by getWinners(): ");
		for (i = 0; i < totalPlayers; i++){
			if (w[i] == 1)
			printf("%i ", i+1);
		}
		printf("\n");
	}

	return 0;

}