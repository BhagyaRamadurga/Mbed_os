#include "mbed.h"

#define BLINKING_RATE    500ms
#define BUTTON_POLL_RATE 50ms

#ifdef LED1
void set_led1_state(DigitalOut &led, bool on)
{
    led = on ? 1 : 0;
}


#endif
void blink_led1(DigitalOut &led)
{
    led = !led; // toggle LED state
}
int main()
{
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led = false;
#endif

#ifdef BUTTON1
    // BUTTON1 is often active-low
    DigitalIn button(BUTTON1, PullUp);
#endif

    while (true) {
#if defined(LED1) && defined(BUTTON1)
        bool pressed = (button.read() == 0);
        set_led1_state(led, pressed);   // LED ON when button pressed
        ThisThread::sleep_for(BUTTON_POLL_RATE);
#elif defined(LED1)
        led = !led;                     // fallback blink if no button
        ThisThread::sleep_for(BLINKING_RATE);
#else
        ThisThread::sleep_for(BUTTON_POLL_RATE);
#endif
#ifdef LED1
        if (is_led1_on(led)) {
            blink_led1(led);              // blink LED if it's on
        }
#endif
    }
}
