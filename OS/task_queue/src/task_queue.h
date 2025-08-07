#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <stdio.h>

typedef enum
{
    TASK_QUEUE_OK = 0,
    TASK_QUEUE_ERR
} task_queue_ret;

typedef void (*task_event_cb)(void *priv);

typedef struct task_event_struct
{
    task_event_cb task_event;
    int exec_pending;
    void *priv;
} task_event_td;

typedef struct task_queue_struct
{
    task_event_td *task_events;
    size_t elements;
    size_t read_loc;
    size_t write_loc;
    size_t nr_pending;

} task_queue_td;

/*
 * This task queue is designed for single-producer, single-consumer usage.
 * All functions are non-blocking and assume either thread or interrupt context.
 * The caller is responsible for implementing task_queue_enter_critical_section()
 * and task_queue_exit_critical_section().
 *
 * The caller is responsible for providing valid, non-NULL pointers to all functions,
 * except task_queue_init(), which checks its arguments.
 */

task_queue_ret task_queue_init(task_queue_td *task_queue, int elements);
void task_queue_deinit(task_queue_td *task_queue);
task_queue_ret task_queue_push(task_queue_td *task_queue, task_event_cb event_cb, void *priv);
void task_queue_pull(task_queue_td *task_queue);
int task_queue_get_pending(task_queue_td *task_queue);
int task_queue_get_free(task_queue_td *task_queue);
void task_queue_print(task_queue_td *task_queue);

#endif /* TASK_QUEUE_H */
