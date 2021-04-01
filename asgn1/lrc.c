#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// static inline u_int8_t left(uint8_t pos, uint8_t players) {
//     return ((pos + players - 1) % players);
// }

// static inline u_int8_t right(uint8_t pos, uint8_t players) {
//     return ((pos + 1) % players);
// }

// Function used to say if a game is finished or not
// Check if there only 1 non-zero number. If true then game is finished
static inline bool finished(uint32_t arr[]) {
    uint32_t non_zeros = 0;
    for (uint32_t i = 0; i < sizeof(arr); i++) {
        if (arr[i] > 0) {
            non_zeros++;
        }
        if (non_zeros > 1) {
            return false;
        }
    }
    return true;
}

int main(void) {
    // typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
    // faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
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
    uint32_t money[num_players];
    for (uint32_t i = 0; i < num_players; i++) {
        money[i] = 3; // Initilize bank account of all players to 3
    }
    while (finished(money) == false) {
        for (int i = 0; i < num_players; i++) {
        }
    }
}
