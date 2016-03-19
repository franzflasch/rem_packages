/*
 * OMM_mach_avr_mini_wi.c
 *
 *  Created on: Feb 24, 2015
 *      Author: fflasch
 */

#include <avr/io.h>
#include <util/delay.h>
#include <OMM_machine_common.h>

#include <stdio.h>

#include <uart_avr.h>

OMM_machine_t __attribute__((weak)) *machine_setup(void)
{
	static OMM_machine_t machine =
	{
			.name = "atmega168_test"
	};

	static OMM_platform_devices pdevs[] =
	{
			{NULL, NULL}
	};

	uart_init();

	machine.pdev_list = &pdevs[0];

	return &machine;
}
