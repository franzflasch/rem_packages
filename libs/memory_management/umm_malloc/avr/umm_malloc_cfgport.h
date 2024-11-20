/*
 * Project specific configuration for umm_malloc
 *
 * This file is intentionally left blank
 */

#include <umm_malloc.h>
#include <umm_malloc_cfg.h>

#define UMM_INFO
// #define UMM_MAX_CRITICAL_DEPTH_CHECK

#include <stddef.h>

#define SUPPORT_UMM_MALLOC_BLOCKS (32)
#define SUPPORT_UMM_MALLOC_HEAP_SIZE ((uint32_t)SUPPORT_UMM_MALLOC_BLOCKS * UMM_BLOCK_BODY_SIZE)
#define UMM_LASTBLOCK ((SUPPORT_UMM_MALLOC_HEAP_SIZE / UMM_BLOCK_BODY_SIZE) - 1)
