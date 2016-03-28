/*
 * pwm_common.h
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#ifndef PWM_COMMON_H_
#define PWM_COMMON_H_


/*
 * spi_common.h
 *
 *  Created on: Feb 14, 2015
 *      Author: franz
 */

#include <stdint.h>

typedef struct pwm_controller_s pwm_controller_t;

struct pwm_controller_s
{
	uint8_t nr_channels;
	uint32_t pwm_period_max;
	void (*PWM_set)(pwm_controller_t *pwm, uint8_t channel, uint32_t val);
	void *platform_drv_info;
};

void PWM_init_controller(pwm_controller_t *controller,
						 uint8_t nr_channels,
						 uint32_t pwm_period_max,
					 	 void *pwm_set,
						 void *platform_drv_info);

void PWM_set(pwm_controller_t *pwm, uint8_t channel, uint32_t val);
uint32_t PWM_get_period_max(pwm_controller_t *pwm);

#endif /* PWM_COMMON_H_ */
