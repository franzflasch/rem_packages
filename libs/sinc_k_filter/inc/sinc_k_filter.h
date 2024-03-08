#ifndef SINC_K_FILTER_H
#define SINC_K_FILTER_H

#include <stdint.h>

/* resources
    Combining the ADS1202 with an FPGA Digital Filter for Current Measurement in Motor Control Applications (chapter 4 Sinc^K filter)
    https://github.com/fotherja/Grid_Tie_Inverter_2/blob/main/Src/main.c#L218
 */

/* WARNING: be careful to set this higher than 3, as the overflow 
 * arithmetic might not work anymore with 32 bit integers
 */
#define SINC_K_CASCADE_MAX 3

typedef struct sinc_k_filter_struct
{
    int sinc_k_cascade;
    int32_t integrator[SINC_K_CASCADE_MAX];
    int32_t differentiator[SINC_K_CASCADE_MAX];
    int32_t prev_differentiator_input[SINC_K_CASCADE_MAX];

} sinc_k_filter_td;


void sinc_k_filter_init(sinc_k_filter_td *sinc_k_filter, int k);
void sinc_k_filter_process_integrators(sinc_k_filter_td *sinc_k_filter, int32_t input);
void sinc_k_filter_process_differentiators(sinc_k_filter_td *sinc_k_filter);


#endif /* SINC_K_FILTER_H */
