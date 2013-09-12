/* bricklib
 * Copyright (C) 2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * led.c: led controlling functions
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include "led.h"

#include <stdbool.h>
#include <stdint.h>

#include "bricklib/drivers/pio/pio.h"

#include "bricklib/utility/util_definitions.h"

#ifdef LED_STD_BLUE
uint32_t led_rxtx = 0;
uint8_t led_counter = 0;
#endif

#ifdef LED_EXT_BLUE_3
uint32_t led_ext3_rxtx = 0;
uint8_t led_ext3_counter = 0;
#endif

#ifdef LED_EXT_BLUE_1
uint32_t led_ext1_rxtx = 0;
uint8_t led_ext1_counter = 0;
#endif

// If the board does not have leds (i.e. PINS_LED is not defined,
// all function will be compiled empty and removed via compiler optimizations)
#ifdef PINS_LED
static const Pin led[] = {PINS_LED};
#define NUM_LED PIO_LISTSIZE(led)
#endif

void led_init() {
#ifdef PINS_LED
	PIO_Configure(led, NUM_LED);
#endif
}

void led_on(const uint8_t led_num) {
#ifdef PINS_LED
	PIO_Clear(&led[led_num]);
#endif
}

void led_off(const uint8_t led_num) {
#ifdef PINS_LED
	PIO_Set(&led[led_num]);
#endif
}

void led_toggle(const uint8_t led_num) {
#ifdef PINS_LED
	if(PIO_GetOutputDataStatus(&led[led_num])) {
		PIO_Clear(&led[led_num]);
	} else {
		PIO_Set(&led[led_num]);
	}
#endif
}

bool led_is_on(const uint8_t led_num) {
#ifdef PINS_LED
	return !PIO_GetOutputDataStatus(&led[led_num]);
#else
	return false;
#endif
}

void led_blink(const uint8_t led_num, const uint32_t delay) {
#ifdef PINS_LED
    led_on(led_num);
    SLEEP_MS(delay);
    led_off(led_num);
#endif
}

// If standard blue led is present, use it for rxtx signaling
void led_tick_task(const uint8_t tick_type) {
#ifdef LED_STD_BLUE
	if(led_counter > 0) {
		led_counter++;
		if(led_counter == LED_RXTX_OFF) {
			led_on(LED_STD_BLUE);
		}

		if(led_counter == LED_RXTX_RESTART) {
			led_counter = 0;
		}
	} else if(led_rxtx > LED_RXTX_NUM) {
		led_off(LED_STD_BLUE);
		led_counter++;
		led_rxtx = 0;
	}
#endif

#ifdef LED_EXT_BLUE_3
	if(led_ext3_counter > 0) {
		led_ext3_counter++;
		if(led_ext3_counter == LED_RXTX_OFF) {
			led_on(LED_EXT_BLUE_3);
		}

		if(led_ext3_counter == LED_RXTX_RESTART) {
			led_ext3_counter = 0;
		}
	} else if(led_ext3_rxtx > LED_RXTX_NUM) {
		led_off(LED_EXT_BLUE_3);
		led_ext3_counter++;
		led_ext3_rxtx = 0;
	}
#endif

#ifdef LED_EXT_BLUE_1
	if(led_ext1_counter > 0) {
		led_ext1_counter++;
		if(led_ext1_counter == LED_RXTX_OFF) {
			led_on(LED_EXT_BLUE_1);
		}

		if(led_ext1_counter == LED_RXTX_RESTART) {
			led_ext1_counter = 0;
		}
	} else if(led_ext1_rxtx > LED_RXTX_NUM) {
		led_off(LED_EXT_BLUE_1);
		led_ext1_counter++;
		led_ext1_rxtx = 0;
	}
#endif
}
