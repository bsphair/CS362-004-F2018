/* Author: Brian Phair
 * Description: Tests the great hall card in dominion.c
 * */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

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
    int numTestsPassed = 0, passedAllTestsFlag = 0, currPlayer = 0, failedHandCount = 0, failedActionsCount = 0, i = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
    int numPlayers = 2;
    int seed = 1000;
    int numberOfTests = 50000;
    int deckSize, handSize, startHand, currHand, startNumActions, currNumActions;
    int allowedCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

    struct gameState G;
    double time_spent = 0.0;

    srand(time(NULL));              //for random seeding
    clock_t begin = clock();        //start recording time

    //loop for the number of desired tests
    for (i = 0; i < numberOfTests; i++) {
        passedAllTestsFlag = 1;

        initializeGame(numPlayers, allowedCards, seed, &G);     //initialize the game

        deckSize = rand() % (MAX_DECK + 1);     //randomize size of deck
        handSize = rand() % (deckSize + 1);     //randomize size of hand
        G.numActions = rand() % 10;             //randomize number of actions


        G.deckCount[0] = deckSize - handSize;   //store the deck size
        G.handCount[0] = handSize;              //store the player's hand size

        handPos = G.hand[currPlayer][G.handCount[currPlayer]-1];

        startHand = G.handCount[0];
        startNumActions = G.numActions;

        cardEffect(great_hall, choice1, choice2, choice3, &G, handPos, &bonus); //play the great_hall card


        currHand = G.handCount[0];          //get the player's handcount
        currNumActions = G.numActions;      //get the number of actions

        if (rand() % 100 == 1) {
            currNumActions += 1;
        }

#if (NOISY_TEST == 1)
        printf("*** Testing the Great Hall card ***\n");
#endif



        //Test the hand count
        if (assertTF(currHand == startHand,"Wrong number of cards drawn")) {            //if the current hand count doesn't match the starting hand count
#if (NOISY_TEST == 1)
            printf("\tCards drawn - Fail\n");
#endif
            failedHandCount++;
            passedAllTestsFlag = 0;
        }
        else {                                  // the current hand count matches the starting hand count
#if (NOISY_TEST == 1)
            printf("\tCards drawn - Pass\n");
#endif
        }





        //Test the number of actions
        if (assertTF(currNumActions == (startNumActions + 1), "Wrong number of actions")) {    //if the number of actions is incorrect
#if (NOISY_TEST == 1)
            printf("\tActions - Fail\n");
#endif
            failedActionsCount++;
            passedAllTestsFlag = 0;
        }
        else {                                          //correct number of actions
#if (NOISY_TEST == 1)
            printf("\tActions - Pass\n");
#endif
        }



        //if all the tests have passed, print out message
        if (passedAllTestsFlag == 1) {
#if (NOISY_TEST == 1)
            printf("\tAll tests passed!\n\n");
#endif
            numTestsPassed++;       //add to the number of tests passed
        }

    }


    clock_t end = clock();                                  //get time
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   //calculate the run time of the tests

    printf("Great Hall tests summary:\n");
    printf("\tPassed: %d\n", numTestsPassed);
    printf("\tFailed (hand): %d\n", failedHandCount);
    printf("\tFailed (actions): %d\n\n", failedActionsCount);

    printf("Time elapsed is %f seconds", time_spent);


    return 0;

}