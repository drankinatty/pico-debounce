/*
 *    Pico button wiring:
 *
 *              |                |
 *              |        GPIO 17 |--- Down Button --> Ground
 *              |        GPIO 16 |--- Up Button --> Ground
 *              +----------------+
 *
 * Copyright (c) David C. Rankin, 2022
 * License: GPLv2
 */
#include <stdio.h>
#include "pico/stdlib.h"

#include "pico_debounce.h"    /* include debounce header */

#define BUTTON_UP    16
#define BUTTON_DOWN  17

#define LED_PIN      PICO_DEFAULT_LED_PIN

/* required extern for debounce_timeouts array */
extern volatile absolute_time_t debounce_timeouts[NGPIO];

volatile uint count = 0;

/** button_callback checks/sets debounce state returning
 *  true if button is in inactive debounce state preventing
 *  response, or false if button is active ready to respond.
 */
void button_callback (uint gpio, uint32_t events)
{
  /* check/register debounce on gpio */
  if (debounce (gpio)) {
    return;
  }

  /* increment/decrement count based on button press */
  if (gpio == BUTTON_UP) {
    count++;
  }
  else if (count > 0 && gpio == BUTTON_DOWN) {
    count--;
  }

  /* turn on for odd numbers */
  gpio_put (LED_PIN, count & 1);
}


int main (void) {

  stdio_init_all();

  /* init on-board LED */
  gpio_init (LED_PIN);
  gpio_set_dir (LED_PIN, GPIO_OUT);

  /* initialize buttons with pull-up resistors */
  gpio_init (BUTTON_UP);
  gpio_pull_up (BUTTON_UP);

  gpio_init (BUTTON_DOWN);
  gpio_pull_up (BUTTON_DOWN);

  /* set button_callback */
  gpio_set_irq_enabled_with_callback (BUTTON_UP, GPIO_IRQ_EDGE_FALL,
                                      true, button_callback);
  gpio_set_irq_enabled (BUTTON_DOWN, GPIO_IRQ_EDGE_FALL, true);

  /* set CIVIS (cursor invisible) and output fixed text */
  fputs ("\033[?25l\nButton Debounce\n\n  count:\r", stdout);

  while (1) {

    /* pico studio library is flaky, must update count each iteration
     * rather than being able to condition output on if (count != last) ...
     * Advance past "count:", clear to end of line, output count.
     * (remove ANSI escapes if not supported by your terminal)
     */
    printf ("\033[8C\033[0K %2u\r", count);
    fflush (stdout);

    sleep_ms(50);   /* delay to allow printf to work and not peg CPU */
  }
}
