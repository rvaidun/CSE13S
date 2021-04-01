#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// static inline u_int8_t left(uint8_t pos, uint8_t players) {
//     return ((pos + players - 1) % players);
// }

// static inline u_int8_t right(uint8_t pos, uint8_t players) {
//     return ((pos + 1) % players);
// }

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
}
