#include <stdio.h>
#include <stdlib.h>

#include <task_queue.h>

void task_queue_init(task_queue_td *task_queue, int elements)
{
    task_queue->task_events = calloc(elements, sizeof(task_event_td));

    if(!task_queue->task_events)
    {
        printf("could not alloc task_events\n");
        return;
    }

    task_queue->elements = elements;
    task_queue->read_loc = 0;
    task_queue->write_loc = 0;
}

void task_queue_deinit(task_queue_td *task_queue)
{
    if (task_queue && task_queue->task_events) {
        free(task_queue->task_events);
        task_queue->task_events = NULL;
        task_queue->elements = 0;
        task_queue->write_loc = 0;
        task_queue->read_loc = 0;
    }
}

void task_queue_push(task_queue_td *task_queue, task_event_cb event_cb, void *priv)
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
    task_queue->task_events[write_loc].priv = priv;
    task_queue->task_events[write_loc].exec_pending = 1;

    task_queue->write_loc = (task_queue->write_loc + 1) % task_queue->elements;
}

void task_queue_pull(task_queue_td *task_queue)
{
    int read_loc = task_queue->read_loc;

    if(!task_queue->task_events[read_loc].exec_pending)
        return;

    task_queue->task_events[read_loc].task_event(task_queue->task_events[read_loc].priv);
    task_queue->task_events[read_loc].exec_pending = 0;

    task_queue->read_loc = (task_queue->read_loc + 1) % task_queue->elements;
}

void task_queue_print(task_queue_td *task_queue)
{
    int i = 0;

    printf("--- Task Queue Details ---\n");
    printf("Total elements in queue: %d\n", task_queue->elements);
    printf("Read location: %d\n", task_queue->read_loc);
    printf("Write location: %d\n", task_queue->write_loc);
    printf("--------------------------\n");

    for(i = 0; i < task_queue->elements; i++)
    {
        printf("Element %d:\n", i);
        // Assuming task_event is a function pointer, we can't directly print its value in a meaningful way
        // other than its memory address, if desired. For now, we'll skip printing the function itself.
        printf("  exec_pending: %d\n", task_queue->task_events[i].exec_pending);
        printf("  priv (address): %p\n", task_queue->task_events[i].priv); // Print the address of priv
        printf("\n");
    }
    printf("--- End of Task Queue Details ---\n");
}
