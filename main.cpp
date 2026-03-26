/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define BUTTON_POLL_RATE  50ms

#ifdef LED1
void set_led1_state(DigitalOut &led, bool on)
{
    led = on ? 1 : 0;
}
#endif


int main()
{
    // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led = false;
#endif

#ifdef BUTTON1
    // Many boards wire BUTTON1 as active-low, so PullUp is used.
    DigitalIn button(BUTTON1, PullUp);
#endif

    while (true) {
#if defined(LED1) && defined(BUTTON1)
        bool pressed = (button.read() == 0);
        set_led1_state(led, pressed);
        ThisThread::sleep_for(BUTTON_POLL_RATE);
#elif defined(LED1)
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
#else
        ThisThread::sleep_for(BUTTON_POLL_RATE);
#endif
    }
}
