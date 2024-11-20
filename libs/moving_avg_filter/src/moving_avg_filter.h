#ifndef MOVING_AVG_FILTER_H
#define MOVING_AVG_FILTER_H

/************** integer (macro) version, creates a new function for each filter **********/
#define MVG_AVG_OK 0
#define MVG_AVG_WAIT 1

#define CREATE_MOVING_AVG_FUNCTION(FUNC_NAME, STAGES, MUL, SHIFT) \
static inline int FUNC_NAME(int sample, int *filtered_value) \
{   \
    static int filter_arr[STAGES] = {0}; \
    static int pos = 0; \
    static int curr_val = 0; \
    static int init_done = 0; \
    \
    if (!filtered_value) { \
        for (int i = 0; i < STAGES; i++) \
            filter_arr[i] = 0; \
        pos = 0; \
        curr_val = 0; \
        init_done = 0; \
        return MVG_AVG_WAIT; \
    } \
    curr_val = curr_val - filter_arr[pos] + sample; \
    filter_arr[pos] = sample; \
    \
    pos++; \
    \
    if(pos >= STAGES) \
    { \
        init_done = 1; \
        pos = 0; \
    } \
    \
    if (SHIFT) \
        *filtered_value = ((curr_val * MUL) >> SHIFT); \
    else \
        *filtered_value = (curr_val / STAGES); \
    \
    if(!init_done) \
        return MVG_AVG_WAIT; \
    \
    return MVG_AVG_OK; \
}

/* Example:
 * CREATE_MOVING_AVG_FUNCTION(moving_avg_10, 10)
 */


/************* float version without array *********************/
typedef struct moving_average_struct
{
    float curr_val;
    int filter_stages;

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
