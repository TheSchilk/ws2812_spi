/*
 * ws2812b.h
 *
 *  Created on: May 5, 2021
 *      Author: pschilk
 */

#ifndef INC_WS2812B_H_
#define INC_WS2812B_H_

#include <stdint.h>

typedef enum{
	WS2812B_PACKING_8b = 1,
	WS2812B_PACKING_4b = 2
} ws2812b_packing_t;

typedef struct{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} ws2812b_led_t;

typedef struct{
	ws2812b_packing_t packing;
	uint32_t led_count;
	ws2812b_led_t *leds;
}ws2812b_handle_t;

#define WS2812B_REQUIRED_BUFFER_LEN(led_count, packing) ((led_count*(packing == WS2812B_PACKING_8b ? 24 : 12))+5) // +5: 1 0x00 at beginning, 4 at end.

void ws2812b_fill_buffer(ws2812b_handle_t *ws, uint8_t *buffer);

#endif /* INC_WS2812bB_H_ */
