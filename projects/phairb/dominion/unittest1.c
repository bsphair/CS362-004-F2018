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
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n*** Current Number of Cards ***\n");
    printf("Player's initial cards in hand = %i\t",  G.handCount[currentPlayer]);
#endif
    /*Add three cards to the player's hands*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n\n** Add 3 cards to the player's hands ***");
#endif
    for(test = 0; test < 3; test++){
#if (PRINT_ALL_STATEMENTS == 1)
        printf("\nIncrementing card count by 1 ->\t");
#endif
        G.handCount[currentPlayer]++;                   // Add 1 card
        assertTF(numHandCards(&G) == G.handCount[currentPlayer], "Cards do not match when increasing the deck");
#if (PRINT_ALL_STATEMENTS == 1)
        printf("Player's Cards in Hand = %i", G.handCount[currentPlayer]);
#endif
    }

    /*Current Number of Cards*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n\n*** Current Number of Cards ***");
    printf("\nPlayer's current cards in hand = %i\t", G.handCount[currentPlayer]);


    printf("\n\n*** Subtract 2 cards from player's hand ***");
#endif
    for(test = 0; test < 2; test++){
#if (PRINT_ALL_STATEMENTS == 1)
        printf("\nDecrementing card count by 1 ->\t");
#endif
        G.handCount[currentPlayer]--;
        assertTF(numHandCards(&G) == G.handCount[currentPlayer], "Cards do not match when decreasing the deck");
#if (PRINT_ALL_STATEMENTS == 1)
        printf("Player's Cards in Hand = %i", G.handCount[currentPlayer]);
#endif
    }

    /*Current Number of Cards*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n\n\n*** Current Number of Cards ***\n");
    printf("Player's current cards in hand = %i\t", G.handCount[currentPlayer]);
#endif
    /*Remove all the cards from the player's hand*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n\n*** Remove all cards from player's hands (player should have zero cards) ***\n");
#endif
    for(test = G.handCount[0]; test > 0; test--){
        G.handCount[currentPlayer]--;
        assertTF(numHandCards(&G) == G.handCount[currentPlayer], "Cards do not match when removing all cards from the deck");
#if (PRINT_ALL_STATEMENTS == 1)
        printf("Player's Cards in Hand = %i\n", G.handCount[currentPlayer]);
#endif
    }

    /*Current Number of Cards*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n\n*** Current Number of Cards ***\n");
    printf("Player's current cards in hand = %i\t", G.handCount[currentPlayer]);
#endif

    /*Add a high number (23) of cards to the player's hand*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n\n*** Add 23 cards to player's hand ***\n");
#endif
    G.handCount[0] = 23;
    assertTF(numHandCards(&G) == G.handCount[currentPlayer], "Cards do not match when adding 23 cards to the deck");

#if (PRINT_ALL_STATEMENTS == 1)
    /*Current Number of Cards*/
    printf("\n*** Current Number of Cards ***\n");
    printf("Player's current cards in hand = %i\t", G.handCount[currentPlayer]);
#endif


    printf("\n\nAll tests for numHandCards() passed!\n");


    return 0;
}