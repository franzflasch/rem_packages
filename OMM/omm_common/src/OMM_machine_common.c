/*
 * OMM_machine_common.c
 *
 *  Created on: Feb 24, 2015
 *      Author: fflasch
 */

#include <OMM_machine_common.h>

/* we use our own strcmp function, because the SDCC version of strcmp is somehow faulty */
static int OMM_str_cmp (const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 != '\0') {
        if (*p2 == '\0') return  1;
        if (*p2 > *p1)   return -1;
        if (*p1 > *p2)   return  1;

        p1++;
        p2++;
    }

    if (*p2 != '\0') return -1;

    return 0;
}

void *OMM_get_pdev_by_name(OMM_machine_t *machine, char *name)
{
    OMM_platform_devices *pdev = machine->pdev_list;

    while(pdev->name != 0)
    {
        if (OMM_str_cmp(pdev->name,name) == 0)
            break;
        pdev++;
    }

    return pdev->pdev;
}

void *OMM_get_pdev_by_index(OMM_machine_t *machine, uint8_t index)
{
    OMM_platform_devices *pdev = machine->pdev_list;
    return pdev[index].pdev;
}

int OMM_machine_is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}
