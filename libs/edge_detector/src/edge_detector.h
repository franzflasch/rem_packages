#ifndef EDGE_DETECTOR_H
#define EDGE_DETECTOR_H

#define EDGE_DETECTOR_IDLE 0
#define EDGE_DETECTOR_FALLING_EDGE 1
#define EDGE_DETECTOR_RISING_EDGE 2

#define CREATE_EDGE_DETECTOR_FUNCTION(FUNC_NAME, LOW_THRESHOLD, HIGH_THRESHOLD) \
static inline int FUNC_NAME(int sample) \
{ \
    static int old_state = 0; \
    \
    if(sample <= LOW_THRESHOLD) \
    { \
        if(old_state == 1) \
        { \
            old_state = 0; \
            return EDGE_DETECTOR_FALLING_EDGE; \
        } \
    } \
    else if(sample >= HIGH_THRESHOLD) \
    { \
        if(old_state == 0) \
        { \
            old_state = 1; \
            return EDGE_DETECTOR_RISING_EDGE; \
        } \
    } \
    \
    return EDGE_DETECTOR_IDLE; \
}

#endif /* EDGE_DETECTOR_H */
