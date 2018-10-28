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
    int seed = 1000;
    int numPlayers = 2;
    struct gameState G;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int a;
    int currentHandCount;


    /*Initialize the game*/
    initializeGame(numPlayers, k ,seed, &G);

    printf("\n*** Testing smithy_card() ***\n");

    for(a = 0; a < numPlayers; a++){
#if (NOISY_TEST == 1)
        printf("\t\tPlayer %i\n", a);
#endif
        currentHandCount = G.handCount[a];
        smithy_card(a, &G, 0);
        printf("Actual Cards: %i \t Expected Cards: %i\n", G.handCount[a], currentHandCount + 3);
        assertTF(G.handCount[a] == currentHandCount + 3, "Error: Wrong number of cards!");
    }

#if (NOISY_TEST == 1)
    printf("\n*** Test the affect of handPos ***\n");
#endif

    //re-initialize the game
    initializeGame(numPlayers, k ,seed, &G);

    for(a = 0; a < numPlayers; a++){
#if (NOISY_TEST == 1)
        printf("\t\tPlayer %i\n", a);
#endif
        currentHandCount = G.handCount[a];
        smithy_card(a, &G, 2);
#if (NOISY_TEST == 1)
        printf("Actual Cards: %i \t Expected Cards: %i \t handPos: %i\n", G.handCount[a], currentHandCount + 3, 2);
#endif
        assertTF(G.handCount[a] == currentHandCount + 3, "Error: Wrong number of cards!");
    }

    printf("\n\nAll tests for numHandCards() passed!\n");
    return 0;
}
