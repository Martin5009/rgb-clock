#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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

enum led_matrix_pwm_levels{
    LED_MATRIX_PWM_1 = 0,
    LED_MATRIX_PWM_3 = 2,
    LED_MATRIX_PWM_256 = 255};
typedef enum led_matrix_pwm_levels led_matrix_pwm_levels;

typedef struct {
    gpio_num_t oe_io_pin;
    gpio_num_t clk_io_pin;
    gpio_num_t lat_io_pin;
    gpio_num_t r1_io_pin;
    gpio_num_t g1_io_pin;
    gpio_num_t b1_io_pin;
    gpio_num_t r2_io_pin;
    gpio_num_t g2_io_pin;
    gpio_num_t b2_io_pin;
    gpio_num_t a_io_pin;
    gpio_num_t b_io_pin;
    gpio_num_t c_io_pin;
} led_matrix_io_t;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} led_matrix_rgb_t;

typedef struct {
    uint8_t refresh_rate;           //display refresh rate capped at 200Hz
    uint8_t width;
    uint8_t height;
    uint8_t pwm_cnt;
    led_matrix_pwm_levels pwm_level;
    TaskHandle_t refresh_task;
    gptimer_handle_t refresh_timer; //used to generate periodic interrupts for display refresh
    led_matrix_io_t *io_assign;
} led_matrix_config_t;

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

typedef led_matrix_t *led_matrix_handle_t;

esp_err_t led_matrix_init(led_matrix_config_t* led_config, led_matrix_handle_t led_matrix);

esp_err_t led_matrix_start_refresh(led_matrix_handle_t led_matrix_handle);

esp_err_t led_matrix_stop_refresh(led_matrix_handle_t led_matrix_handle);

static void led_matrix_refresh_task(void *pvParameters);

void led_matrix_set_buffer(led_matrix_handle_t led_matrix_handle, led_matrix_rgb_t *buffer);

static void led_matrix_write_screen(led_matrix_handle_t led_matrix_handle);

static bool IRAM_ATTR led_matrix_refresh_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data);


