#include <stdio.h>

#include "../headers/heap.h"

heap_s *heap;

void* alloc(uint32_t size) {
    void* p = heap_malloc(heap,size);
    printf("allocate %d ",size);
    if (p == 0) {
        printf("failed\n");
    } else {
        printf("@%d\n",heap_relptr(heap,p));
        for (uint32_t i =0; i<size; i++) {
            ((char*) p)[i] = 0xff;
        }
    }
    heap_stats(heap);
    return p;
}

void dealloc(void* p) {
    printf("deallocate @%d\n",heap_relptr(heap,p));
    heap_free(heap,p);
    heap_stats(heap);
}

void freeAll() {
    printf("freeAll\n");
    heap_freeAll(heap);
    heap_stats(heap);
}

//change to main to run ./main on compilation

int run() {

    void* p;
    void* q;
    void* r;

    heap = heap_new(100);
    heap_stats(heap);
    alloc(1000000);
    alloc(100);
    alloc(85);
    alloc(84);
    alloc(73);
    p = alloc(72);
    alloc(1);
    dealloc(p);
    p = alloc(1);
    alloc(57);
    q = alloc(56);
    dealloc(p);
    alloc(5);
    p = alloc(4);
    dealloc(p);
    alloc(72);
    dealloc(q);
    p = alloc(72);
    dealloc(p);
    p = alloc(30);
    alloc(30);
    q = alloc(28);
    dealloc(q);
    dealloc(p);
    p = alloc(72);
    dealloc(p);
 

    p = alloc(4);
    q = alloc(8);
    r = alloc(36);

    dealloc(p);
    dealloc(r);
    dealloc(q);

    p = alloc(72);
    dealloc(p);
   
    alloc(10);
    alloc(20);
    alloc(8);
    

    alloc(72);

    freeAll();
    
    alloc(71);

    freeAll();

    for (int i=0; i<7; i++) {
        alloc(0);
    }

    return 0;
}
