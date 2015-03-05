#ifndef _DATA_H_
#define _DATA_H_

#include <stdint.h>

//8-byte data items
typedef struct {
 uint32_t x;
 uint32_t y;
 uint32_t z;
} item_t;

static item_t sentinel = {-1,-1,-1};

#endif
