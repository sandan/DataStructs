#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdint.h>
#include <sys/mman.h>
struct heap_struct{
 uint32_t required;
 uint32_t consumed;
 uint32_t size;
 uint32_t* block_ptr;
};

typedef struct heap_struct heap_s;

heap_s* heap_new(uint32_t size);
void heap_stats(heap_s *heap);
uint32_t heap_relptr(heap_s *heap, void* ptr);
void* heap_malloc(heap_s *heap, uint32_t size);
void heap_free(heap_s *heap, void* ptr);
void heap_freeAll(heap_s *heap);

#endif
