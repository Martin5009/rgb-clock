#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/resource.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "i2c_ds3231.h"
#include "esp_console.h"

#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_NUM_1) | (1ULL<<GPIO_NUM_2) | (1ULL<<GPIO_NUM_41) | (1ULL<<GPIO_NUM_40) | (1ULL<<GPIO_NUM_38) | (1ULL<<GPIO_NUM_37))
#define I2C_MASTER_FREQUENCY 100000

QueueHandle_t time_mailbox;
i2c_master_bus_handle_t bus_handle;
i2c_ds3231_handle_t ds3231_handle;
i2c_ds3231_dec_time_t current_time = {
        .second = 0,
        .minute = 0,
        .hour = 0,
        .day = 1,
        .month = 1
    };

/*--------------------------------------*/
// Task Definitions
/*--------------------------------------*/

void fetch_time_task(void *pvParameters)
{
    for (;;)
    {   
        i2c_ds3231_get_time(ds3231_handle, &current_time);

        xQueueOverwrite(time_mailbox, &current_time);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void show_time_task(void *pvParameters)
{
    i2c_ds3231_dec_time_t time_buffer = {
        .second = 0,
        .minute = 0,
        .hour = 0,
        .day = 0,
        .month = 0
    };
    for (;;) 
    {
        xQueuePeek(time_mailbox, &time_buffer, 0);

        i2c_ds3231_print_dec_time(&time_buffer);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void max_stack_usage_task(void *pvParameters)
{
    uint32_t free_bytes = 0;
    TaskHandle_t task = (TaskHandle_t)pvParameters;

    //Get task name
    char *task_name = NULL;
    task_name = pcTaskGetName(task);
    
    for (;;)
    {
        free_bytes = uxTaskGetStackHighWaterMark2(task);
        printf("%s: %lu free bytes in stack\n", task_name, free_bytes);
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void blink_task(void *pvParameters) 
{
    for(;;)
    {
    gpio_set_level(GPIO_NUM_1,1);
    vTaskDelay(pdMS_TO_TICKS(500));

    gpio_set_level(GPIO_NUM_1,0);
    vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/*--------------------------------------*/
// Entry Point Definition
/*--------------------------------------*/

void app_main(void)
{
    // Configure GPIO
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
        .pull_down_en = 0,
        .pull_up_en = 0,
    };
    gpio_config(&io_conf);

    //Initialize master i2c bus
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = -1,
        .scl_io_num = GPIO_NUM_10,
        .sda_io_num = GPIO_NUM_11,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

    //Initialize DS3231 as i2c device
    i2c_ds3231_config_t i2c_ds3231_config = {
        .ds3231_device.scl_speed_hz = I2C_MASTER_FREQUENCY,
        .ds3231_device.device_address = 0b1101000,
        .hr_mode = I2C_DS3231_24HR_MODE
    };
    ESP_ERROR_CHECK(i2c_ds3231_init(bus_handle, &i2c_ds3231_config, &ds3231_handle));

    //Set time
    i2c_ds3231_set_time(ds3231_handle, &current_time);

    //Create mailbox to hold current time
    time_mailbox = xQueueCreate(1, sizeof(i2c_ds3231_dec_time_t));

    //Create tasks and handles
    TaskHandle_t fetch_time_handle = NULL;
    xTaskCreate(fetch_time_task, "fetch_time", 1200, NULL, 2, &fetch_time_handle);

    TaskHandle_t show_time_handle = NULL;
    xTaskCreate(show_time_task, "show_time", 2000, NULL, 2, &show_time_handle);

    TaskHandle_t blink_handle = NULL;
    xTaskCreate(blink_task, "blink", 1000, NULL, 1, &blink_handle);

    TaskHandle_t fetch_time_usage_handle = NULL;
    xTaskCreate(max_stack_usage_task, "stack_usage2", 2000, (void *)fetch_time_handle, 1, &fetch_time_usage_handle);

    TaskHandle_t show_time_usage_handle = NULL;
    xTaskCreate(max_stack_usage_task, "stack_usage1", 2000, (void *)show_time_handle, 1, &show_time_usage_handle);
}