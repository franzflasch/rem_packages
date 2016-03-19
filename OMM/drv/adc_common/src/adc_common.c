#include <adc_common.h>

void ADC_init_controller(adc_controller_t *adc,
						  uint8_t nr_channels,
						  uint16_t adc_max_val,
						  uint16_t adc_range_return,
					 	  void *adc_get,
						  void *platform_drv_info)
{
	adc->adc_max_val = adc_max_val;
	adc->adc_range_return = adc_range_return;
	adc->nr_channels = nr_channels;
	adc->ADC_get = adc_get;
	adc->platform_drv_info = platform_drv_info;
}

uint16_t ADC_get(adc_controller_t *adc, uint8_t channel)
{
	float calc_factor = 0;

	calc_factor = (float)adc->adc_range_return/(float)adc->adc_max_val;

	return (adc->ADC_get(adc, channel)*calc_factor);
}

