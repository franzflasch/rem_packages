#ifndef ANTIRTOS_C_WRAPPER_H
#define ANTIRTOS_C_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

/*** fQ Wrapper ***/

typedef struct fQ_t fQ_t;
typedef void (*fP_t)(void);

fQ_t* fQ_create(int sizeQ);
void fQ_destroy(fQ_t* queue);
int fQ_push(fQ_t* queue, fP_t func);
int fQ_pull(fQ_t* queue);

/*** fQP<int> Wrapper ***/

typedef struct fQP_int_t fQP_int_t;
typedef void (*fP_int_t)(int);

fQP_int_t* fQP_int_create(int sizeQ);
void fQP_int_destroy(fQP_int_t* queue);
int fQP_int_push(fQP_int_t* queue, fP_int_t func, int param);
int fQP_int_pull(fQP_int_t* queue);

/*** del_fQ Wrapper ***/

typedef struct del_fQ_t del_fQ_t;

del_fQ_t* del_fQ_create(int sizeQ);
void del_fQ_destroy(del_fQ_t* queue);
int del_fQ_push_delayed(del_fQ_t* queue, fP_t func, unsigned long delayTime);
int del_fQ_push(del_fQ_t* queue, fP_t func);
void del_fQ_tick(del_fQ_t* queue);
int del_fQ_pull(del_fQ_t* queue);
int del_fQ_revoke(del_fQ_t* queue, fP_t func);

/*** del_fQP<int> Wrapper ***/

typedef struct del_fQP_int_t del_fQP_int_t;

del_fQP_int_t* del_fQP_int_create(int sizeQ);
void del_fQP_int_destroy(del_fQP_int_t* queue);
int del_fQP_int_push(del_fQP_int_t* queue, fP_int_t func, int param);
int del_fQP_int_push_delayed(del_fQP_int_t* queue, fP_int_t func, int param, unsigned long delayTime);
void del_fQP_int_tick(del_fQP_int_t* queue);
int del_fQP_int_revoke(del_fQP_int_t* queue, fP_int_t func);
int del_fQP_int_pull(del_fQP_int_t* queue);

#ifdef __cplusplus
}
#endif

#endif /* ANTIRTOS_C_WRAPPER_H */
