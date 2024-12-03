#include <stdio.h>
#include <stdlib.h>

#include <task_queue.h>

void task_queue_init(task_queue_td *task_queue, int elements)
{
    task_queue->task_events = calloc(elements, sizeof(task_event_td));

    if(!task_queue->task_events)
        return;

    task_queue->elements = elements;
    task_queue->read_loc = 0;
    task_queue->write_loc = 0;
}

void task_queue_push(task_queue_td *task_queue, task_event_cb event_cb, void *private)
{
    if (!event_cb)
        return;

    int write_loc = task_queue->write_loc;

    if (write_loc == task_queue->read_loc && task_queue->task_events[write_loc].exec_pending)
    {
        printf("task queue is full!\n");
        return;
    }

    task_queue->task_events[write_loc].task_event = event_cb;
    task_queue->task_events[write_loc].private = private;
    task_queue->task_events[write_loc].exec_pending = 1;

    task_queue->write_loc = (task_queue->write_loc + 1) % task_queue->elements;
}

void task_queue_pull(task_queue_td *task_queue)
{
    int read_loc = task_queue->read_loc;

    if(!task_queue->task_events[read_loc].exec_pending)
        return;

    task_queue->task_events[read_loc].task_event(task_queue->task_events[read_loc].private);
    task_queue->task_events[read_loc].exec_pending = 0;

    task_queue->read_loc = (task_queue->read_loc + 1) % task_queue->elements;
}
