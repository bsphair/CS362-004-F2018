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
    int newDeckCount;
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













    return 0;
}