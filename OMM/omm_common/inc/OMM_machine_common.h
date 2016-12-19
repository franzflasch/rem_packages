/*
 * OMM_machine_common.h
 *
 *  "OpenMicroMake" Common machine description
 *
 *  Created on: Feb 24, 2015
 *      Author: fflasch
 */

#ifndef OMM_MACHINE_COMMON_H_
#define OMM_MACHINE_COMMON_H_

#include <stdint.h>

#ifdef __SDCC
#define USE_OMM_STRCMP
#elif __GNUC__
#endif

typedef struct OMM_platform_devices_s
{
    const char *name;
    void *pdev;

} OMM_platform_devices;

typedef struct OMM_machine_desc_s
{
    /* Machine name */
    const char *name;

    /* Common platform device list */
    OMM_platform_devices *pdev_list;

} OMM_machine_t;

void *OMM_get_pdev_by_name(OMM_machine_t *machine, char *name);
void *OMM_get_pdev_by_index(OMM_machine_t *machine, uint8_t index);
int OMM_machine_is_big_endian(void);

/* These functions are architecure specific and have to be defined externally */
OMM_machine_t *machine_setup(void);
void OMM_busy_delay(uint32_t val);

#endif /* OMM_MACHINE_COMMON_H_ */
