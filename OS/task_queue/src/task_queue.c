#include <stdlib.h>

#include <task_queue.h>

__attribute__((weak)) void task_queue_enter_critical_section(void)
{
    return;
}

__attribute__((weak)) void task_queue_exit_critical_section(void)
{
    return;
}

__attribute__((weak)) void task_queue_printf(const char *fmt, ...)
{
    (void)fmt;
}

task_queue_ret task_queue_init(task_queue_td *task_queue, int elements)
{
    if (!task_queue || elements <= 0)
        return TASK_QUEUE_ERR;

    task_queue->task_events = calloc(elements, sizeof(task_event_td));
    if (!task_queue->task_events) {
        task_queue_printf("could not alloc task_events\n\r");
        return TASK_QUEUE_ERR;
    }

    task_queue->elements = elements;
    task_queue->read_loc = 0;
    task_queue->write_loc = 0;
    task_queue->nr_pending = 0;

    return TASK_QUEUE_OK;
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

task_queue_ret task_queue_push(task_queue_td *task_queue, task_event_cb event_cb, void *priv)
{
    if (!event_cb)
        return TASK_QUEUE_ERR;

    size_t write_loc = task_queue->write_loc;

    task_queue_enter_critical_section();
    if ((write_loc == task_queue->read_loc) && task_queue->task_events[write_loc].exec_pending)
    {
        // task_queue_printf("task queue is full!\n\r");
        task_queue_exit_critical_section();
        return TASK_QUEUE_ERR;
    }

    task_queue->task_events[write_loc].task_event = event_cb;
    task_queue->task_events[write_loc].priv = priv;

    task_queue->task_events[write_loc].exec_pending = 1;
    task_queue->nr_pending++;
    task_queue->write_loc = (task_queue->write_loc + 1) % task_queue->elements;

    task_queue_exit_critical_section();

    return TASK_QUEUE_OK;
}

void task_queue_pull(task_queue_td *task_queue)
{
    size_t read_loc = task_queue->read_loc;

    task_queue_enter_critical_section();
    if(!task_queue->task_events[read_loc].exec_pending)
    {
        task_queue_exit_critical_section();
        return;
    }
    task_queue_exit_critical_section();

    task_queue->task_events[read_loc].task_event(task_queue->task_events[read_loc].priv);

    task_queue_enter_critical_section();
    task_queue->task_events[read_loc].exec_pending = 0;
    task_queue->nr_pending = (task_queue->nr_pending > 0) ? task_queue->nr_pending - 1 : 0;
    task_queue->read_loc = (task_queue->read_loc + 1) % task_queue->elements;
    task_queue_exit_critical_section();
}

int task_queue_get_pending(task_queue_td *task_queue)
{
    task_queue_enter_critical_section();
    size_t pending = task_queue->nr_pending;
    task_queue_exit_critical_section();
    return pending;
}

int task_queue_get_free(task_queue_td *task_queue)
{
    task_queue_enter_critical_section();
    size_t free = task_queue->elements-task_queue->nr_pending;
    task_queue_exit_critical_section();
    return free;
}


void task_queue_print(task_queue_td *task_queue)
{
    int i = 0;

    task_queue_printf("--- Task Queue Details ---\n\r");
    task_queue_printf("Total elements in queue: %d\n\r", task_queue->elements);
    task_queue_printf("Read location: %d\n\r", task_queue->read_loc);
    task_queue_printf("Write location: %d\n\r", task_queue->write_loc);
    task_queue_printf("--------------------------\n\r");

    for(i = 0; i < task_queue->elements; i++)
    {
        task_queue_printf("Element %d:\n\r", i);
        // Assuming task_event is a function pointer, we can't directly print its value in a meaningful way
        // other than its memory address, if desired. For now, we'll skip printing the function itself.
        task_queue_printf("  exec_pending: %d\n\r", task_queue->task_events[i].exec_pending);
        task_queue_printf("  priv (address): %p\n\r", task_queue->task_events[i].priv); // Print the address of priv
        task_queue_printf("\n\r");
    }
    task_queue_printf("--- End of Task Queue Details ---\n\r");
}
