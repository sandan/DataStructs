#ifndef _STACK_ARRAY_H_
#define _STACK_ARRAY_H_

#include <stdint.h>
#include <stdbool.h>

/**TODO: refactor this into its own subproject for data items**/
//8-byte data items
typedef struct {
 uint32_t x;
 uint32_t y;
 uint32_t z;
} item_t;

item_t sentinel = {-1,-1,-1};

//the stack
typedef struct {
 item_t *base;   //pointer to base of stack
 item_t *top;    //pointer to the top to insert
 int size;       //size of stack
} stack;

//Stack API

extern stack* create_stack(uint32_t size);
extern void remove_stack(stack *st);
extern int push(item_t i, stack *st);
extern item_t pop(stack *st);
extern item_t peek(stack *st);
extern bool empty(stack *st);

#endif
