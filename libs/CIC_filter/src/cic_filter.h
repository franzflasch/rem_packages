#ifndef CIC_FILTER_H
#define CIC_FILTER_H

/* based on: https://github.com/fotherja/Grid_Tie_Inverter_2/blob/main/Src/main.c#L218 */
#define DEFINE_CIC_FILTER_FUNCTION(cic_name, offset, gain) \
static inline int32_t cic_name(volatile uint8_t *raw_data, int nr_samples) \
{ \
    static int32_t I_1, I_2, I_3, D_1, D_2, D_3; \
    static int32_t previous_input, previous_D_1, previous_D_2; \
    \
    int i = 0; \
    uint8_t x; \
    \
    int32_t measured_val = 0; \
    \
    for(i=0; i<nr_samples; i++) \
    { \
        x = (raw_data[i] >> 7) & 1; I_1 = I_1 + x; I_2 = I_2 + I_1; I_3 = I_3 + I_2; \
        x = (raw_data[i] >> 6) & 1; I_1 = I_1 + x; I_2 = I_2 + I_1; I_3 = I_3 + I_2; \
        x = (raw_data[i] >> 5) & 1; I_1 = I_1 + x; I_2 = I_2 + I_1; I_3 = I_3 + I_2; \
        x = (raw_data[i] >> 4) & 1; I_1 = I_1 + x; I_2 = I_2 + I_1; I_3 = I_3 + I_2; \
        x = (raw_data[i] >> 3) & 1; I_1 = I_1 + x; I_2 = I_2 + I_1; I_3 = I_3 + I_2; \
        x = (raw_data[i] >> 2) & 1; I_1 = I_1 + x; I_2 = I_2 + I_1; I_3 = I_3 + I_2; \
        x = (raw_data[i] >> 1) & 1; I_1 = I_1 + x; I_2 = I_2 + I_1; I_3 = I_3 + I_2; \
        x = (raw_data[i] >> 0) & 1; I_1 = I_1 + x; I_2 = I_2 + I_1; I_3 = I_3 + I_2; \
    } \
    \
    D_1 = I_3 - previous_input; \
    previous_input = I_3; \
    \
    D_2 = D_1 - previous_D_1; \
    previous_D_1 = D_1; \
    \
    D_3 = D_2 - previous_D_2; \
    previous_D_2 = D_2; \
    \
    measured_val = (D_3 / (gain)) - (offset); \
    \
    return measured_val; \
}

#endif /* CIC_FILTER_H */
