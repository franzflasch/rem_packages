#include <umm_malloc_cfgport.h>

void* operator new(size_t size) {
    return umm_malloc(size);
}

void* operator new[](size_t size) {
    return umm_malloc(size);
}

void operator delete(void* ptr) noexcept {
    umm_free(ptr);
}

void operator delete[](void* ptr) noexcept {
    umm_free(ptr);
}

void operator delete(void* ptr, size_t /*size*/) noexcept {
    umm_free(ptr);
}

void operator delete[](void* ptr, size_t /*size*/) noexcept {
    umm_free(ptr);
}
