// Code posted by Eugene on Piazza.
// Implemetation of set
#include "set.h"

Set set_empty(void) {
    return 0x00000000; // Empty set is 0s for each bit.
}

bool set_member(Set s, int x) {
    return s & (1 << (x % SET_CAPACITY));
}

Set set_insert(Set s, int x) {
    return s | (1 << (x % SET_CAPACITY));
}

Set set_remove(Set s, int x) {
    return s & ~(1 << (x % SET_CAPACITY));
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}

Set set_complement(Set s) {
    return ~s;
}
