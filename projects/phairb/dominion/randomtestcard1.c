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



int assertTF(int condition, char* statement1){

    if(condition != 1){
#if (NOISY_TEST == 1)
        printf("\t*** %s ***\n", statement1);
#endif
        return 1;
    }
    else{
        return 0;
    }
}



int main () {
    int numTestsPassed = 0, passedAllTestsFlag = 0, currPlayer = 0, failedDeckCount = 0, failedHandCount = 0, failedDiscardCount = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0, i = 0;
    int seed = 1000;
    int numPlayers = 2;
    int numberOfTests = 50000;
    int deckSize, handSize, startDeck, currDeck, startHand, currHand, startDiscard, currDiscard;
    int allowedCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    struct gameState G;
    double time_spent = 0.0;

    srand(time(NULL));
    clock_t begin = clock();


    //loop for number of tests
    for (i = 0; i < numberOfTests; i++) {

        initializeGame(numPlayers, allowedCards, seed, &G);     //initialize the game

        deckSize = rand() % (MAX_DECK + 1);     //randomize size of deck
        handSize = rand() % (deckSize + 1);     //randomize size of hand

        G.deckCount[0] = deckSize - handSize;   //update the deck count
        G.handCount[0] = handSize;              //update the hand count
        handPos = G.hand[currPlayer][G.handCount[currPlayer]-1];

        //store the initial deck count, hand count, and discard count amounts
        startDeck = G.deckCount[0];     //store deck count
        startHand = G.handCount[0];     //store hand count
        startDiscard = G.playedCardCount;   //store discard count

        cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);     //"Play" the smithy card

        //store the updated deck count, hand count, and discard count amounts after the card has been played
        currDeck = G.deckCount[0];      //store deck count
        currHand = G.handCount[0];      //store hand count
        currDiscard = G.playedCardCount;    //store discard count

        passedAllTestsFlag = 1;     //reset to 1 -> tests have passed


#if (NOISY_TEST == 1)
        printf("*** Testing Smithy card ***\n");
#endif



        //test if the smithy card decreased deck count by 3 cards
        if (assertTF( currDeck == (startDeck - 3) ,"Deck count not decreased by 3")) {      //deck count is wrong, test failed
#if (NOISY_TEST == 1)
            printf("\tDeck count - Fail\n");
#endif
            failedDeckCount++;
            passedAllTestsFlag = 0;
        }
        else {          //deck count is correct, test passed
#if (NOISY_TEST == 1)
            printf("\tDeck count - Pass\n");
#endif
        }





        //test if the smithy card increased the hand count by 2
        if (assertTF( currHand == (startHand + 2) ,"Wrong number of cards drawn")) {      //hand size is wrong, test failed
#if (NOISY_TEST == 1)
            printf("\tCards drawn - Fail\n");
#endif
            failedHandCount++;
            passedAllTestsFlag = 0;
        }
        else {              //hand size is correct, test passed
#if (NOISY_TEST == 1)
            printf("\tCards drawn - Pass\n");
#endif
        }





        //test if the smithy card discarded the correct number of cards
        if (assertTF( currDiscard == (startDiscard + 1), "Wrong number of cards discarded")) {        //discard amount is wrong, test failed
#if (NOISY_TEST == 1)
            printf("\tCards discarded - Fail\n");
#endif
            failedDiscardCount++;
            passedAllTestsFlag = 0;
        }
        else {                  //discard count is correct, test passed
#if (NOISY_TEST == 1)
            printf("\tCards discarded - Pass\n");
#endif
        }




        //all the tests passed
        if (passedAllTestsFlag == 1) {
#if (NOISY_TEST == 1)
            printf("All tests passed!\n");
#endif
            numTestsPassed++;
        }

    }

    clock_t end = clock();                                  //get time
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   //calculate the run time of the tests

    printf("Smithy tests summary:\n");
    printf("\tPassed: %d\n", numTestsPassed);
    printf("\tFailed (deck): %d\n", failedDeckCount);
    printf("\tFailed (hand): %d\n", failedHandCount);
    printf("\tFailed (discard): %d\n\n", failedDiscardCount);

    printf("Time elapsed is %f seconds", time_spent);

    return 0;

}