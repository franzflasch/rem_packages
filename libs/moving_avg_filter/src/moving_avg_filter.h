#ifndef MOVING_AVG_FILTER_H
#define MOVING_AVG_FILTER_H

/************** integer (macro) version, creates a new function for each filter **********/
#define CREATE_MOVING_AVG_FUNCTION(FUNC_NAME, STAGES) \
static inline int FUNC_NAME(int sample) { \
    static int filter_stages = STAGES; \
    static int filter_arr[STAGES] = {0}; \
    static int pos = 0; \
    static int curr_val = 0; \
    \
    curr_val = curr_val - filter_arr[pos] + sample; \
    filter_arr[pos] = sample; \
    \
    pos++; \
    \
    if(pos >= filter_stages) \
        pos = 0; \
    \
    return curr_val / filter_stages; \
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
