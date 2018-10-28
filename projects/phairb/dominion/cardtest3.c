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

int assertTF(int condition, char* statement){

    if(condition != 1){
        printf("%s\n\n", statement);
        return 1;
    }
    return 0;
}




int main(int argc, char** argv) {
    int error = 0;
    int handCount;
    int deckcount;
    int handPos = 0;
    int a;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};


    printf("\n*** Testing village_card() ***\n");

    initializeGame(numPlayers, k, seed, &G);            //initialize the game
    memcpy(&testG, &G, sizeof(struct gameState));       //copy gamestate to testG

#if (NOISY_TEST == 1)
    printf("\n*** Test Case 1: ***\n");


    printf("Original Discard Count: %i\n", testG.discardCount[currentPlayer]);
    printf("Original Handcount: %i\n", testG.handCount[currentPlayer]);
    printf("Original Actions: %i\n", testG.numActions);
#endif
    for(a = 0; a < 2; a++){
#if (NOISY_TEST == 1)
        printf("\n* Test 1.%i\n", a + 1);
        printf("* Increase Discard by 1 *\n");
        printf("* Increase Handcount by 1 *\n");
        printf("* Increase Actions by 2 *\n");
#endif
        deckcount = testG.deckCount[currentPlayer];         //store deckcount of current player

        village_card(&testG, currentPlayer, handPos);

        handCount = testG.handCount[currentPlayer];         //store handcount of current player

#if (NOISY_TEST == 1)
        printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + a + 1);
        printf("Actual Handcount: %i \t\t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + a + 1);
        printf("Actual Actions: %i \t\t Expected Actions: %i\n", testG.numActions, G.numActions + (a + 1) * 2);
#endif
        error = assertTF(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + a + 1, "!!! Test Case 1 Failed: Wrong amount of discarded cards !!!");
        error = assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + a + 1, "!!! Test Case 1 Failed: Wrong amount of cards in hand !!!");
        error = assertTF(testG.numActions == G.numActions + (a + 1) * 2, "!!! Test Case 1 Failed: Wrong amount of number of actions !!!");
    }

    memcpy(&testG, &G, sizeof(struct gameState));       //copy gamestate to testG



    //Test adding extra actions
#if (NOISY_TEST == 1)
    printf("\n\n*** Test Case 2: Testing Extra Actions***\n");
#endif
    currentPlayer = 0;
#if (NOISY_TEST == 1)
    printf("\nOriginal Discard Count: %i\n", testG.discardCount[currentPlayer]);
    printf("Original Handcount: %i\n", testG.handCount[currentPlayer]);
    printf("Original Actions: %i\n", testG.numActions);

    printf("* Adding 1 Action to the player. *\n");
#endif
    testG.numActions++;     //increase the number of actions by one
#if (NOISY_TEST == 1)
    printf("Updated Actions: %i\n\n", testG.numActions);
#endif

    deckcount = testG.deckCount[currentPlayer];     //store deckcount of current player

    village_card(&testG, currentPlayer, handPos);

    handCount = testG.handCount[currentPlayer];     //store handcount of current player
#if (NOISY_TEST == 1)
    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 1);
    printf("Actual Handcount: %i \t\t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 1);
    printf("Actual Actions: %i \t\t Expected Actions: %i\n", testG.numActions, G.numActions + 2);
#endif
    error = assertTF(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 1, "!!! Test Case 1 Failed: Wrong amount of discarded cards !!!");
    error = assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + 2, "!!! Test Case 1 Failed: Wrong amount of cards in hand !!!");
    error = assertTF(testG.numActions == G.numActions + 2, "!!! Test Case 1 Failed: Wrong amount of number of actions !!!");





    memcpy(&testG, &G, sizeof(struct gameState));

    //Test the upper boundary of Actions
#if (NOISY_TEST == 1)
    printf("\n\n*** Test Case 2: Testing Upper Boundary of Actions***\n");
#endif
    currentPlayer = 0;

#if (NOISY_TEST == 1)
    printf("\nOriginal Discard Count: %i\n", testG.discardCount[currentPlayer]);
    printf("Original Handcount: %i\n", testG.handCount[currentPlayer]);
    printf("Original Actions: %i\n", testG.numActions);

    printf("* Adding 1 Action to the player. *\n");
#endif
    testG.numActions = 100;     //increase the number of actions by one
#if (NOISY_TEST == 1)
    printf("Updated Actions: %i\n\n", testG.numActions);
#endif

    deckcount = testG.deckCount[currentPlayer];     //store deckcount of current player

    village_card(&testG, currentPlayer, handPos);

    handCount = testG.handCount[currentPlayer];     //store handcount of current player
#if (NOISY_TEST == 1)
    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 1);
    printf("Actual Handcount: %i \t\t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 1);
    printf("Actual Actions: %i \t\t Expected Actions: %i\n", testG.numActions, G.numActions + 101);
#endif
    error = assertTF(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 1, "!!! Test Case 1 Failed: Wrong amount of discarded cards !!!");
    error = assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + 1, "!!! Test Case 1 Failed: Wrong amount of cards in hand !!!");
    error = assertTF(testG.numActions == G.numActions + 101, "!!! Test Case 1 Failed: Wrong amount of number of actions !!!");




    if(error == 0) {
        printf("\n\nAll tests for numHandCards() passed!\n");
    }

    return 0;
}