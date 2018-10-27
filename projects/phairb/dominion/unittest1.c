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
#define PRINT_ALL_STATEMENTS 1

void assertTF(int condition, char* statement){

    if(condition != 1){
        printf("\n\n%s\n\n", statement);
    }
}



int main(int argc, char** argv){
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int test;

    /*Initialize the game*/
    initializeGame(numPlayers, k ,seed, &G);

    printf("\n*** Test numHandsCards() ***\n");

    printf("\n*** Current Number of Cards ***\n");
    printf("Player's initial cards in hand = %i\t",  G.handCount[currentPlayer]);

    /*Add three cards to the player's hands*/
    printf("\n\n** Add 3 cards to the player's hands ***");

    for(test = 0; test < 3; test++){
        printf("\nIncrementing card count by 1 ->\t");
        G.handCount[currentPlayer]++;                   // Add 1 card
        assertTF(numHandCards(&G) == G.handCount[currentPlayer], "Cards do not match when increasing the deck");
        printf("Player's Cards in Hand = %i", G.handCount[currentPlayer]);
    }

    /*Current Number of Cards*/
    printf("\n\n*** Current Number of Cards ***");
    printf("\nPlayer's current cards in hand = %i\t", G.handCount[currentPlayer]);


    printf("\n\n*** Subtract 2 cards from player's hand ***");

    for(test = 0; test < 2; test++){
        printf("\nDecrementing card count by 1 ->\t");
        G.handCount[currentPlayer]--;
        assertTF(numHandCards(&G) == G.handCount[currentPlayer], "Cards do not match when decreasing the deck");
        printf("Player's Cards in Hand = %i", G.handCount[currentPlayer]);
    }

    /*Current Number of Cards*/
    printf("\n\n\n*** Current Number of Cards ***\n");
    printf("Player's current cards in hand = %i\t", G.handCount[currentPlayer]);

    /*Remove all the cards from the player's hand*/
    printf("\n\n*** Remove all cards from player's hands (player should have zero cards) ***\n");
    for(test = G.handCount[0]; test > 0; test--){
        G.handCount[currentPlayer]--;
        assertTF(numHandCards(&G) == G.handCount[currentPlayer], "Cards do not match when removing all cards from the deck");
        printf("Player's Cards in Hand = %i\n", G.handCount[currentPlayer]);
    }

    /*Current Number of Cards*/
    printf("\n\n*** Current Number of Cards ***\n");
    printf("Player's current cards in hand = %i\t", G.handCount[currentPlayer]);


    /*Add a high number (23) of cards to the player's hand*/
    printf("\n\n*** Add 23 cards to player's hand ***\n");
    G.handCount[0] = 23;
    assertTF(numHandCards(&G) == G.handCount[currentPlayer], "Cards do not match when adding 23 cards to the deck");

    /*Current Number of Cards*/
    printf("\n*** Current Number of Cards ***\n");
    printf("Player's current cards in hand = %i\t", G.handCount[currentPlayer]);



    printf("\n\nAll tests for numHandCards() passed!\n");


    return 0;
}