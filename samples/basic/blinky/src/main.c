#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

/* Define the nodes corresponding to the LEDs */
#define LED0_NODE DT_NODELABEL(led0)
#define LED1_NODE DT_NODELABEL(led1)

/* Get the GPIO device specifications for both LEDs */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

void main(void)
{
    if (!device_is_ready(led0.port) || !device_is_ready(led1.port)) {
        return;
    }

    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);

    while (1) {
        /* Toggle LED0 on, LED1 off */
        gpio_pin_set_dt(&led0, 1);
        gpio_pin_set_dt(&led1, 0);
        k_msleep(1000); /* Sleep for 1000 ms */

        /* Toggle LED0 off, LED1 on */
        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 1);
        k_msleep(1000); /* Sleep for 1000 ms */
    }

    return 0;
}