/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


int main()
{
#if !defined(LED1) || !defined(BUTTON1)
#error "This example requires both LED1 and BUTTON1 pin definitions."
#endif

    DigitalOut led(LED1, 0);
    DigitalIn button(BUTTON1, PullUp);

    bool previous_pressed = false;

    while (true) {
        const bool pressed = (button.read() == 0);

        if (pressed && !previous_pressed) {
            led = !led;
            ThisThread::sleep_for(50ms);
        }

        previous_pressed = pressed;
        ThisThread::sleep_for(10ms);
    }
}
