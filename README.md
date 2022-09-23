# pico-debounce
Raspberry Pi Pico Software Debounce

When I first got the Raspberry Pi Pico, I looked around to see what people were doing for software button debounce. I was surprised that there were a lot of bad examples of handling debounce either because the proposed solutions were a bit resource intensive, or they lacked the ability to handle multiple buttons on any GPIO pin without further defines.

This debounce routine uses a simple array of `absolute_time_t[30]` (one for each GPIO). When a button press occurs, the current time plus the debounce period is stored in the array indexed by the GPIO pin holding the time in the future the debouce expires. The debounce function returns `true` if checked within the debounce period and false otherwise.

In the button callback, the check of the debounce function passing the GPIO pin will return `true` if debounce is active indicating the remainder of the button callback should be skipped, or will set the future time when the debounce period ends, returning false indicating the button is active and the rest of the callback should be processed.

The check requires nothing but checking a single-element in an array. Setting requires only an assignment of the future time using `make_timeout_time_ms(DEBOUNCE_MS)`.

The code is trivial and broken into a header and source file, but can easily be cut and pasted into individual code. The only requirement other than including the header is the need to declare an `extern` variable for the array holding the timeouts.

A note on the debounce period. The momentary breadboard buttons have horrible debounce times and can bounce both within the switch itself and when the legs of the button make contact within the breadboard itself. For these buttons a large debounce of 200 ms is needed to avoid debounce (some are better than others). I have tested and have bounces with a 180 ms period, but effectively all bounce is eliminated by 200 ms. This also leaves a reasonable opportunity to respond to double-click if desired. Pressing the button 5 times in a second is a fairly rapid rate to begin with.

If your switch is soldered in with good bounce characteristics, you can adjust the debounce period as desired. A minimum of 35 - 50 ms should accommodate most well made buttons.

**Example Program**

The example program provides is a variation on the button count example from pico-examples that uses GPIO 16 for the count increment button and GPIO 17 for counter decrement. The count is display via stdio and will display on the terminal. ANSI escapes are used to have the count update in-place on the terminal. If your terminal doesn't support ANSI escapes you can simply remove them from the example program. The on-board LED is turned on for each odd-number of the count variable.

Due to the quirky nature of the pico-SDK stdio, a short delay is used in the program loop to keep the output at a sane rate. Normally you would only update the count when it changed, but if you include your output inside a conditional, the output is disabled. The Program output will look similar to the following in your terminal:

```none
Button Debounce

  count:  5
```

A `CMakeLists.txt` is provided, so to test, if using a single Pico connected by USB using uart, just swap the values on the final two lines in the file and uncomment them.
