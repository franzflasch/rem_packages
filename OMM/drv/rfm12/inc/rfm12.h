#ifndef RFM12_H
#define RFM12_H

#include <stdint.h>

#define RFM12FREQ(freq)     ((freq-430.0)/0.0025)

typedef struct rfm12_ctrl_info_s
{
    /* spi interface */
   void *spi;

   /* Function pointers to the corresponding SPI driver layer */
   uint8_t (*SPI_transfer_byte)(void *spi, uint8_t val);
   void (*SPI_transfer_msg)(void *spi, uint8_t *data_out, uint8_t *data_in, uint16_t len);

   /* Software layer specific */
   void (*delay_func)(uint64_t val);


} rfm12_ctrl_info_t;



void rfm12_drv_init(rfm12_ctrl_info_t *rfm12,
                void *rfm12_spi,
                void *spi_transfer_byte,
                void *spi_transfer_msg,
                void *delay_func);

void RFM12_Init(rfm12_ctrl_info_t *rfm12);
void RFM12_SetBandwidth(rfm12_ctrl_info_t *rfm12, uint8_t bandwidth, uint8_t gain, uint8_t drssi);
void RFM12_SetFreq(rfm12_ctrl_info_t *rfm12, uint16_t freq);
void RFM12_SetBaud(rfm12_ctrl_info_t *rfm12, uint16_t baud);
void RFM12_SetPower(rfm12_ctrl_info_t *rfm12, uint8_t power, uint8_t mod);
void RFM12_Ready(void);
void RFM12_TxData(rfm12_ctrl_info_t *rfm12, uint8_t *data, uint8_t length);
void RFM12_RxData(rfm12_ctrl_info_t *rfm12, uint8_t *data, uint8_t length);

#endif
