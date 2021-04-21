#ifndef __SET_H__
#define __SET_H__

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t Set;

#define SET_CAPACITY 32 // 32 bits means 32 items max.

Set set_empty(void);

bool set_member(Set s, int x);

Set set_insert(Set s, int x);

Set set_remove(Set s, int x);

Set set_union(Set s, Set t);

Set set_intersect(Set s, Set t);

Set set_difference(Set s, Set t);

Set set_complement(Set s);

#endif
