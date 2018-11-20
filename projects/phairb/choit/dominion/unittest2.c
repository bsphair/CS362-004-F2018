#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define PRINT_ALL_STATEMENTS 1

void printCardAmount(struct gameState G){
#if (PRINT_ALL_STATEMENTS == 1)
    printf("Current Card Status:\n");
    printf("Player 1 = %i cards\n", G.handCount[0]);
    printf("Player 2 = %i cards\n", G.handCount[1]);
#endif
}

int assertTrue(int condition, char* statement){
    if (condition != 1){
        printf("\n%s\n", statement);
        return 1;
    }
    return 0;
}


int drawOneCard(struct gameState G, int player, int correctNumber){
    int error = 0;
    drawCard(player, &G);
    error = assertTrue(G.handCount[player] == correctNumber, "Failed to increment card by 1.");
#if (PRINT_ALL_STATEMENTS == 1)
    printCardAmount(G);
#endif
    return error;
}


int main(int argc, char** argv) {
    int seed = 1000;
    int numPlayers = 2;
    int playerOne = 0;
    int playerTwo = 1;
    int error = 0;
    int x = 0;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    /*Initialize the game*/
    initializeGame(numPlayers, k ,seed, &G);

    printf("\n*** Testing drawCard() ***\n\n");

#if (PRINT_ALL_STATEMENTS == 1)
    printf("Number of players used for testing is 2 players. The first player will originally have 5 cards while the second player will have 0 cards.\n\n");
#endif

    /*Initial cards*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("Initial amount of cards\n");
    printCardAmount(G);
#endif

    /*Player 1 draws 1 card*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n** Player 1 will draw one card **\n");
#endif
    error = drawOneCard(G, playerOne, 6);

    /*Player 1 draws to 10 cards*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n** Player 1 draw cards until 10 cards in hand **\n");
#endif
    for(x = G.handCount[playerOne]; x < 10; x++){
        error = drawCard(playerOne, &G);
    }
    error = assertTrue(G.handCount[playerOne] == 10, "Failed to add cards until 10 cards in hand.");
#if (PRINT_ALL_STATEMENTS == 1)
    printCardAmount(G);
#endif


    /*Player 2 draws 1 card*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n** Player 2 will draw one card **\n");
#endif
    error = drawOneCard(G, playerTwo, 1);


    /*Player 2 draws to 10 cards*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n** Player 1 draw cards until 10 cards in hand **\n");
#endif
    for(x = G.handCount[playerTwo]; x < 10; x++){
        error = drawCard(playerTwo, &G);
    }
    error = assertTrue(G.handCount[playerTwo] == 10, "Failed to add cards until 10 cards in hand.");
#if (PRINT_ALL_STATEMENTS == 1)
    printCardAmount(G);
#endif


    /*Player 1 tries to draw 1 card past 10*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n** Player 1 will draw one card with 10 cards in hand. Since hand is full, function should not draw anymore cards. **\n");
#endif
    error = drawOneCard(G, playerOne, 10);

    /*Player 2 tries to draw 1 card past 10*/
#if (PRINT_ALL_STATEMENTS == 1)
    printf("\n** Player 2 will draw one card with 10 cards in hand. Since hand is full, function should not draw anymore cards. **\n");
#endif
    error = drawOneCard(G, playerTwo, 10);



    if(error == 0){
        printf("\nAll tests passed!\n\n");
    }
    else{
        printf("Tests not passed.\n");
    }

    return 0;
}