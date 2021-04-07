#include "philos.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Code from assignment PDF
static inline u_int8_t left(uint8_t pos, uint8_t players) {
    return ((pos + players - 1) % players);
}

// Code from assignment PDF
static inline u_int8_t right(uint8_t pos, uint8_t players) {
    return ((pos + 1) % players);
}

// Function used to say if a game is finished or not
// If game is not finished program will return -1
// If game is finished return position of winner
// Arr parameter is array the amount of money players have
// size parameter is the size of the array
static inline int8_t finished(uint32_t arr[], uint8_t size) {
    int8_t winner = -1;
    uint8_t non_zeros = 0;
    // Loop through array, if there is more than 1 value that is not 0 return -1
    // If there is a value that is > 0 set winner to the position
    for (uint8_t i = 0; i < size; i++) {
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
    printf("Random seed: ");
    if ((scanf("%u", &seed) < 1 || seed <= 0)) {
        printf("Seed must be a postive number %u\n", seed);

        return 0;
    }
    printf("How many players? ");
    if ((scanf("%u", &num_players) < 1 || num_players < 1 || num_players > 14)) {
        printf("Number of players must be from 1-14\n");
        return 0;
    }

    srandom(seed); // Set seed to the seed the user entered

    // Money is array to say how much money each player has. Size of array is total number of players
    uint32_t money[num_players];
    for (uint32_t i = 0; i < num_players; i++) {
        money[i] = 3; // Initilize bank account of all players to 3
    }

    uint32_t pot = 0;
    // If there is a winner variable will be set to position of winner. Negative value means game is in play
    int8_t winner = -1;
    while (winner == -1) {
        for (uint32_t i = 0; i < num_players && (winner = finished(money, num_players)) == -1;
             i++) {
            if (money[i] > 0) {
                printf("%s rolls... ", philosophers[i]);
                uint8_t total_rolls = (money[i] > 3) ? 3 : money[i];
                for (uint32_t j = 0; j < total_rolls; j++) {
                    faces roll = die[random() % 6];
                    switch (roll) {
                    case LEFT: {
                        u_int8_t left_player = left(i, num_players);
                        money[i] -= 1;
                        money[left_player] += 1;
                        printf("gives $1 to %s", philosophers[left_player]);
                        break;
                    }

                    case RIGHT: {
                        u_int8_t right_player = right(i, num_players);
                        money[i] -= 1;
                        money[right_player] += 1;
                        printf("gives $1 to %s", philosophers[right_player]);
                        break;
                    }

                    case CENTER: {
                        money[i] -= 1;
                        pot += 1;
                        printf("puts $1 in the pot");
                        break;
                    }

                    default: {
                        printf("gets a pass");
                        break;
                    }
                    }

                    if (j != total_rolls - 1) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }
    printf("%s wins the $%d pot ", philosophers[winner], pot);
    printf("with $%d left in the bank!\n", money[winner]);
}
