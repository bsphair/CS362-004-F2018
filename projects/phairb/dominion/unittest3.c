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




//Description: Test the affect if trying to change the number of initial coins
void testCoinCount(struct gameState G, int numPlayers, int numberOfTests){
    int a, b;

    for(a = 1; a <= numPlayers; a++) {      //loop over all players
#if (NOISY_TEST == 1)
        printf("\t\tPlayer %i\n", a);
#endif

        for (b = 0; b < numberOfTests; b++){        //loop for number of tests
#if (NOISY_TEST == 1)
            printf("Original Coin = %i", 0);
#endif
            G.coins = b;                //change coin amount
            updateCoins(a, &G, 0);      //update the game state
#if (NOISY_TEST == 1)
            printf("\tAdded Coins = %i\tFinal Coins = %i\n", 100, G.coins);
#endif
        }
    }
}


//Description: Tests the affect of the input card on the value of the coins
void testCard(struct gameState G, int numPlayers, int numberOfTests, int coinType[], int handCount, int cardMultiplier){
    int a, b;

    for(a = 1; a <= numPlayers; a++){       //loop over all players
#if (NOISY_TEST == 1)
        printf("\n\t\tPlayer %i\n", a);
#endif
        for(b = 1; b <= numberOfTests; b++){    //loop for number of tests
            G.handCount[a] = b;                 //update hand count
            memcpy(G.hand[a], coinType, sizeof(int) * handCount);   //update the hand
            updateCoins(a, &G, 0);
            assertTrue(G.coins == b * cardMultiplier, "Number of coins is wrong\n");
#if (NOISY_TEST == 1)
            printf("Coins: %i \t Expected: %i\n", G.coins, b * cardMultiplier);
#endif
        }
    }
}

//Description: Test the affect of the input bonus value on the value of the coins
void testBonus(struct gameState G, int numPlayers, int numberOfTests, int bonus){
    int a, b;

    for(a = 1; a <= numPlayers; a++) {      //loop over all players
#if (NOISY_TEST == 1)
        printf("\n\t\tPlayer %i\n", a);
#endif
        for (b = 1; b <= numberOfTests; b++) {      //loop for number of tests
            updateCoins(a, &G, bonus);
#if (NOISY_TEST == 1)
            printf("Bonus: %i \t Expected: %i\n", G.coins, bonus);
#endif
        }
    }

}





int main() {
    int a, i, cardMultiplier;
    int seed = 1000;
    int numPlayers = 2;
    int handCount = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int noCards[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
        noCards[i] = 0;
    }


    initializeGame(numPlayers, k ,seed, &G);

    printf("\n*** Testing updateCoins() ***\n\n");


#if (NOISY_TEST == 1)
    printf("*** Testing if coins are reset to zero within the function. A number of coins will be added to the coin amount and then it will be deterimined if that number is reset or not. ***\n");
#endif
    testCoinCount(G, numPlayers, 5);    //5 represents the number of tests the function will run

#if (NOISY_TEST == 1)
    printf("\n*** Test Copper Card ***\n");
#endif
    cardMultiplier = 1;
    testCard(G, numPlayers, 5, coppers, handCount, cardMultiplier);

#if (NOISY_TEST == 1)
    printf("\n*** Test Silver Card ***\n");
#endif
    cardMultiplier = 2;
    testCard(G, numPlayers, 5, silvers, handCount, cardMultiplier);

#if (NOISY_TEST == 1)
    printf("\n*** Test Gold Card ***\n");
#endif
    cardMultiplier = 3;
    testCard(G, numPlayers, 5, golds, handCount, cardMultiplier);

#if (NOISY_TEST == 1)
    printf("\n*** Test No Card ***\n");
#endif
    cardMultiplier = 0;
    testCard(G, numPlayers, 5, noCards, handCount, cardMultiplier);

#if (NOISY_TEST == 1)
    printf("\n*** Test Addition of Bonus ***\n");
#endif
    for(a = 0; a < 5; a++) {
#if (NOISY_TEST == 1)
        printf("\n** Testing Bonus = %i **", a);
#endif
        testBonus(G, numPlayers, 1, a);
    }



    printf("\nAll Tests Passed!!\n");

    return 0;
}