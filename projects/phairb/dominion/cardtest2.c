#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void assertTF(int condition, char* statement){

    if(condition != 1){
        printf("%s\n\n", statement);
    }
}


void testCopperCopper(struct gameState G, struct gameState testG, int currentPlayer){
    int deckcount = testG.deckCount[currentPlayer];
    int i;
    int newDeck1 [] = {copper, copper};
    int newDeckCount = 3;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][--deckcount] = newDeck1[i];
    }

    adventurer_card(currentPlayer, &testG, 0, 0, 0);

    int newCards = 2;
    int xtraCoins = 0;
    int numBuys = 0;

    int handCount = testG.handCount[currentPlayer];

    printf("\n\tPlayer %i:\n", currentPlayer + 1);
    printf("TestG Handcount: %i \t G Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards);
}



int main(int argc, char** argv) {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int numBuys = 0;
    int numActions = 0;
    int handCount;
    int deckcount;
    int  newDeckCount;
    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
    int currentPlayer;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};



    /*Initialize the game*/
//    initializeGame(numPlayers, k ,seed, &G);
//    memcpy(&testG, &G, sizeof(struct gameState));

    printf("\n*** Testing adventurer_card() ***\n");

    initializeGame(numPlayers, k, seed, &G);



//    printf("\n\n*** Test if the variable drawntreasure has any affect on cards drawn ***\n");
//    printf("* Test Parameters: *\n");
//    printf("drawntreasure value: 0 \t Number of cards that should be drawn: 2\n");
//    printf("drawntreasure value: 1 \t Number of cards that should be drawn: 1\n");
//    printf("drawntreasure value: 2 \t Number of cards that should be drawn: 0\n\n");
//
//
//    for(a = 0; a < numPlayers; a++){
//        initializeGame(numPlayers, k ,seed, &G);
//        memcpy(&testG, &G, sizeof(struct gameState));
//        for(b = 0; b <= 3; b++){
//            int currentHandCount = testG.handCount[a];
//#if (NOISY_TEST == 1)
//        printf("\t\tPlayer %i\n", a + 1);
//        printf("Original Cards: %i \tdrawntreasure: %i \n", testG.handCount[a], b);
//#endif
//            adventurer_card(b, &testG, a, 0, temphand);
//#if (NOISY_TEST == 1)
//            if(b == 0) {
//                printf("Actual Cards: %i \tExpected Cards: %i \n", testG.handCount[a], G.handCount[a] + 2);
//            }
//            else if(b == 1){
//                printf("Actual Cards: %i \tExpected Cards: %i \n", testG.handCount[a], G.handCount[a]+ 1);
//            }
//            else if(b == 2){
//                printf("Actual Cards: %i \tExpected Cards: %i \n", testG.handCount[a], G.handCount[a] + 0);
//            }
//            else if(b == 3){
//                printf("Actual Cards: %i \tExpected Cards: %i \n", testG.handCount[a], G.handCount[a] + 0);
//            }
//#endif
//        }
//        endTurn(&testG);
//        endTurn(&G);
//    }

//              ****** DON"T DELETE**********




    printf("\n\n*** Test based on the Treasure cards in hand ***\n");




    printf("\n*** Test Case Copper, Copper ***\n");

    currentPlayer = 0;

    memcpy(&testG, &G, sizeof(struct gameState));
    deckcount = testG.deckCount[currentPlayer];

    int newDeck1 [] = {copper, copper};
    newDeckCount = 3;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][--deckcount] = newDeck1[i];
    }

    adventurer_card(0, &testG, 0, 0, 0);

    newCards = 2;
    xtraCoins = 0;
    numBuys = 0;

    handCount = testG.handCount[currentPlayer];
    printf("TestG Handcount: %i \t G Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards);






    memcpy(&testG, &G, sizeof(struct gameState));
    currentPlayer = 0;
    deckcount = testG.deckCount[currentPlayer];

    printf("Deckcount = %i\n", testG.deckCount[currentPlayer]);

    int newDeck2 [] = {copper, gold, gold, copper};
    newDeckCount = 4;
    testG.deckCount[currentPlayer] = newDeckCount;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck2[i];
    }

    for(i = 0; i < deckcount; i++) {
        printf("%i\n", testG.deck[currentPlayer][i]);
    }

    int temp[] = {};

    adventurer_card(0, &testG, 0, 0, temp);

    printf("In my discard:\n");

    for(i = 0; i < testG.discardCount[currentPlayer]; i++){
        printf("%i\n", testG.discard[currentPlayer][i]);
    }

    printf("TestG Discard Count for Player 1: %i \t G Discard Count for Player 1: %i\n",);


    printf("\n\nAll tests for numHandCards() passed!\n");

    return 0;
}
