/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
#define CHIP_NAME "ESP32-S2 Beta"
#endif

void app_main(void)
{

	gpio_config_t io_conf;
	
	#define GPIO_OUTPUT 4
	#define GPIO_OUTPUT_PIN (1ULL<<GPIO_OUTPUT)
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = GPIO_OUTPUT_PIN;
	gpio_config(&io_conf);

	#define GPIO_INPUT 18
	#define GPIO_INPUT_PIN (1ULL<<GPIO_INPUT)
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pin_bit_mask = GPIO_INPUT_PIN;
	gpio_config(&io_conf);

	uint16_t cnt=0;
	while(1) {
		if ( !gpio_get_level(GPIO_INPUT) )
	        	vTaskDelay(200 / portTICK_RATE_MS);	// push
		else
	        	vTaskDelay(500 / portTICK_RATE_MS);
	        gpio_set_level(GPIO_OUTPUT, cnt++ & 1);
    	}
}
