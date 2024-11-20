#include <umm_malloc_cfgport.h>

/* Start addresses and the size of the heap */
uint32_t UMM_MALLOC_CFG_HEAP_SIZE = SUPPORT_UMM_MALLOC_HEAP_SIZE;

static char project_umm_heap[SUPPORT_UMM_MALLOC_BLOCKS][UMM_BLOCK_BODY_SIZE];
void *UMM_MALLOC_CFG_HEAP_ADDR = &project_umm_heap;
