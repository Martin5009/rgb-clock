#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_types.h"
#include "esp_system.h"
#include "sdkconfig.h"
#include "driver/gptimer.h"
#include "driver/gpio.h"

#define LED_MATRIX_REFRESH_TIMEOUT_THRESHOLD pdMS_TO_TICKS(5000)

//Defines the number of brightness levels available 
//for individual R, G, or B LEDs
enum led_matrix_pwm_levels{
    LED_MATRIX_PWM_1 = 0,
    LED_MATRIX_PWM_8 = 7,
    LED_MATRIX_PWM_16 = 15,
    LED_MATRIX_PWM_32 = 31,
    LED_MATRIX_PWM_64 = 63,
    LED_MATRIX_PWM_128 = 127,
    LED_MATRIX_PWM_256 = 255};
typedef enum led_matrix_pwm_levels led_matrix_pwm_levels;

//GPIO pin assignments
typedef struct {
    gpio_num_t oe;
    gpio_num_t clk;
    gpio_num_t lat;
    gpio_num_t r1;
    gpio_num_t g1;
    gpio_num_t b1;
    gpio_num_t r2;
    gpio_num_t g2;
    gpio_num_t b2;
    gpio_num_t a;
    gpio_num_t b;
    gpio_num_t c;
    gpio_num_t d;
} led_matrix_io_t;

//RGB LED object
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_matrix_rgb_t;

//LED matrix configuration
typedef struct {
    uint8_t refresh_rate;           
    uint8_t width;
    uint8_t height;
    uint8_t pwm_cnt;
    led_matrix_pwm_levels pwm_level;
    TaskHandle_t refresh_task;      //NULL task handle
    gptimer_handle_t refresh_timer; //NULL gptimer handle
    led_matrix_io_t *io_assign;
} led_matrix_config_t;

//LED matrix object
typedef struct {
    uint8_t refresh_rate;
    uint8_t width;
    uint8_t height;
    uint8_t pwm_cnt;
    led_matrix_pwm_levels pwm_level;
    TaskHandle_t refresh_task;
    led_matrix_rgb_t *buffer_1;
    gptimer_handle_t refresh_timer;
    led_matrix_io_t *io_assign;
} led_matrix_t;

//LED matrix handle
typedef led_matrix_t *led_matrix_handle_t;

/**
 * @brief Initialize LED matrix using led_config
 * 
 * @param[in] led_config LED matrix configuration struct
 * @param[out] led_matrix_handle LED matrix handle
*/
esp_err_t led_matrix_init(led_matrix_config_t *led_config, led_matrix_handle_t *led_matrix_handle);

/**
 * @brief Begins the LED matrix refresh cycle
 * 
 * @param[in] led_matrix_handle LED matrix handle
*/
esp_err_t led_matrix_start_refresh(led_matrix_handle_t led_matrix_handle);

/**
 * @brief Ends the LED matrix refresh cycle
 * 
 * @param[in] led_matrix_handle LED matrix handle
*/
esp_err_t led_matrix_stop_refresh(led_matrix_handle_t led_matrix_handle);

/**
 * @brief Manually set the led_matrix frame buffer
*/
void led_matrix_set_buffer(led_matrix_handle_t led_matrix_handle, led_matrix_rgb_t *buffer);


/**
 * @brief Refresh task that runs upon receiving refresh interrupt
*/
static void led_matrix_refresh_task(void *pvParameters);

/**
 * @brief Directly controls LED matrix GPIO pins
*/
static void led_matrix_write_screen(led_matrix_handle_t led_matrix_handle);

/**
 * @brief Refresh interrupt handler that defers to refresh task
*/
static bool IRAM_ATTR led_matrix_refresh_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data);


