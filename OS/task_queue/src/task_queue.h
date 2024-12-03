#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

typedef void (*task_event_cb)(void *private);

typedef struct task_event_struct
{
    task_event_cb task_event;
    int exec_pending;
    void *private;

} task_event_td;

typedef struct task_queue_struct
{
    task_event_td *task_events;
    int elements;
    int read_loc;
    int write_loc;

} task_queue_td;

void task_queue_init(task_queue_td *task_queue, int elements);
void task_queue_push(task_queue_td *task_queue, task_event_cb event_cb, void *private);
void task_queue_pull(task_queue_td *task_queue);

#endif /* TASK_QUEUE_H */
