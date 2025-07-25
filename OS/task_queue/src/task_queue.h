#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

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
    int elements;
    int read_loc;
    int write_loc;

} task_queue_td;

void task_queue_init(task_queue_td *task_queue, int elements);
void task_queue_deinit(task_queue_td *task_queue);
void task_queue_push(task_queue_td *task_queue, task_event_cb event_cb, void *priv);
void task_queue_pull(task_queue_td *task_queue);
void task_queue_print(task_queue_td *task_queue);

#endif /* TASK_QUEUE_H */
