#ifndef _STACK_ARRAY_H_
#define _STACK_ARRAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "../data/data.h"

/**TODO: refactor this into its own subproject for data items**/
//the stack
typedef struct {
 item_t *base;   //pointer to base of stack
 item_t *top;    //pointer to the top to insert
 int size;       //size of stack
} stack;

//Stack API

stack* create_stack(uint32_t size);
void remove_stack(stack *st);
int push(item_t i, stack *st);
item_t pop(stack *st);
item_t peek(stack *st);
bool empty(stack *st);

#endif
