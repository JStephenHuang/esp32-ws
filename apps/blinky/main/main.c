#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

static const gpio_num_t led_pin = GPIO_NUM_4;
static const uint32_t sleep_time_ms = 1000;

void app_main(void) {
    uint8_t led_state = 0;
    
    // configure gpio
    gpio_reset_pin(led_pin);
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);

    // loop
    while (1) {

        // toggle led
        led_state = !led_state;
        gpio_set_level(led_pin, led_state);

        // print led state
        printf("LED state %d\n", led_state);

        // delay
        vTaskDelay(sleep_time_ms / portTICK_PERIOD_MS);
    }
}