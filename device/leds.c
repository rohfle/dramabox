/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define POWER_GPIO CONFIG_POWER_GPIO
#define WIFI_GPIO CONFIG_WIFI_GPIO
#define INTERNET_GPIO CONFIG_INTERNET_GPIO


#define DELAY_PERIOD

void leds_task(void *pvParameter)
{
  Ticktype_t xLastWakeTime;
  // setup GPIOs
  gpio_pad_select_gpio(POWER_GPIO);
  gpio_set_direction(POWER_GPIO, GPIO_MODE_OUTPUT);
  gpio_pad_select_gpio(WIFI_GPIO);
  gpio_set_direction(WIFI_GPIO, GPIO_MODE_OUTPUT);
  gpio_pad_select_gpio(INTERNET_GPIO);
  gpio_set_direction(INTERNET_GPIO, GPIO_MODE_OUTPUT);

  xLastWakeTime = xTaskGetTickCount();

  do {
    vTaskDelayUntil(&xLastWakeTime, DELAY_PERIOD);

    if (sleep) {
      gpio_set_level(POWER_GPIO, 0);
    } else {
      gpio_set_level(POWER_GPIO, 1);
    }

    if (internet) {
      gpio_set_level(WIFI_GPIO, 0);
      gpio_set_level(INTERNET_GPIO, 1);
    } else if (wifi) {
      gpio_set_level(WIFI_GPIO, 1);
      gpio_set_level(INTERNET_GPIO, 0);
    } else {
      gpio_set_level(WIFI_GPIO, 0);
      gpio_set_level(INTERNET_GPIO, 0);
    }
  } while(1);
}

void app_main()
{
    xTaskCreate(&leds_task, "leds_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
