#include <sinc_k_filter.h>

#include <string.h>

void sinc_k_filter_init(sinc_k_filter_td *sinc_k_filter, int k)
{
    memset(sinc_k_filter, 0, sizeof(sinc_k_filter_td));
    sinc_k_filter->sinc_k_cascade = k;
}

void sinc_k_filter_process_integrators(sinc_k_filter_td *sinc_k_filter, int32_t input)
{
    int i = 0;

    /* the integrators must inherently overflow at some point, but it seems that this is
     * made by design for CIC (Cascaded Integrator-Comb) filters:
     * https://www.dsprelated.com/showarticle/1337.php
     *
     * CIC filters suffer from accumulator (adder) arithmetic register overflow because of the unity feedback at each integrator stage.
     * This overflow is of no consequence as long as the following two conditions are met:
        * each stage is implemented with two’s complement (non-saturating) arithmetic [1,3], and
        * the range of a stage's number system is greater than or equal to the maximum value expected at the stage's output.
        *
     * as far as I understand this: even tough a overflow might occur here, it is not a problem as long as the diff
     * between the current and previous value would still be the same. If the diff is (would be) greater than the integer max value the
     * filter would not work anymore.
     */
    sinc_k_filter->integrator[0] += input;

    for(i=1;i<sinc_k_filter->sinc_k_cascade;i++)
    {
        sinc_k_filter->integrator[i] += sinc_k_filter->integrator[i-1];
    }
}

void sinc_k_filter_process_differentiators(sinc_k_filter_td *sinc_k_filter)
{
    int i = 0;

    sinc_k_filter->differentiator[0] = sinc_k_filter->integrator[sinc_k_filter->sinc_k_cascade-1] - sinc_k_filter->prev_differentiator_input[0];
    sinc_k_filter->prev_differentiator_input[0] = sinc_k_filter->integrator[sinc_k_filter->sinc_k_cascade-1];

    for(i=1;i<sinc_k_filter->sinc_k_cascade;i++)
    {
        sinc_k_filter->differentiator[i] = sinc_k_filter->differentiator[i-1] - sinc_k_filter->prev_differentiator_input[i];
        sinc_k_filter->prev_differentiator_input[i] = sinc_k_filter->differentiator[i-1];
    }
}
