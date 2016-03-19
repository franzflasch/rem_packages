/*
 * pwm_common.c
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

/*
 * spi_common.c
 *
 *  Created on: Feb 14, 2015
 *      Author: franz
 */

#include <pwm_common.h>

void PWM_init_controller(pwm_controller_t *controller,
						 uint8_t nr_channels,
						 uint32_t pwm_period_max,
					 	 void *pwm_set,
						 void *platform_drv_info)
{
	controller->nr_channels = nr_channels;
	controller->pwm_period_max = pwm_period_max;
	controller->PWM_set = pwm_set;
	controller->platform_drv_info = platform_drv_info;
}

void PWM_set(pwm_controller_t *pwm, uint8_t channel, uint32_t val)
{
	return pwm->PWM_set(pwm, channel, val);
}

