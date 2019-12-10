#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "driver/gpio.h"
//-----------------------------------------------
#define BLINK_GPIO GPIO_NUM_2
#define BUTTON_GPIO GPIO_NUM_4
//-----------------------------------------------
void app_main(void)
{
 gpio_pad_select_gpio(BLINK_GPIO);
 gpio_pad_select_gpio(BUTTON_GPIO);
 gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLUP_ONLY);
 gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
 gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
 while (1)
 {
   gpio_set_level(BLINK_GPIO, 0);
   vTaskDelay(100 / portTICK_PERIOD_MS);
   if(!gpio_get_level(BUTTON_GPIO))   gpio_set_level(BLINK_GPIO, 1);
   vTaskDelay(100 / portTICK_PERIOD_MS);
 }
}
//-----------------------------------------------

