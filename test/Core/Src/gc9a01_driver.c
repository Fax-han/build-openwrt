#include "gc9a01_driver.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi1;

/* 发送命令字节 (DC=0) */
void gc9a01_spi_write_cmd(uint8_t cmd)
{
    DC_LOW();
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    DC_HIGH();
}

/* 发送数据字节 (DC=1) */
void gc9a01_spi_write_data(uint8_t data)
{
    DC_HIGH();
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
}

/* 发送多个数据字节 */
void gc9a01_spi_write_data_array(const uint8_t *data, uint16_t len)
{
    DC_HIGH();
    HAL_SPI_Transmit(&hspi1, (uint8_t *)data, len, HAL_MAX_DELAY);
}

/* GC9A01 初始化序列 */
void gc9a01_init(void)
{
    printf("[GC9A01] Starting initialization...\r\n");

    /* Reset */
    gc9a01_spi_write_cmd(GC9A01_SWRESET);
    HAL_Delay(150);
    printf("[GC9A01] Reset done\r\n");

    /* Sleep Out */
    gc9a01_spi_write_cmd(GC9A01_SLPOUT);
    HAL_Delay(100);
    printf("[GC9A01] Sleep Out done\r\n");

    /* Color Mode: 16-bit RGB565 */
    gc9a01_spi_write_cmd(GC9A01_COLMOD);
    gc9a01_spi_write_data(0x05);  // 16-bit color
    printf("[GC9A01] Color mode set\r\n");

    /* Memory Access Control */
    gc9a01_spi_write_cmd(GC9A01_MADCTL);
    gc9a01_spi_write_data(0x00);  // Normal direction
    printf("[GC9A01] Memory access control set\r\n");

    /* Gamma 1 */
    gc9a01_spi_write_cmd(GC9A01_GAMMA1);
    const uint8_t gamma1_data[] = {0xF0, 0x04, 0x07, 0x04, 0x04, 0x04, 0x05, 0x06, 0x06, 0x04, 0x04, 0x04, 0x05, 0x06};
    gc9a01_spi_write_data_array(gamma1_data, sizeof(gamma1_data));
    printf("[GC9A01] Gamma 1 set\r\n");

    /* Gamma 2 */
    gc9a01_spi_write_cmd(GC9A01_GAMMA2);
    const uint8_t gamma2_data[] = {0xF0, 0x02, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x04, 0x04, 0x04, 0x05, 0x07};
    gc9a01_spi_write_data_array(gamma2_data, sizeof(gamma2_data));
    printf("[GC9A01] Gamma 2 set\r\n");

    /* Display ON */
    gc9a01_spi_write_cmd(GC9A01_DISPON);
    HAL_Delay(50);
    printf("[GC9A01] Display ON\r\n");
    printf("[GC9A01] Initialization complete!\r\n");
}

/* 设置显示窗口 */
void gc9a01_set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint8_t buf[4];

    /* Column Address Set */
    gc9a01_spi_write_cmd(GC9A01_CASET);
    buf[0] = (x0 >> 8) & 0xFF;
    buf[1] = x0 & 0xFF;
    buf[2] = (x1 >> 8) & 0xFF;
    buf[3] = x1 & 0xFF;
    gc9a01_spi_write_data_array(buf, 4);

    /* Row Address Set */
    gc9a01_spi_write_cmd(GC9A01_RASET);
    buf[0] = (y0 >> 8) & 0xFF;
    buf[1] = y0 & 0xFF;
    buf[2] = (y1 >> 8) & 0xFF;
    buf[3] = y1 & 0xFF;
    gc9a01_spi_write_data_array(buf, 4);

    /* RAM Write */
    gc9a01_spi_write_cmd(GC9A01_RAMWR);
}

/* 填充颜色 (RGB 888 格式转 RGB565) */
void gc9a01_fill_color(uint8_t r, uint8_t g, uint8_t b)
{
    printf("[GC9A01] Filling color: R=%d, G=%d, B=%d\r\n", r, g, b);

    gc9a01_set_address_window(0, 0, GC9A01_WIDTH - 1, GC9A01_HEIGHT - 1);

    /* RGB888 -> RGB565 */
    uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);

    for (uint32_t i = 0; i < GC9A01_WIDTH * GC9A01_HEIGHT; i++) {
        gc9a01_spi_write_data((color >> 8) & 0xFF);
        gc9a01_spi_write_data(color & 0xFF);
    }

    printf("[GC9A01] Fill complete!\r\n");
}
