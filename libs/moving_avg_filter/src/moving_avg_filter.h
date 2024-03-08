#ifndef MOVING_AVG_FILTER_H
#define MOVING_AVG_FILTER_H

typedef struct moving_average_struct
{
    float curr_val;
    float filter_stages;

} moving_average_td;

static inline void moving_average_init(moving_average_td *moving_average, int filter_stages)
{
    moving_average->filter_stages = filter_stages;
}

static inline float moving_average_exec(moving_average_td *moving_average, float sample)
{
    moving_average->curr_val -= moving_average->curr_val/moving_average->filter_stages;
    moving_average->curr_val += sample/moving_average->filter_stages;

    return moving_average->curr_val;
}

#endif /* MOVING_AVG_FILTER_H */
