#include "philos.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static inline u_int8_t left(uint8_t pos, uint8_t players) {
    return ((pos + players - 1) % players);
}

static inline u_int8_t right(uint8_t pos, uint8_t players) {
    return ((pos + 1) % players);
}

// Function used to say if a game is finished or not
// If game is not finished return -1
// If game is finished return position of winner
static inline int8_t finished(uint32_t arr[], uint8_t size) {
    uint8_t winner = -1;
    uint8_t non_zeros = 0;
    for (uint32_t i = 0; i < size; i++) {
        if (arr[i] > 0) {
            non_zeros++;
            winner = i;
        }
        if (non_zeros > 1) {
            return -1;
        }
    }
    return winner;
}

int main(void) {
    typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
    faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
    uint32_t num_players, seed;
    printf("Random Seed: ");
    if ((scanf("%u", &seed) < 1 || seed <= 0)) {
        printf("Seed must be a postive number\n");
        return 0;
    }
    printf("How many players? ");
    if ((scanf("%u", &num_players) < 1 || num_players < 1 || num_players > 14)) {
        printf("Number of players must be from 1-14\n");
        return 0;
    }

    srandom(seed); // Set seed to the seed the user entered
    uint32_t money[num_players];
    for (uint32_t i = 0; i < num_players; i++) {
        money[i] = 3; // Initilize bank account of all players to 3
    }
    uint32_t pot = 0;
    // If there is a winner variable will be set to position of winner. Negative means game is in play
    int8_t winner = finished(money, num_players);
    while (winner < 0) {
        for (uint32_t i = 0; i < num_players; i++) {
            if (money[i] > 0) {
                printf("%s rolls... ", philosophers[i]);
                printf("Money in account %d ", money[i]);
                for (uint32_t j = 0; j <= money[i]; j++) {
                    faces roll = die[random() % 5];
                    switch (roll) {
                    case LEFT: {
                        u_int8_t left_player = left(i, num_players);
                        money[i] -= 1;
                        money[left_player] += 1;
                        printf("gives $1 to %s ", philosophers[left_player]);
                        break;
                    }

                    case RIGHT: {
                        u_int8_t right_player = right(i, num_players);
                        money[i] -= 1;
                        money[right_player] += 1;
                        printf("gives $1 to %s ", philosophers[right_player]);
                        break;
                    }

                    case CENTER: {
                        money[i] -= 1;
                        pot += 1;
                        printf("puts $1 in the pot ");
                        break;
                    }
                    default: printf("gets a pass "); break;
                    }
                }
                printf("\n");
                winner = finished(money, num_players);
            }
        }
    }
    printf("%s wins the $%d pot ", philosophers[winner], pot);
    printf("with $%d left in the bank!\n", money[winner]);
}
