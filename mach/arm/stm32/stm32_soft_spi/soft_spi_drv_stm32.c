/*
 * drv_avr.c
 *
 *  Created on: Feb 14, 2015
 *      Author: franz
 */

#include <soft_spi_drv_stm32.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define SOFT_SPI_SCK_RCC_PORT	RCC_GPIOC
#define SOFT_SPI_SCK_PORT 		GPIOC
#define SOFT_SPI_SCK_PIN		GPIO10

#define SOFT_SPI_MISO_RCC_PORT	RCC_GPIOC
#define SOFT_SPI_MISO_PORT 		GPIOC
#define SOFT_SPI_MISO_PIN		GPIO11

#define SOFT_SPI_MOSI_RCC_PORT	RCC_GPIOC
#define SOFT_SPI_MOSI_PORT 		GPIOC
#define SOFT_SPI_MOSI_PIN		GPIO12

#define SOFT_SPI_CS0_RCC_PORT	RCC_GPIOE
#define SOFT_SPI_CS0_PORT 		GPIOE
#define SOFT_SPI_CS0_PIN 		GPIO8

static void set_mosi(uint8_t val)
{
	if(val == SOFT_SPI_HIGH)
	{
		gpio_set(SOFT_SPI_MOSI_PORT, SOFT_SPI_MOSI_PIN);
	}
	else
	{
		gpio_clear(SOFT_SPI_MOSI_PORT, SOFT_SPI_MOSI_PIN);
	}
}

static uint8_t get_miso(void)
{
	return gpio_get(SOFT_SPI_MISO_PORT, SOFT_SPI_MISO_PIN);
}

static void set_clk(uint8_t val)
{
	if(val == SOFT_SPI_HIGH)
	{
		gpio_set(SOFT_SPI_SCK_PORT, SOFT_SPI_SCK_PIN);
	}
	else
	{
		gpio_clear(SOFT_SPI_SCK_PORT, SOFT_SPI_SCK_PIN);
	}
	#ifdef SOFT_SPI_USE_SCK_DELAY
		_delay_ms(5)
	#endif
}

static void set_cs(uint8_t pin, uint8_t val)
{
	switch(pin)
	{
	case 0:
		if(val == SOFT_SPI_HIGH)
		{
			gpio_set(SOFT_SPI_CS0_PORT, SOFT_SPI_CS0_PIN);
		}
		else
		{
			gpio_clear(SOFT_SPI_CS0_PORT, SOFT_SPI_CS0_PIN);
		}
		break;
	default:
		break;
	}
}

void SOFT_SPI_setup_stm32(soft_spi_t *spi)
{
	rcc_periph_clock_enable(SOFT_SPI_SCK_RCC_PORT | SOFT_SPI_MISO_RCC_PORT | SOFT_SPI_MOSI_RCC_PORT | SOFT_SPI_CS0_RCC_PORT);

	gpio_mode_setup(SOFT_SPI_SCK_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SOFT_SPI_SCK_PIN);
	gpio_mode_setup(SOFT_SPI_MISO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, SOFT_SPI_MISO_PIN);
	gpio_mode_setup(SOFT_SPI_MOSI_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SOFT_SPI_MOSI_PIN);
	gpio_mode_setup(SOFT_SPI_CS0_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SOFT_SPI_CS0_PIN);

	gpio_set(SOFT_SPI_MOSI_PORT, SOFT_SPI_MOSI_PIN);
	gpio_set(SOFT_SPI_CS0_PORT, SOFT_SPI_CS0_PIN);

	spi->get_miso = get_miso;
	spi->set_mosi = set_mosi;
	spi->set_clk = set_clk;
	spi->set_cs = set_cs;
}
