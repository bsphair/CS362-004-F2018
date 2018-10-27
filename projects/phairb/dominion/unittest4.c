#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1



//Description: Function will print out error statement based on condition
int assertTrue(int condition, char* statement){
    if (condition != 1){
        printf("\n%s\n", statement);
        return 1;
    }
    return 0;
}



int main(int argc, char** argv){
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    /*Initialize the game*/
    initializeGame(numPlayers, k ,seed, &G);

    printf("\n*** Testing whoseTurn() ***\n\n");

#if (NOISY_TEST == 1)
    printf("\n*** Testing if Player 1 starts the game ***.\n\n");
#endif

    //Test if player one is the first player of the game
    currentPlayer = 0;
    G.whoseTurn = currentPlayer;    //set player 1 as the player of the game
    assertTrue(whoseTurn(&G) == 0, "Player one did not start the game");    //test if player 1 is the player
#if (NOISY_TEST == 1)
    printf("Current Player: %i \t Expected Player: %i\n", whoseTurn(&G) + 1, currentPlayer + 1);
#endif

#if (NOISY_TEST == 1)
    printf("\n\n*** Testing if Player 2 starts the game ***.\n\n");
#endif


    //Test if player one is the first player of the game
    currentPlayer = 1;
    G.whoseTurn = currentPlayer;    //set player 1 as the player of the game
    assertTrue(whoseTurn(&G) == 1, "Player two did not start the game");    //test if player 1 is the player
#if (NOISY_TEST == 1)
    printf("Current Player: %i \t Expected Player: %i\n", whoseTurn(&G) + 1, currentPlayer + 1);
#endif



    //Test if whoseTurn updates when the function endTurn is called
#if (NOISY_TEST == 1)
    printf("\n\n*** Reseting current player to Player 1 ***.\n");
#endif
    currentPlayer = 0;
    G.whoseTurn = currentPlayer;    //set player 1 as the player of the game
#if (NOISY_TEST == 1)
    printf("Current Player: %i\n", whoseTurn(&G) + 1);
#endif
    endTurn(&G);
    assertTrue(whoseTurn(&G) == 1, "Player one's turn did not end properly");    //test if player 1 is the player
#if (NOISY_TEST == 1)
    printf("Current Player After Ending Turn: %i \t Expected Player: %i\n", whoseTurn(&G) + 1, 2);
    printf("\nTest for Player 2 to make a turn:\n");
#endif
#if (NOISY_TEST == 1)
    printf("Current Player: %i\n", whoseTurn(&G) + 1);
#endif
    endTurn(&G);
    assertTrue(whoseTurn(&G) == 0, "Player one's turn did not end properly");    //test if player 1 is the player
#if (NOISY_TEST == 1)
    printf("Current Player After Ending Turn: %i \t Expected Player: %i\n", whoseTurn(&G) + 1, 1);
#endif








    printf("\n\nAll tests for whoseTurn() passed!\n");


    return 0;
}