/*
 * gpio_common.h
 *
 *  Created on: Feb 26, 2015
 *      Author: fflasch
 */

#ifndef GPIO_COMMON_H_
#define GPIO_COMMON_H_

/*
 * spi_common.h
 *
 *  Created on: Feb 14, 2015
 *      Author: franz
 */

#include <stdint.h>

#define GPIO_COMMON_LOW 0
#define GPIO_COMMON_HIGH 1

typedef struct gpio_controller_s gpio_controller_t;

typedef enum gpio_mode
{
    ACTIVE_LOW,
    ACTIVE_HIGH

}gpio_mode_e;

struct gpio_controller_s
{
    uint8_t mode;
    uint8_t nrpins;
    void (*GPIO_set)(gpio_controller_t *gpio, uint8_t pin, uint8_t val);
    uint8_t (*GPIO_get)(gpio_controller_t *gpio, uint8_t pin);
    void *platform_drv_info;
};

void GPIO_init_controller(gpio_controller_t *controller,
                          gpio_mode_e mode,
                          uint8_t nrpins,
                          void (*gpio_set)(gpio_controller_t *gpio, uint8_t pin, uint8_t val),
                          uint8_t (*gpio_get)(gpio_controller_t *gpio, uint8_t pin),
                          void *platform_drv_info);

void GPIO_set(gpio_controller_t *gpio, uint8_t pin, uint8_t val);
uint8_t GPIO_get(gpio_controller_t *gpio, uint8_t pin);

#define GPIO_set(gpio, pin, val)        \
do {                                    \
    if(gpio->GPIO_set != NULL)          \
        gpio->GPIO_set(gpio, pin, val); \
} while(0)

#define GPIO_get(gpio, pin)                 \
do {                                        \
    if(gpio->GPIO_get != NULL)              \
        return gpio->GPIO_get(gpio, pin);   \
    else                                    \
        return 0xFF;                        \
} while(0)

#endif /* GPIO_COMMON_H_ */
