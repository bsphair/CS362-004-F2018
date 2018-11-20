/* Author: Brian Phair
 * Description: Tests cases for "Smithy" card located in dominion.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define TESTCARD "SMITHY"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int assertTF(int condition, char* statement){

    if(condition != 1){
        printf("%s\n\n", statement);
        return 1;
    }
    return 0;
}



int main(int argc, char** argv) {
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G, testG;
    int k[10] = { adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room };
    int i;
    int newCards = 3;
    int played   = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int thisPlayer = 0;
    int error = 0;
    int alltests = 0;

    /*Initialize the game*/
    initializeGame(numPlayers, k, seed, &G);

    printf("\n*** Testing smithy_card() ***\n");

    memcpy(&testG, &G, sizeof(struct gameState));


    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        if (testG.hand[thisPlayer][i] == smithy) {
            handpos = i;
            break;
        }
    }

    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);     //play the card

#if(NOISY_TEST == 1)
    printf("\n*** Verify Smithy Card Usage ***\n");
#endif

    error = assertTF(testG.playedCardCount == G.playedCardCount + 1, "ERROR: Wrong card usage");

    if (error == 0) {           //correct card usage
#if(NOISY_TEST == 1)
        printf("Passed: ");
#endif
    }
    else {                      //wrong card usage
#if(NOISY_TEST == 1)
        printf("Failed: ");
#endif
        alltests = 1;
    }
#if(NOISY_TEST == 1)
    printf("Actual = %d, Expected = %d\n", testG.playedCardCount, G.playedCardCount + played);
#endif




    /* VERIFY HAND COUNT */

    memcpy(&testG, &G, sizeof(struct gameState));   //restart game

    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        if (testG.hand[thisPlayer][i] == smithy) {
            handpos = i;
            break;
        }
    }

    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);     //play Smithy card

#if(NOISY_TEST == 1)
    printf("\n*** Verify Hand Count ***\n");
#endif

    error = assertTF(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - played, "ERROR: Wrong hand count");

    if (error == 0) {       //correct hand count
#if(NOISY_TEST == 1)
        printf("Passed: ");
#endif
    }
    else {                  //wrong hand count
#if(NOISY_TEST == 1)
        printf("Failed: ");
#endif
        alltests = 1;
    }
#if(NOISY_TEST == 1)
    printf("Actual = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - played);
#endif




    /* VERFIY DECK COUNT */

#if(NOISY_TEST == 1)
    printf("\n*** Verify Deck Count ***\n");
#endif

    memcpy(&testG, &G, sizeof(struct gameState));  //restart game

    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        if (testG.hand[thisPlayer][i] == smithy) {
            handpos = i;
            break;
        }
    }

    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);     //play Smithy card

    error = assertTF(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards, "ERROR: Wrong deck count");

    if (error == 0) {       //correct deck count
#if(NOISY_TEST == 1)
        printf("Passed: ");
#endif
    }
    else {                  //wrong deck count
#if(NOISY_TEST == 1)
        printf("Failed: ");
#endif
        alltests = 1;
    }
#if(NOISY_TEST == 1)
    printf("Actual = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
#endif




    /* VERFIY DISCARD COUNT */

#if(NOISY_TEST == 1)
    printf("\n*** Verify Discard Count ***\n");
#endif

    memcpy(&testG, &G, sizeof(struct gameState));       //restart game

    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        if (testG.hand[thisPlayer][i] != smithy) {
            testG.hand[thisPlayer][i] = smithy;
            handpos = i;
            break;
        }
    }

    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);     //play Smithy card

    error = assertTF(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + played, "ERROR: Wrong discard count");

    if (error == 0) {       //Correct number of discards
#if(NOISY_TEST == 1)
        printf("Passed: ");
#endif
    }
    else {                  //Wrong number of discards
#if(NOISY_TEST == 1)
        printf("Failed: ");
#endif
        alltests = 1;
    }
#if(NOISY_TEST == 1)
    printf("Actual = %d, Expected = %d\n\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + played);
#endif



    //print a message based on testing results
    if(alltests == 0){
        printf("ALL TESTS PASSED!!!\n\n");
    }
    else{
        printf("Errors have occurred.\n\n");
    }

    return 0;
}
