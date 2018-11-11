/* Author: Brian Phair
 * Description: Tests the great hall card in dominion.c
 * */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main () {
    int numTestsPassed = 0, passedAllTestsFlag = 0, testDraw = 0, failedDiscard = 0, beforeCoins = 0, afterCoins = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
    int numPlayers = 2, currPlayer = 0, deckSize, handSize, randomCard, randAllowedCard;
    int trCopper, trSilver, trGold;
    int numberOfTests = 50000;
    int seed = 1000;
    int i, j, k;
    int allowedCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    struct gameState G;


    srand(time(NULL));


    //loop for number of desired tests
    for (i = 0; i < numberOfTests; i++) {
        passedAllTestsFlag = 1;

        initializeGame(numPlayers, allowedCards, seed, &G);     //initialize the game

        deckSize = rand() % (MAX_DECK + 1);     //randomize size of deck
        handSize = rand() % (deckSize + 1);     //randomize size of hand

        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;

        beforeCoins = 0;
        afterCoins = 0;


        //Place random cards in each player's deck
        for (j = 0; j < numPlayers; j++) {          //for each of the players

            for (k = 0; k < G.deckCount[j]; k++) {      //for the size of the deck

                randomCard = rand() % 51;	//generate random number

                if (randomCard == 1) {      //place copper in deck
                    G.deck[j][k] = copper;
                }
                else if (randomCard == 2) { //place silver in deck
                    G.deck[j][k] = silver;
                }
                else if (randomCard == 3) { //place gold in deck
                    G.deck[j][k] = gold;
                }
                else {
                    randAllowedCard = rand() % 10;
                    G.deck[j][k] = allowedCards[randAllowedCard];
                }
            }
        }


        //calculate the number of coins in the player's hand
        for (j = 0; j < G.handCount[currPlayer]; j++) {
            if (G.hand[currPlayer][j] == copper || G.hand[currPlayer][j] == silver || G.hand[currPlayer][j] == gold) {
                beforeCoins += 1;
            }
        }

        cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus); //play the adventurer card


        //calculate the number of coins in the player's hand
        for (j = 0; j < G.handCount[currPlayer]; j++) {
            if (G.hand[currPlayer][j] == copper || G.hand[currPlayer][j] == silver || G.hand[currPlayer][j] == gold) {
                afterCoins += 1;
            }
        }


        trCopper = 0;
        trSilver = 0;
        trGold = 0;

        for (j = 0; j < G.discardCount[currPlayer]; j++) {

            if (G.discard[currPlayer][j] == copper) {
                trCopper += 1;
            }
            else if (G.discard[currPlayer][j] == silver) {
                trSilver += 1;
            }
            else if (G.discard[currPlayer][j] == gold) {
                trGold += 1;
            }
        }


#if (NOISY_TEST == 1)
        printf("*** Testing Adventurer card ***\n");
#endif

        if (afterCoins != (beforeCoins + 2)) {
#if (NOISY_TEST == 1)
            printf("\tCards drawn - Fail\n");
#endif
            testDraw++;
            passedAllTestsFlag = 0;
        }
        else {
#if (NOISY_TEST == 1)
            printf("\tCards drawn - Pass\n");
#endif
        }

        if (afterCoins < beforeCoins) {
#if (NOISY_TEST == 1)
            printf("\tCards count - Fail\n");
#endif
            testDraw++;
            passedAllTestsFlag = 0;
        }
        else {
#if (NOISY_TEST == 1)
            printf("\tCards count - Pass\n");
#endif
        }


        if (trGold != 0) {
#if (NOISY_TEST == 1)
            printf("\tGold - Fail\n");
#endif
            failedDiscard++;
            passedAllTestsFlag = 0;
        }
        else {
#if (NOISY_TEST == 1)
            printf("\tGold - Pass\n");
#endif
        }

        if (trSilver != 0) {
#if (NOISY_TEST == 1)
            printf("\tSilver - Fail\n");
#endif
            failedDiscard++;
            passedAllTestsFlag = 0;
        }
        else {
#if (NOISY_TEST == 1)
            printf("\tSilver - Pass\n");
#endif
        }

        if (trCopper != 0) {
#if (NOISY_TEST == 1)
            printf("\tCopper - Fail\n");
#endif
            failedDiscard++;
            passedAllTestsFlag = 0;
        }
        else {
#if (NOISY_TEST == 1)
            printf("\tCopper - Pass\n");
#endif
        }


        if (passedAllTestsFlag == 1) {
#if (NOISY_TEST == 1)
            printf("\tAll tests passed!\n\n");
#endif
            numTestsPassed++;
        }

    }

    printf("Adventurer tests summary:\n");
    printf("\tPassed: %d\n", numTestsPassed);
    printf("\tFailed (draw): %d\n", testDraw);
    printf("\tFailed (discard): %d\n\n", failedDiscard);



    return 0;

}