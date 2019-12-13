#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/task.h"
#include "driver/gpio.h"
//-----------------------------------------------
#define BLINK_GPIO GPIO_NUM_2
#define CONFIG_FREERTOS_HZ 100
//-----------------------------------------------
void app_main(void)
{
 uint32_t i = 0;
 gpio_pad_select_gpio(BLINK_GPIO);
 gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
 esp_chip_info_t chip_info;
 esp_chip_info(&chip_info);
 while (1)
 {
   uint8_t mac_addr[6];
   i++;
   if (i>9999) i=1;
   gpio_set_level(BLINK_GPIO, 0);
   vTaskDelay(500 / portTICK_PERIOD_MS);
   printf("String %04d\n", i);
   printf("Free Heap Size: %04u\n", esp_get_free_heap_size());
   printf("Minimum free Heap Size: %04u\n", esp_get_minimum_free_heap_size());
   esp_efuse_mac_get_default(mac_addr);
   printf("MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
   printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
   printf("silicon revision %d, ", chip_info.revision);
   printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
   gpio_set_level(BLINK_GPIO, 1);
   vTaskDelay(500 / portTICK_PERIOD_MS);
 }
}
//-----------------------------------------------

