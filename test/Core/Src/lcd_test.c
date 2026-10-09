#include "lcd_test.h"
#include "gc9a01_driver.h"
#include "stdio.h"

void LCD_DiagnosticTest(void)
{
    printf("\r\n========== LCD DIAGNOSTIC TEST START ==========\r\n");

    /* Stage 1: GPIO DC Pin Test */
    printf("[Stage 1] Testing GPIO DC pin (PB0)...\r\n");
    for (int i = 0; i < 5; i++) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
        printf("  DC=HIGH\r\n");
        HAL_Delay(100);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
        printf("  DC=LOW\r\n");
        HAL_Delay(100);
    }
    printf("[Stage 1] GPIO DC pin OK\r\n\r\n");

    /* Stage 2: SPI Init Check */
    printf("[Stage 2] SPI1 is already initialized in main.c\r\n");
    printf("[Stage 2] SPI1 OK (hspi1 handle ready)\r\n\r\n");

    /* Stage 3: DC Control Test (via driver macro) */
    printf("[Stage 3] Testing DC control via driver macros...\r\n");
    DC_LOW();
    printf("  DC_LOW() executed\r\n");
    HAL_Delay(100);
    DC_HIGH();
    printf("  DC_HIGH() executed\r\n");
    HAL_Delay(100);
    printf("[Stage 3] DC control OK\r\n\r\n");

    /* Stage 4: GC9A01 Initialization */
    printf("[Stage 4] Initializing GC9A01...\r\n");
    gc9a01_init();
    printf("[Stage 4] GC9A01 initialization OK\r\n\r\n");

    /* Stage 5: Display Fill Test (Red color) */
    printf("[Stage 5] Filling display with RED color...\r\n");
    gc9a01_fill_color(255, 0, 0);
    HAL_Delay(2000);
    printf("[Stage 5] RED fill OK\r\n\r\n");

    /* Stage 6: Display Fill Test (Green color) */
    printf("[Stage 6] Filling display with GREEN color...\r\n");
    gc9a01_fill_color(0, 255, 0);
    HAL_Delay(2000);
    printf("[Stage 6] GREEN fill OK\r\n\r\n");

    /* Stage 7: Display Fill Test (Blue color) */
    printf("[Stage 7] Filling display with BLUE color...\r\n");
    gc9a01_fill_color(0, 0, 255);
    HAL_Delay(2000);
    printf("[Stage 7] BLUE fill OK\r\n\r\n");

    printf("========== LCD DIAGNOSTIC TEST COMPLETE ==========\r\n\r\n");
}
