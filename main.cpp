#include "mbed.h"

#define BLINKING_RATE    500ms
#define BUTTON_POLL_RATE 50ms

void set_led1_state(DigitalOut &led, bool on)
{
    led = on ? 1 : 0;
}

void blink_led1(DigitalOut &led)
{
    led = !led; // toggle LED state
}

int main()
{
#ifdef LED1
    DigitalOut led(LED1);
    bool previous_led_state = (led.read() != 0);
    if (previous_led_state) {
        printf("LED1 starts as ON\n");
    } else {
        printf("LED1 starts as OFF\n");
    }
#endif

#ifdef BUTTON1
    // BUTTON1 is often active-low
    DigitalIn button(BUTTON1, PullUp);
    bool previous_pressed = false;
    uint32_t button_press_count = 0;
#endif

    while (true) {
#if defined(LED1) && defined(BUTTON1)
        bool pressed = (button.read() == 0);
        set_led1_state(led, pressed);   // LED ON when button pressed

        // Count and report only on new button press events.
        if (pressed && !previous_pressed) {
            button_press_count++;
            printf("BUTTON1 pressed %lu time(s)\n", static_cast<unsigned long>(button_press_count));
        }
        previous_pressed = pressed;

        ThisThread::sleep_for(BUTTON_POLL_RATE);
#elif defined(LED1)
        blink_led1(led);
        ThisThread::sleep_for(BLINKING_RATE);
#else
        ThisThread::sleep_for(BUTTON_POLL_RATE);
#endif

#if defined(LED1)
        bool current_led_state = (led.read() != 0);
        if (current_led_state != previous_led_state) {
            printf("LED1 is %s\n", current_led_state ? "ON" : "OFF");
            previous_led_state = current_led_state;
        }
#endif
    }
}
