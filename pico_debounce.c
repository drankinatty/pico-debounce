/* Raspberry Pi Pico Debounce
 *
 * Copyright (c) David C. Rankin, 2022
 * License: GPLv2
 */

#include "pico_debounce.h"

/* one timeout for each gpio, set as debounce_timeouts[gpio] */
volatile absolute_time_t debounce_timeouts[NGPIO] = { 0u };


/** debounce function takes gpio pin to debounce as argument and
 *  returns true if pin is currently in debounce state, false otherwise
 */
bool debounce (uint gpio)
{
  /* check if gpio is less than DEBOUNCE_MS from time set */
  if (get_absolute_time() < debounce_timeouts[gpio]) {
    return true;
  }

  /* otherwise set new debouce timout for gpio pin */
  debounce_timeouts[gpio] = make_timeout_time_ms(DEBOUNCE_MS);

  return false;
}

/* alternate setting of timeout */
// debounce_timeouts[gpio] = get_absolute_time() + DEBOUNCE_MS;
