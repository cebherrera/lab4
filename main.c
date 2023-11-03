#include <stdio.h>
#include <stdint.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <string.h>
#include "clock.h"
#include "cdcacm.h"
#include "spi-mems.h"
#include "console.h"
#include "sdram.h"
#include "lcd-spi.h"
#include "gfx.h"

const char myData[] = "Hello, World!";
int dataLength = sizeof(myData) - 1; // Subtract 1 to exclude the null terminator

int i = 0;

extern usbd_device *usbd_dev;

uint8_t who;
#define GYR_RNW			(1 << 7) /* Write when zero */
#define GYR_WHO_AM_I	0x0F

int main(void)
{
	//lcd_spi_init();
	clock_setup();
	sdram_init();
	setup_mems();
	setup_cdcacm();    // Initialize USB device and setup USB configuration

	// Read WHO_AM_I
	//spi_send(SPI5, GYR_WHO_AM_I);
	//who = spi_read(SPI5);
	//spi_send(SPI5, 0);
	
	who = 0xD5;
	// Convert 'who' to a string
	char whoStr[16];
	snprintf(whoStr, sizeof(whoStr), "%d", who);
	//who deberia ser = 0xD4 

	bool sectionExecuted = false;

	int16_t vec[3];
	char xstr[15];
    char ystr[15];
    char zstr[15];
    
	msleep(2000);
	gfx_init(lcd_draw_pixel, 240, 320);
	gfx_fillScreen(LCD_GREY);
    gfx_fillRoundRect(10, 10, 220, 220, 5, LCD_WHITE);
    gfx_drawRoundRect(10, 10, 220, 220, 5, LCD_RED);
    gfx_setTextSize(1);

	while (1) {
        //usbd_poll(usbd_dev);

		(void) read_xyz(vec);
		vec[0] = vec[0];
        vec[1] = vec[1];
        vec[2] = vec[2];

		sprintf(xstr, "X: %d", vec[0]);
        sprintf(ystr, "Y: %d", vec[1]);
        sprintf(zstr, "Z: %d", vec[2]);

		gfx_setCursor(15, 25);
		gfx_puts(xstr);
		gfx_setCursor(15, 65);
		gfx_puts(ystr);
		gfx_setCursor(15, 105);
		gfx_puts(zstr);
		lcd_show_frame();
		msleep(2000);

		//i++;

		//if (i > 1000000) {
		//	if (!sectionExecuted) {
		//	cdcacm_data_tx(usbd_dev, whoStr, strlen(whoStr));
		//	sectionExecuted = true;
        //}
		//}
	}
    return 0;
}