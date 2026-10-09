#ifndef GC9A01_DRIVER_H
#define GC9A01_DRIVER_H

#include "main.h"

/* DC Pin Control */
#define DC_HIGH() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)
#define DC_LOW()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)

/* GC9A01 Commands */
#define GC9A01_SWRESET    0x01
#define GC9A01_SLPOUT     0x11
#define GC9A01_DISPON     0x29
#define GC9A01_CASET      0x2A
#define GC9A01_RASET      0x2B
#define GC9A01_RAMWR      0x2C
#define GC9A01_MADCTL     0x36
#define GC9A01_COLMOD     0x3A
#define GC9A01_GCTRL      0xB2
#define GC9A01_VCOMS      0xBB
#define GC9A01_LCMCTRL    0xC0
#define GC9A01_VDVVRHEN   0xC2
#define GC9A01_VRHS       0xC3
#define GC9A01_VDVS       0xC4
#define GC9A01_FRCTRL2    0xC6
#define GC9A01_CABCCTRL   0xC7
#define GC9A01_REGSEL1    0xFE
#define GC9A01_REGSEL2    0xEF
#define GC9A01_PWMFRQ     0xFD
#define GC9A01_GAMMA1     0xE0
#define GC9A01_GAMMA2     0xE1

/* Display dimensions */
#define GC9A01_WIDTH      240
#define GC9A01_HEIGHT     240

/* Function Prototypes */
void gc9a01_spi_write_cmd(uint8_t cmd);
void gc9a01_spi_write_data(uint8_t data);
void gc9a01_spi_write_data_array(const uint8_t *data, uint16_t len);
void gc9a01_init(void);
void gc9a01_set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void gc9a01_fill_color(uint8_t r, uint8_t g, uint8_t b);

#endif /* GC9A01_DRIVER_H */
