#ifndef PICO_DEBOUNCE_H
#define PICO_DEBOUNCE_H  1

/* Raspberry Pi Pico Debounce
 *
 * Copyright (c) David C. Rankin, 2022
 * License: GPLv2
 */

#include "pico/stdlib.h"

/* NGPIO -       number of gpio to size debounce_timeouts array
 * DEBOUNCE_MS - number of ms to debounce, note: breadboard pushbuttons
 *               are horrible and can bounce both in the switch and at
 *               the breadboard pins. 180 ms doesn't catch all, 200 does and
 *               leaves reasonable ability to catch double-clicks.
 *               Adjust as necessary. For soldered switches, 35 ms may do.
 */
#define NGPIO          30
#define DEBOUNCE_MS   200


/** debounce function takes gpio pin to debounce as argument and
 *  returns true if pin is currently in debounce state, false otherwise
 */
bool debounce (uint gpio);


#endif
