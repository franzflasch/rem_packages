/*
 * OMM_common_stm32f1.c
 *
 *  Created on: Feb 27, 2015
 *      Author: fflasch
 */

#include <stdint.h>
#include <stdlib.h>

void OMM_busy_delay(uint32_t val)
{
	uint32_t j = 0;
	for(j=0;j<(val*1000);j++)
			__asm__("nop");
}
