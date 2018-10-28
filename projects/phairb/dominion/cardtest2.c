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


//void testCopperCopper(struct gameState G, struct gameState testG, int currentPlayer){
//    int deckcount = testG.deckCount[currentPlayer];
//    int i;
//    int newDeck1 [] = {copper, copper};
//    int newDeckCount = 3;
//
//    for(i = 0; i < newDeckCount; i++){
//        testG.deck[currentPlayer][--deckcount] = newDeck1[i];
//    }
//
//    adventurer_card(currentPlayer, &testG, 0, 0, 0);
//
//    int newCards = 2;
//    int xtraCoins = 0;
//    int numBuys = 0;
//
//    int handCount = testG.handCount[currentPlayer];
//
//    printf("\n\tPlayer %i:\n", currentPlayer + 1);
//    printf("TestG Handcount: %i \t G Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards);
//}



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

    initializeGame(numPlayers, k, seed, &G);



    printf("\n\n*** Test based on the Treasure cards in hand ***\n");



    //Test if the function can find Copper cards
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
    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards);



    //Test if the function can find Gold cards
    printf("\n*** Test Case Copper, Gold ***\n");
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));


    currentPlayer = 0;
    deckcount = testG.deckCount[currentPlayer];

    int newDeck2 [] = {copper, gold};
    newDeckCount = 2;
    testG.deckCount[currentPlayer] = newDeckCount;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck2[i];
    }

    int temp[] = {};

    adventurer_card(0, &testG, 0, 0, temp);

    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 1);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 2);
    assertTF(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + 2, "!!! Wrong number of cards in the player's hand !!!");





    //Test if the player has "junk" cards in the middle of their deck
    printf("\n*** Test Case Copper, NoCard, NoCard, Copper ***\n");
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = 0;
    deckcount = testG.deckCount[currentPlayer];

    int NoCard = 0;
    int newDeck3 [] = {copper, NoCard, NoCard, copper};
    newDeckCount = 4;
    testG.deckCount[currentPlayer] = newDeckCount;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck3[i];
    }

    int temp1[] = {};

    adventurer_card(0, &testG, 0, 0, temp1);

    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 2);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards);




    //Test if the player has no Treasure Cards
    printf("\n*** Test Case: No Cards in the Player's Deck ***\n");
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = 0;
    deckcount = testG.deckCount[currentPlayer];

    int newDeck4 [] = {};
    newDeckCount = 0;
    testG.deckCount[currentPlayer] = newDeckCount;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck4[i];
    }

    int temp2[] = {};

    adventurer_card(0, &testG, 0, 0, temp2);

    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]);




    //Test if the player has silver Cards
    printf("\n*** Test Case: No Cards in the Player's Deck ***\n");
    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = 0;
    deckcount = testG.deckCount[currentPlayer];

    int newDeck5 [] = {silver, silver};
    newDeckCount = 2;
    testG.deckCount[currentPlayer] = newDeckCount;

    for(i = 0; i < newDeckCount; i++){
        testG.deck[currentPlayer][i] = newDeck5[i];
    }

    int temp3[] = {};

    adventurer_card(0, &testG, 0, 0, temp3);

    printf("Actual Discard Count: %i \t Expected Discard Count: %i\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
    printf("Actual Handcount: %i \t Expected Handcount: %i\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 2);






    printf("\n\nAll tests for numHandCards() passed!\n");

    return 0;
}
