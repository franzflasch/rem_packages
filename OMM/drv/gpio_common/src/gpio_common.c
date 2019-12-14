/*
 * gpio_common.c
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
#include <stdio.h>
#include <gpio_common.h>

void GPIO_init_controller(gpio_controller_t *controller,
						  gpio_mode_e mode,
						  uint8_t nrpins,
					 	  void *gpio_set,
					 	  void *gpio_get,
						  void *platform_drv_info)
{
	controller->mode = mode;
	controller->nrpins = nrpins;
	controller->GPIO_set = ( void (*)(gpio_controller_t *gpio, uint8_t pin, uint8_t val) ) gpio_set;
	controller->GPIO_get = ( uint8_t (*)(gpio_controller_t *gpio, uint8_t pin) ) gpio_get;
	controller->platform_drv_info = platform_drv_info;
}
