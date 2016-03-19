#include <rfm12.h>
#include <stdlib.h>


/* send and receive multiple bytes over SPI */
static void rfm12_transfer_spi(rfm12_ctrl_info_t *rfm12, uint8_t* dataout, uint8_t* datain, uint8_t len)
{
    rfm12->SPI_transfer_msg(rfm12->spi, dataout, datain, len);
}

/* PUBLIC */
void rfm12_drv_init(rfm12_ctrl_info_t *rfm12,
                void *rfm12_spi,
                void *spi_transfer_byte,
                void *spi_transfer_msg,
                void *delay_func)
{
    rfm12->spi = rfm12_spi;
    rfm12->SPI_transfer_byte = spi_transfer_byte;
    rfm12->SPI_transfer_msg = spi_transfer_msg;

    rfm12->delay_func = delay_func;
}

uint16_t rfm12_write16(rfm12_ctrl_info_t *rfm12, uint16_t data)
{
	uint16_t ret_val16;
	uint8_t data_to_write[2] = {0,0};
	uint8_t data_to_receive[2] = {0,0};

    data_to_write[0] = (data >> 8);
    data_to_write[1] = (data & 0x00FF);

    rfm12_transfer_spi(rfm12, data_to_write, data_to_receive, 2);

    ret_val16 = ((data_to_receive[0] << 8) | data_to_receive[1]);
    return ret_val16;
}

void RFM12_Init(rfm12_ctrl_info_t *rfm12)
{
    /* wait until POR done */
    rfm12->delay_func(1000);

    //RFM12_Write(0x0000);
    rfm12_write16(rfm12, 0x0000);
    
    //RFM12_Write(0xC0E0);    /* clockout: 10MHz */
    rfm12_write16(rfm12, 0xC0E0);

    //RFM12_Write(0x80D7);    /* enable FIFO */
    rfm12_write16(rfm12, 0x80D7);

    //RFM12_Write(0xC2AB);    /* data filter: internal */
    rfm12_write16(rfm12, 0xC2AB);

    //RFM12_Write(0xCA81);    /* set FIFO mode */
    rfm12_write16(rfm12, 0xCA81);

    //RFM12_Write(0xE000);    /* disable wakeuptimer */
    rfm12_write16(rfm12, 0xE000);

    //RFM12_Write(0xC800);    /* disable low duty cycle */
    rfm12_write16(rfm12, 0xC800);

    //RFM12_Write(0xC4F7);    /* AFC settings: autotuning: -10kHz...+7,5kHz */
    rfm12_write16(rfm12, 0xC4F7);
}

/*****************************************************************************/
/* RFM12_SetBandwidth                                                        */
/*                                                                           */
/* Set bandwidth.                                                            */
/*                                                                           */
/* bandwidth:  Baseband Bandwidth [kHz]                                      */
/*             0 .. reserved                                                 */
/*             1 .. 400 kHz                                                  */
/*             2 .. 340 kHz                                                  */
/*             3 .. 270 kHz                                                  */
/*             4 .. 200 kHz                                                  */
/*             5 .. 134 kHz                                                  */
/*             6 .. 67 kHz                                                   */
/*             7 .. reserved                                                 */
/* gain:       LNA gain (dBm)                                                */
/*             0 .. 0 dBm                                                    */
/*             1 .. -6 dBm                                                   */
/*             2 .. -14 dBm                                                  */
/*             3 .. -20 dBm                                                  */
/* drssi:      RSSIsetth [dBm]                                               */
/*             0 .. -103 dBm                                                 */
/*             1 .. -97 dBm                                                  */
/*             2 .. -91 dBm                                                  */
/*             3 .. -85 dBm                                                  */
/*             4 .. -79 dBm                                                  */
/*             5 .. -73 dBm                                                  */
/*             6 .. reserved                                                 */
/*             7 .. reserved                                                 */
/*                                                                           */
/* Return:  none                                                             */
/*****************************************************************************/
void RFM12_SetBandwidth(rfm12_ctrl_info_t *rfm12, uint8_t bandwidth, uint8_t gain, uint8_t drssi)
{
    //RFM12_Write(0x9400|((bandwidth&7)<<5)|((gain&3)<<3)|(drssi&7));
	rfm12_write16(rfm12, (0x9400|((bandwidth&7)<<5)|((gain&3)<<3)|(drssi&7)));
}

/*****************************************************************************/
/* RFM12_SetFreq                                                             */
/*                                                                           */
/* Set frequency. Use RFM12FREQ macro to convert frequency to proper value.  */
/*                                                                           */
/* freq:  RFM12 frequency for wireless communication                         */
/*        Example usage: RFM12_SetFreq(RFM12FREQ(430.2400MHz));              */
/*        Possible frequency values: 430.2400MHz .. 439.7575MHz              */
/*                                                                           */
/* Return:  none                                                             */
/*****************************************************************************/
void RFM12_SetFreq(rfm12_ctrl_info_t *rfm12, uint16_t freq)
{
    /* 430.2400MHz */
    if (freq < 96)
    {
        freq = 96;
    }
    /* 439.7575MHz */
    else if (freq > 3903)
    {
        freq = 3903;
    }
    rfm12_write16(rfm12, (0xA000 | freq));
}

/*****************************************************************************/
/* RFM12_SetBaud                                                             */
/*                                                                           */
/* Set baudrate.                                                             */
/*                                                                           */
/* baud:  desired baudrate                                                   */
/*                                                                           */
/* Return:  none                                                             */
/*****************************************************************************/
void RFM12_SetBaud(rfm12_ctrl_info_t *rfm12, uint16_t baud)
{
    if (baud < 663)
    {
        return;
    }

    /* Baudrate= 344827,58621/(R+1)/(1+CS*7) */
    if (baud < 5400)
    {
        rfm12_write16(rfm12, (0xC680|((43104/baud)-1)));
    }
    else
    {
        rfm12_write16(rfm12, (0xC600|((344828UL/baud)-1)));
    }
}

/*****************************************************************************/
/* RFM12_SetPower                                                            */
/*                                                                           */
/* Set output power.                                                         */
/*                                                                           */
/* power:  output power                                                      */
/*         0 .. 0 dBm (1mW)                                                  */
/*         1 .. -3 dBm (501 \B5W)                                            */
/*         2 .. -6 dBm (251 \B5W)                                            */
/*         3 .. -9 dBm (126 \B5W)                                            */
/*         4 .. -12 dBm (63 \B5W)                                            */
/*         5 .. -15 dBm (32 \B5W)                                            */
/*         6 .. -18 dBm (16 \B5W)                                            */
/*         7 .. -21 dBm (8 \B5W)                                             */
/* mod:    frequency deviation                                               */
/*         0 .. 15 kHz                                                       */
/*         1 .. 30 kHz                                                       */
/*         2 .. 45 kHz                                                       */
/*         3 .. 60 kHz                                                       */
/*         4 .. 75 kHz                                                       */
/*         5 .. 90 kHz                                                       */
/*         6 .. 105 kHz                                                      */
/*         7 .. 120 kHz                                                      */
/*         8 .. 135 kHz                                                      */
/*         9 .. 150 kHz                                                      */
/*         10 .. 165 kHz                                                     */
/*         11 .. 180 kHz                                                     */
/*         12 .. 195 kHz                                                     */
/*         13 .. 210 kHz                                                     */
/*         14 .. 225 kHz                                                     */
/*         15 .. 240 kHz                                                     */
/*                                                                           */
/* Return:  none                                                             */
/*****************************************************************************/
void RFM12_SetPower(rfm12_ctrl_info_t *rfm12, uint8_t power, uint8_t mod)
{
    rfm12_write16(rfm12, (0x9800|(power&7)|((mod&15)<<4)));
}


// TODO: remove this hack here
#include <avr/io.h>

#define SOFT_SPI_MISO_DDR_PORT 	DDRB
#define SOFT_SPI_MISO_PORT 		PORTB
#define SOFT_SPI_MISO_PINPUT	PINB
#define SOFT_SPI_MISO_PIN		PB7

#define SOFT_SPI_MOSI_DDR_PORT 	DDRD
#define SOFT_SPI_MOSI_PORT 		PORTD
#define SOFT_SPI_MOSI_PIN		PD7

#define SOFT_SPI_CS0_DDR_PORT 	DDRB
#define SOFT_SPI_CS0_PORT 		PORTB
#define SOFT_SPI_CS0_PIN 		PB6

#define RFM12_ClrSDI()      SOFT_SPI_MOSI_PORT &= ~(1<<SOFT_SPI_MOSI_PIN)
#define RFM12_ClrNSEL()     SOFT_SPI_CS0_PORT &= ~(1<<SOFT_SPI_CS0_PIN)

static uint8_t RFM12_GetSDO(void)
{
	return (SOFT_SPI_MISO_PINPUT & (1 << SOFT_SPI_MISO_PIN));
}

/*****************************************************************************/
/* RFM12_Ready                                                               */
/*                                                                           */
/* Waits until FIFO is ready.                                                */
/*                                                                           */
/* Return:  none                                                             */
/*****************************************************************************/
void RFM12_Ready(void)
{
    RFM12_ClrSDI();
    RFM12_ClrNSEL();

    /* wait until FIFO ready */
    while (!(RFM12_GetSDO()));
}

/*****************************************************************************/
/* RFM12_TxData                                                              */
/*                                                                           */
/* Transmit data via RFM12 wireless tranceiver module.                       */
/*                                                                           */
/* data:   pointer to data buffer to be transmitted                          */
/* length: data buffer length                                                */
/*                                                                           */
/* Return:  none                                                             */
/*****************************************************************************/
void RFM12_TxData(rfm12_ctrl_info_t *rfm12, uint8_t *data, uint8_t length)
{
    uint8_t i;

    /* enable TX */
    rfm12_write16(rfm12,0x8238);
    RFM12_Ready();

    /* send preamble (0xAA) */
    rfm12_write16(rfm12,0xB8AA);
    RFM12_Ready();
    rfm12_write16(rfm12,0xB8AA);
    RFM12_Ready();
    rfm12_write16(rfm12,0xB8AA);
    RFM12_Ready();

    /* send sync word 0x2DD4 */
    rfm12_write16(rfm12,0xB82D);
    RFM12_Ready();
    rfm12_write16(rfm12,0xB8D4);

    /* send data buffer */
    for (i=0; i < length; i++)
    {   RFM12_Ready();
    rfm12_write16(rfm12,0xB800|(*data++));
    }
    RFM12_Ready();

    /* transmit 2 dummy bytes to avoid that last bytes of real payload don't */
    /* get transmitted properly (due to transmitter disabled to early) */
    rfm12_write16(rfm12,0xB800);
    RFM12_Ready();
    rfm12_write16(rfm12,0xB800);
    RFM12_Ready();

    /* disable TX */
    rfm12_write16(rfm12,0x8208);
}

/*****************************************************************************/
/* RFM12_TxData                                                              */
/*                                                                           */
/* Receive data via RFM12 wireless tranceiver module.                        */
/*                                                                           */
/* data:   pointer to data buffer to be received                             */
/* length: number of bytes to be received                                    */
/*                                                                           */
/* Return:  none                                                             */
/*****************************************************************************/
void RFM12_RxData(rfm12_ctrl_info_t *rfm12, uint8_t *data, uint8_t length)
{
    uint8_t i;

    /* enable RX */
    rfm12_write16(rfm12,0x82C8);

    /* set FIFO mode */
    rfm12_write16(rfm12,0xCA81);

    /* enable FIFO */
    rfm12_write16(rfm12,0xCA83);

    RFM12_ClrSDI();
    //delay_us(3);
    for (i=0; i < length; i++)
    {
        RFM12_Ready();
        *data++=rfm12_write16(rfm12,0xB000);
    }

    /* disable RX */
    rfm12_write16(rfm12,0x8208);
}
