#ifndef LED_MATRIX_CONTROL_H
#define LED_MATRIX_CONTROL_H

#include <stdint.h>
#include "freertos/task.h"
#include "esp_err.h"
#include "driver/gptimer.h"
#include "driver/gpio.h"
#include "fonts.h"

#define LED_MATRIX_CHAR_WIDTH 5
#define LED_MATRIX_CHAR_HEIGHT 8
#define LED_MATRIX_FONT font

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
    uint16_t refresh_rate;           
    uint8_t width;
    uint8_t height;
    led_matrix_pwm_levels pwm_level;
    gptimer_handle_t refresh_timer; //NULL gptimer handle
    led_matrix_io_t *io_assign;
} led_matrix_config_t;

//LED matrix object
typedef struct {
    uint16_t refresh_rate;
    uint8_t width;
    uint8_t height;
    led_matrix_pwm_levels pwm_level;
    led_matrix_rgb_t* buffer_1;
    gptimer_handle_t refresh_timer;
    led_matrix_io_t* io_assign;
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
 * @brief Draws character on LED matrix at position (x, y) on top of existing buffer contents
 * 
 * @param[in] led_matrix_handle LED matrix handle
 * @param[in] ch Character to draw, either as an ASCII code or single-quoted string (e.g. 'a')
 * @param[in] color RGB value of the drawn character
 * @param[in] x x-coordinate of the drawn character, where x = 0 is the left edge of display/char
 * @param[in] y y-coordinate of the drawn character, where y = 0 is the top edge of the display/char
*/
void led_matrix_draw_char(led_matrix_handle_t led_matrix_handle, char ch, led_matrix_rgb_t color, uint8_t x, uint8_t y);

/**
 * @brief Draws string on LED matrix starting at (x, y)
 * 
 * @param[in] led_matrix_handle LED matrix handle
 * @param[in] str String to draw
 * @param[in] size Size of string to draw
 * @param[in] color RGB value of the drawn string
 * @param[in] x x-coordinate of the drawn string, where x = 0 is the left edge of the display
 * @param[in] y y-coordinate of the drawn string, where y = 0 is the top edge of the display
 */
void led_matrix_draw_str(led_matrix_handle_t led_matrix_handle, char* str, uint8_t size, led_matrix_rgb_t color, uint8_t x, uint8_t y);

/**
 * @brief Set frame buffer
*/
void led_matrix_set_buffer(led_matrix_handle_t led_matrix_handle, led_matrix_rgb_t *buffer);

/**
 * @brief Clear frame buffer
*/
void led_matrix_clear_buffer(led_matrix_handle_t led_matrix_handle);

/**
 * @brief Print frame buffer
*/
void led_matrix_print_buffer(led_matrix_handle_t led_matrix_handle);

#endif