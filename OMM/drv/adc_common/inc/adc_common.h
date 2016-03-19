#ifndef ADC_COMMON_H_
#define ADC_COMMON_H_

#include <stdint.h>

typedef struct adc_controller_s adc_controller_t;

struct adc_controller_s
{
	uint16_t adc_max_val;
	uint16_t adc_range_return;
	uint8_t nr_channels;
	uint16_t (*ADC_get)(adc_controller_t *adc, uint8_t channel);
	void *platform_drv_info;
};

void ADC_init_controller(adc_controller_t *adc,
						  uint8_t nr_channels,
						  uint16_t adc_max_val,
						  uint16_t adc_range_return,
					 	  void *adc_get,
						  void *platform_drv_info);

uint16_t ADC_get(adc_controller_t *adc, uint8_t channel);

#endif /* ADC_COMMON_H_ */
