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
        printf("\n!!!%s!!!\n", statement);
        return 1;
    }
    return 0;
}


void printPassedOrFailed(int error){
    if(error == 0){
        printf("Passed: ");
    }
    else{
        printf("Failed: ");
    }
}



int main(int argc, char** argv) {
    int deckcount;
    int newDeckCount;
    int error = 0;
    int handCount;
//    int alltests = 0;
    int newCards = 2;
//    int played = 1;
//    int treasureCount = 0;
//    int treasureCards = 0;
//    int treasureCards2 = 0;
    int a;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = { adventurer, embargo, village, minion, gold,
                  silver,     sea_hag, tribute, smithy, copper };


    printf("\n*** Testing adventurer_card() ***\n");


    //Initialize the game
    initializeGame(numPlayers, k, seed, &G);


    /* VERIFY THE HAND COUNT */

    printf("\n*** Test Case 1: Verify Hand Count ***\n");

    memcpy(&testG, &G, sizeof(struct gameState));       //reset game

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus); //play adventurer card

    //test if the hand count is correct
    error = assertTF(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards, "ERROR: Wrong hand count");
    printPassedOrFailed(error);
    printf("Actual = %d, Expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);




    /* VERIFY THE DECK COUNT */

    printf("\n*** Test Case 2: Verify Deck Count ***\n");

    memcpy(&testG, &G, sizeof(struct gameState)); //reset game

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus); //play adventurer card

    //test if the deck count is correct
    error = assertTF(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards, "ERROR: Wrong deck count");
    printPassedOrFailed(error);
    printf("Actual = %d, Expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);



    /* Test Deck of Two Copper Cards */

    printf("\n*** Test Case 3: Test Two Copper Cards in Hand ***\n");

    memcpy(&testG, &G, sizeof(struct gameState));       //reset the game

    deckcount = testG.deckCount[0];
    int newDeck1[] = {copper, copper};

    newDeckCount = 3;

    for(a = 0; a < newDeckCount; a++){
        testG.deck[0][--deckcount] = newDeck1[a];
    }

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);     //play adventurer card

    handCount = testG.handCount[0];

    error = assertTF(testG.discardCount[0] == G.discardCount[0], "ERROR: Wrong amount of discard cards");
    printPassedOrFailed(error);
    printf("Actual Discard Count: %i  Expected Discard Count %i\n", testG.discardCount[0], G.discardCount[0]);


    error = assertTF(testG.handCount[0] == G.handCount[0] + 2, "ERROR: Wrong amount of cards in hand !!!");
    printPassedOrFailed(error);
    printf("Actual Handcount: %i \t  Expected Handcount: %i\n", testG.handCount[0], G.handCount[0] + 2);




    /* Test if function can find Gold cards */

#if (NOISY_TEST == 1)
    printf("\n*** Test Case 4: Test Hand of Copper and Gold ***\n");
#endif

    memcpy(&testG, &G, sizeof(struct gameState));       //reset the game
    deckcount = testG.deckCount[0];                     //reset the deck count

    int newDeck2 [] = {copper, gold};                   //create new deck
    newDeckCount = 2;                                   //store size of new deck
    testG.deckCount[0] = newDeckCount;                  //update player's deckcount

    for(a = 0; a < newDeckCount; a++){
        testG.deck[0][a] = newDeck2[a];
    }

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);     //play adventurer card

    printPassedOrFailed(assertTF(testG.discardCount[0] == G.discardCount[0] + 1, "Test Case 4 ERROR: Wrong amount of discarded cards"));
    printf("Actual Discard Count: %i Expected Discard Count: %i\n", testG.discardCount[0], G.discardCount[0] + 1);

    printPassedOrFailed(assertTF(testG.handCount[0] == G.handCount[0] + newCards, "Test Case 4 ERROR: Wrong amount of cards"));
    printf("Actual Handcount: %i \t\tExpected Handcount: %i\n", testG.handCount[0], G.handCount[0] + 2);




    //Test if the player has "junk" cards in the middle of their deck

#if (NOISY_TEST == 1)
    printf("\n*** Test Case 5: Test Hand of Copper and \"Junk\" cards ***");
#endif

    memcpy(&testG, &G, sizeof(struct gameState));       //reset the game
    deckcount = testG.deckCount[0];                     //reset the deck count

    int NoCard = 0;
    int newDeck3 [] = {copper, NoCard, NoCard, copper};                   //create new deck
    newDeckCount = 4;                                   //store size of new deck
    testG.deckCount[0] = newDeckCount;                  //update player's deckcount

    for(a = 0; a < newDeckCount; a++){
        testG.deck[0][a] = newDeck3[a];
    }

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);     //play adventurer card

    printPassedOrFailed(assertTF(testG.discardCount[0] == G.discardCount[0] + 1, "Test Case 5 ERROR: Wrong amount of discarded cards"));
    printf("Actual Discard Count: %i Expected Discard Count: %i\n", testG.discardCount[0], G.discardCount[0] + 1);

    printPassedOrFailed(assertTF(testG.handCount[0] == G.handCount[0] + newCards, "Test Case 5 ERROR: Wrong amount of cards"));
    printf("Actual Handcount: %i \t\tExpected Handcount: %i\n", testG.handCount[0], G.handCount[0] + 2);




    //Test if the player has no Treasure Cards
#if (NOISY_TEST == 1)
    printf("\n*** Test Case 6: Test Hand of Copper and \"Junk\" cards ***");
#endif

    memcpy(&testG, &G, sizeof(struct gameState));       //reset the game
    deckcount = testG.deckCount[0];                     //reset the deck count

    int newDeck4 [] = {};                                   //create a new deck with no cards
    newDeckCount = 0;                                       //store size of the new deck
    testG.deckCount[0] = newDeckCount;          //update the current player's deckcount

    for(a = 0; a < newDeckCount; a++){
        testG.deck[0][a] = newDeck4[a];
    }

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);     //play adventurer card

    printPassedOrFailed(assertTF(testG.discardCount[0] == G.discardCount[0] + 1, "Test Case 6 ERROR: Wrong amount of discarded cards"));
    printf("Actual Discard Count: %i Expected Discard Count: %i\n", testG.discardCount[0], G.discardCount[0] + 1);

    printPassedOrFailed(assertTF(testG.handCount[0] == G.handCount[0] + newCards, "Test Case 6 ERROR: Wrong amount of cards"));
    printf("Actual Handcount: %i \t\tExpected Handcount: %i\n", testG.handCount[0], G.handCount[0] + 2);




    //Test if the player has silver Cards
#if (NOISY_TEST == 1)
    printf("\n*** Test Case 7: Test Case: No Cards in the Player's Deck ***\n");
#endif

    memcpy(&testG, &G, sizeof(struct gameState));       //reset the game
    deckcount = testG.deckCount[0];                     //reset the deck count

    int newDeck5 [] = {silver, silver};                     //create a new deck with only silver
    newDeckCount = 2;                                       //store size of the new deck
    testG.deckCount[0] = newDeckCount;          //update the current player's deckcount

    for(a = 0; a < newDeckCount; a++){
        testG.deck[0][a] = newDeck5[a];
    }

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);     //play adventurer card

    printPassedOrFailed(assertTF(testG.discardCount[0] == G.discardCount[0] + 1, "Test Case 6 ERROR: Wrong amount of discarded cards"));
    printf("Actual Discard Count: %i Expected Discard Count: %i\n", testG.discardCount[0], G.discardCount[0] + 1);

    printPassedOrFailed(assertTF(testG.handCount[0] == G.handCount[0] + newCards, "Test Case 6 ERROR: Wrong amount of cards"));
    printf("Actual Handcount: %i \t\tExpected Handcount: %i\n", testG.handCount[0], G.handCount[0] + 2);





    return 0;
}
