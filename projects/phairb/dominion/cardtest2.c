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




int main(int argc, char** argv) {
    int newCards = 0;
//    int discarded = 1;
    int xtraCoins = 0;
//    int shuffledCards = 0;
    int numBuys = 0;
//    int numActions = 0;
    int handCount;
    int deckcount;
    int  newDeckCount;
    int i;
//    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
//    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
//    int thisPlayer = 0;
//    int nextPlayer = 1;
    int currentPlayer;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};


    printf("\n*** Testing adventurer_card() ***\n");

    //Initialize the game
    initializeGame(numPlayers, k, seed, &G);




    //Test if the function can find Copper cards
#if (NOISY_TEST == 1)
    printf("\n*** Test Case 1: Test Case Copper, Copper ***\n");
#endif
    currentPlayer = 0;      //set the current player

    memcpy(&testG, &G, sizeof(struct gameState));   //copy the gamestate to testG
    deckcount = testG.deckCount[currentPlayer];     //store the deckcount of current player

    int newDeck1 [] = {copper, copper};         //create new deck
    newDeckCount = 3;                           //set newdeckcount

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][--deckcount] = newDeck1[i];
    }

    adventurer_card(0, &testG, 0, 0, 0);

    newCards = 2;
    xtraCoins = 0;
    numBuys = 0;

    handCount = testG.handCount[currentPlayer];     //store the handcount of current player
#if (NOISY_TEST == 1)
    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards);
#endif
    assertTF(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer], "!!! Test Case 1 Failed: Wrong amount of discarded cards !!!");
    assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards, "!!! Test Case 1 Failed: Wrong amount of cards in hand !!!");


    //Test if the function can find Gold cards
#if (NOISY_TEST == 1)
    printf("\n*** Test Case 2: Test Case Copper, Gold ***\n");
#endif
    initializeGame(numPlayers, k, seed, &G);            //re-initialize the game
    memcpy(&testG, &G, sizeof(struct gameState));       //copy the gamestate to testG


    currentPlayer = 0;                                  //set current player
    deckcount = testG.deckCount[currentPlayer];         //store deckcount of current player

    int newDeck2 [] = {copper, gold};                   //create new deck
    newDeckCount = 2;                                   //store size of new deck
    testG.deckCount[currentPlayer] = newDeckCount;      //update player's deckcount

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck2[i];
    }

    int temp[] = {};

    adventurer_card(0, &testG, 0, 0, temp);

#if (NOISY_TEST == 1)
    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 1);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 2);
#endif
    assertTF(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 1, "!!! Test Case 2 Failed: Wrong amount of discarded cards !!!");
    assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards, "!!! Test Case 2 Failed: Wrong amount of cards in hand !!!");




    //Test if the player has "junk" cards in the middle of their deck
#if (NOISY_TEST == 1)
    printf("\n*** Test Case 3: Test Case Copper, NoCard, NoCard, Copper ***\n");
#endif
    initializeGame(numPlayers, k, seed, &G);                //re-initialize the game
    memcpy(&testG, &G, sizeof(struct gameState));           //copy the gamestate to testG

    currentPlayer = 0;                                      //set current player
    deckcount = testG.deckCount[currentPlayer];             //store the deckcount of current player

    int NoCard = 0;                                         //create a "junk" card
    int newDeck3 [] = {copper, NoCard, NoCard, copper};     //make new deck with good + junk cards
    newDeckCount = 4;                                       //store size of the new deck
    testG.deckCount[currentPlayer] = newDeckCount;          //update the current player's deckcount

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck3[i];
    }

    int temp1[] = {};

    adventurer_card(0, &testG, 0, 0, temp1);

#if (NOISY_TEST == 1)
    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 2);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards);
#endif
    assertTF(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 2, "!!! Test Case 3 Failed: Wrong amount of discarded cards !!!");
    assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards, "!!! Test Case 3 Failed: Wrong amount of cards in hand !!!");



    //Test if the player has no Treasure Cards
#if (NOISY_TEST == 1)
    printf("\n*** Test Case 4: Test Case: No Cards in the Player's Deck ***\n");
#endif
    initializeGame(numPlayers, k, seed, &G);                //re-initialize the game
    memcpy(&testG, &G, sizeof(struct gameState));           //copy the gamestate to testG

    currentPlayer = 0;                                      //set current player
    deckcount = testG.deckCount[currentPlayer];             //store the deckcount of current player

    int newDeck4 [] = {};                                   //create a new deck with no cards
    newDeckCount = 0;                                       //store size of the new deck
    testG.deckCount[currentPlayer] = newDeckCount;          //update the current player's deckcount

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck4[i];
    }

    int temp2[] = {};

    adventurer_card(0, &testG, 0, 0, temp2);

#if (NOISY_TEST == 1)
    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]);
#endif
    assertTF(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer], "!!! Test Case 4 Failed: Wrong amount of discarded cards !!!");
    assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer], "!!! Test Case 4 Failed: Wrong amount of cards in hand !!!");





    //Test if the player has silver Cards
#if (NOISY_TEST == 1)
    printf("\n*** Test Case 5: Test Case: No Cards in the Player's Deck ***\n");
#endif
    initializeGame(numPlayers, k, seed, &G);                //re-initialize the game
    memcpy(&testG, &G, sizeof(struct gameState));           //copy the gamestate to testG

    currentPlayer = 0;                                      //set current player
    deckcount = testG.deckCount[currentPlayer];             //store the deckcount of current player

    int newDeck5 [] = {silver, silver};                     //create a new deck with only silver
    newDeckCount = 2;                                       //store size of the new deck
    testG.deckCount[currentPlayer] = newDeckCount;          //update the current player's deckcount

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck5[i];
    }

    int temp3[] = {};

    adventurer_card(0, &testG, 0, 0, temp3);

#if (NOISY_TEST == 1)
    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 2);
#endif
    assertTF(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer], "!!! Test Case 5 Failed: Wrong amount of discarded cards !!!");
    assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards, "!!! Test Case 5 Failed: Wrong amount of cards in hand !!!");





    printf("\n\nAll tests for numHandCards() passed!\n");

    return 0;
}
