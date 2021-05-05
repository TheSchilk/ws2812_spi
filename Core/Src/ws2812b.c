/*
 * ws2812.c
 *
 *  Created on: May 5, 2021
 *      Author: pschilk
 */

#include "ws2812b.h"

// private prototypes
static void add_byte(ws2812b_handle_t *ws, uint8_t value, uint8_t **buffer);


void ws2812b_fill_buffer(ws2812b_handle_t *ws, uint8_t *buffer){
	ws2812b_led_t *led  = ws->leds;


	// Add a single 0x00 prefix to buffer
	*buffer = 0x00;
	buffer++;

	for(uint32_t i = 0; i < ws->led_count; i++){
		add_byte(ws, led->green, &buffer);
		add_byte(ws, led->red, &buffer);
		add_byte(ws, led->blue, &buffer);
		led++;
	}


	// Add 4 0x00 to end of buffer
	*buffer = 0x00;
	buffer++;
	*buffer = 0x00;
	buffer++;
	*buffer = 0x00;
	buffer++;
	*buffer = 0x00;
	buffer++;
}

// private functions

#define VAL_8B_1 (0x3F << 1) // LSB of these must be 0, as they are already present on the MISO pin when the previous transmission ends.
#define VAL_8B_0 (0x07 << 1) //

#define VAL_4B_1
#define VAL_4B_0

static void add_byte(ws2812b_handle_t *ws, uint8_t value,uint8_t **buffer){
	if(ws->packing == WS2812B_PACKING_8b){
		// 8b packing
		for(int b = 0; b < 8; b++){
				**buffer = (value & (1U << b) ? VAL_8B_1 : VAL_8B_0);
				++*buffer;
		}
	} else {
		// 4b packing
		// TODO
	}
}
