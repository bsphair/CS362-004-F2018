/* Author: Brian Phair
 * Description: Tests the smithy card in dominion.c
 * */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>



// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1



int main () {
    int numTestsPassed = 0, passedAllTestsFlag = 0, currPlayer = 0, failedDeckCount = 0, failedHandCount = 0, failedDiscardCount = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0, i = 0;
    int seed = 1000;
    int numPlayers = 2;
    int numberOfTests = 50000;
    int deckSize, handSize, startDeck, currDeck, startHand, currHand, startDiscard, currDiscard;
    int allowedCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    struct gameState G;

    srand(time(NULL));

    //loop for number of tests
    for (i = 0; i < numberOfTests; i++) {

        //Randomly intialize the game state. Then make sure the needed variables are sane.
        initializeGame(numPlayers, allowedCards, seed, &G);

        deckSize = rand() % (MAX_DECK + 1);
        handSize = rand() % (deckSize + 1);

        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
        handPos = G.hand[currPlayer][G.handCount[currPlayer]-1];


        //Note the current state before playing the card
        startDeck = G.deckCount[0];
        startHand = G.handCount[0];
        startDiscard = G.playedCardCount;


        //Play the card
        cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);


        //Note the state after playing the card
        currDeck = G.deckCount[0];
        currHand = G.handCount[0];
        currDiscard = G.playedCardCount;


        //NOW... the moment of reckoning... the tests
        passedAllTestsFlag = 1;


#if (NOISY_TEST == 1)
        printf("*** Testing Smithy card ***\n");
#endif
        if (currDeck != (startDeck - 3)) {
#if (NOISY_TEST == 1)
            printf("\tDeck count - Fail\n");
#endif
            failedDeckCount++;
            passedAllTestsFlag = 0;
        }
        else {
#if (NOISY_TEST == 1)
            printf("\tDeck count - Pass\n");
#endif
        }

        if (currHand != (startHand + 2)) {
#if (NOISY_TEST == 1)
            printf("\tCards drawn - Fail\n");
#endif
            failedHandCount++;
            passedAllTestsFlag = 0;
        }
        else {
#if (NOISY_TEST == 1)
            printf("\tCards drawn - Pass\n");
#endif
        }

        if (currDiscard != (startDiscard + 1)) {
#if (NOISY_TEST == 1)
            printf("\tCards discarded - Fail\n");
#endif
            failedDiscardCount++;
            passedAllTestsFlag = 0;
        }
        else {
#if (NOISY_TEST == 1)
            printf("\tCards discarded - Pass\n");
#endif
        }


        if (passedAllTestsFlag == 1) {
#if (NOISY_TEST == 1)
            printf("All tests passed!\n");
#endif
            numTestsPassed++;
        }

    }


    printf("Smithy tests summary:\n");
    printf("\tPassed: %d\n", numTestsPassed);
    printf("\tFailed (deck): %d\n", failedDeckCount);
    printf("\tFailed (hand): %d\n", failedHandCount);
    printf("\tFailed (discard): %d\n\n", failedDiscardCount);



    return 0;

}