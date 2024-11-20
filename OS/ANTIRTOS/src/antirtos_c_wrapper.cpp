#include <antirtos.h>
#include <antirtos_c_wrapper.h>

/*** fQ Wrapper Implementation ***/

struct fQ_t {
    fQ* cpp_queue;
};

extern "C" {

fQ_t* fQ_create(int sizeQ) {
    fQ_t* queue = new fQ_t;
    queue->cpp_queue = new fQ(sizeQ);
    return queue;
}

void fQ_destroy(fQ_t* queue) {
    delete queue->cpp_queue;
    delete queue;
}

int fQ_push(fQ_t* queue, fP_t func) {
    return queue->cpp_queue->push(func);
}

int fQ_pull(fQ_t* queue) {
    return queue->cpp_queue->pull();
}

/*** fQP<int> Wrapper Implementation ***/

}

struct fQP_int_t {
    fQP<int>* cpp_queue;
};

extern "C" {

fQP_int_t* fQP_int_create(int sizeQ) {
    fQP_int_t* queue = new fQP_int_t;
    queue->cpp_queue = new fQP<int>(sizeQ);
    return queue;
}

void fQP_int_destroy(fQP_int_t* queue) {
    delete queue->cpp_queue;
    delete queue;
}

int fQP_int_push(fQP_int_t* queue, fP_int_t func, int param) {
    return queue->cpp_queue->push(func, param);
}

int fQP_int_pull(fQP_int_t* queue) {
    return queue->cpp_queue->pull();
}

/*** del_fQ Wrapper Implementation ***/

}

struct del_fQ_t {
    del_fQ* cpp_queue;
};

extern "C" {

del_fQ_t* del_fQ_create(int sizeQ) {
    del_fQ_t* queue = new del_fQ_t;
    queue->cpp_queue = new del_fQ(sizeQ);
    return queue;
}

void del_fQ_destroy(del_fQ_t* queue) {
    delete queue->cpp_queue;
    delete queue;
}

int del_fQ_push_delayed(del_fQ_t* queue, fP_t func, unsigned long delayTime) {
    return queue->cpp_queue->push_delayed(func, delayTime);
}

int del_fQ_push(del_fQ_t* queue, fP_t func) {
    return queue->cpp_queue->push(func);
}

void del_fQ_tick(del_fQ_t* queue) {
    queue->cpp_queue->tick();
}

int del_fQ_pull(del_fQ_t* queue) {
    return queue->cpp_queue->pull();
}

int del_fQ_revoke(del_fQ_t* queue, fP_t func) {
    return queue->cpp_queue->revoke(func);
}

/*** del_fQP<int> Wrapper Implementation ***/

}

struct del_fQP_int_t {
    del_fQP<int>* cpp_queue;
};

extern "C" {

del_fQP_int_t* del_fQP_int_create(int sizeQ) {
    del_fQP_int_t* queue = new del_fQP_int_t;
    queue->cpp_queue = new del_fQP<int>(sizeQ);
    return queue;
}

void del_fQP_int_destroy(del_fQP_int_t* queue) {
    delete queue->cpp_queue;
    delete queue;
}

int del_fQP_int_push(del_fQP_int_t* queue, fP_int_t func, int param) {
    return queue->cpp_queue->push(func, param);
}

int del_fQP_int_push_delayed(del_fQP_int_t* queue, fP_int_t func, int param, unsigned long delayTime) {
    return queue->cpp_queue->push_delayed(func, param, delayTime);
}

void del_fQP_int_tick(del_fQP_int_t* queue) {
    queue->cpp_queue->tick();
}

int del_fQP_int_revoke(del_fQP_int_t* queue, fP_int_t func) {
    return queue->cpp_queue->revoke(func);
}

int del_fQP_int_pull(del_fQP_int_t* queue) {
    return queue->cpp_queue->pull();
}

}
