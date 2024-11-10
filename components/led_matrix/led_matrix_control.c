#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_check.h"
#include "esp_system.h"
#include "driver/gptimer.h"
#include "driver/gpio.h"
#include "led_matrix_control.h"

#define LED_MATRIX_TIMER_FREQ 1000000

static const char TAG[] = "led_matrix";

//ISR-exclusive variables
static volatile uint8_t row = 0;
static volatile uint8_t col = 0;

static volatile led_matrix_rgb_t led_top;
static volatile led_matrix_rgb_t led_bottom;

static volatile led_matrix_handle_t led_matrix_handle_isr;
static volatile led_matrix_rgb_t* buffer_isr;
static volatile led_matrix_pwm_levels pwm_level;
static volatile uint8_t pwm_cnt = 0;
static volatile uint8_t width;
static volatile uint8_t height;
static volatile led_matrix_io_t io;

static bool IRAM_ATTR led_matrix_refresh_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
{
    //gptimer_stop(timer);

    led_matrix_handle_isr = (led_matrix_handle_t)user_data;

    //LED matrix struct members
    buffer_isr = led_matrix_handle_isr->buffer_1;
    pwm_level = led_matrix_handle_isr->pwm_level;
    width = led_matrix_handle_isr->width;
    height = led_matrix_handle_isr->height;
    io = *(led_matrix_handle_isr->io_assign);

    //initialize GPIO output values
    gpio_set_level(io.oe, 0);
    gpio_set_level(io.clk, 0);
    gpio_set_level(io.lat, 0);

    //write to matrix
    led_top = buffer_isr[row*width + col];
    led_bottom = buffer_isr[(height/2 + row)*width + col];
    
    //determine state of R1 G1 B1 and R2 G2 B2 based on PWM counter
    //pwm_level/255 is the normalization factor
    gpio_set_level(io.r1, (led_top.red * pwm_level/255 > pwm_cnt));
    gpio_set_level(io.g1, (led_top.green * pwm_level/255 > pwm_cnt));
    gpio_set_level(io.b1, (led_top.blue * pwm_level/255 > pwm_cnt));

    gpio_set_level(io.r2, (led_bottom.red * pwm_level/255 > pwm_cnt));
    gpio_set_level(io.g2, (led_bottom.green * pwm_level/255 > pwm_cnt));
    gpio_set_level(io.b2, (led_bottom.blue * pwm_level/255 > pwm_cnt));

    //pulse CLK to write color bit
    gpio_set_level(io.clk, 1);
    gpio_set_level(io.clk, 0);

    //update pwm, row, col counter
    col++;
    
    if((row >= height/2) & (col >= width))
    {
        row = 0;
        col = 0;

        if(pwm_cnt >= pwm_level)
        {
            pwm_cnt = 0;
        }
        else
        {
            pwm_cnt++;
        }
        }
    else if (col >= width)
    {
        //set OE high to disable LEDs
        gpio_set_level(io.oe, 1);

        //pulse LAT to load shift register contents into matrix
        gpio_set_level(io.lat, 1);
        gpio_set_level(io.lat, 0);

        //set ABCD to row number
        gpio_set_level(io.a, (row >> 0) & 0b1);
        gpio_set_level(io.b, (row >> 1) & 0b1);
        gpio_set_level(io.c, (row >> 2) & 0b1);
        gpio_set_level(io.d, (row >> 3) & 0b1);

        //set OE low to reenable LEDs
        gpio_set_level(io.oe, 0);

        col = 0;
        row++;
    }

    //gptimer_start(timer);

    return false;
}

esp_err_t led_matrix_init(led_matrix_config_t *led_config, led_matrix_handle_t *led_matrix_handle) 
{   
    esp_err_t ret = ESP_OK;

    //Initialize led matrix struct
    led_matrix_handle_t out_handle;
    out_handle = (led_matrix_handle_t)calloc(1, sizeof(led_matrix_t));
    ESP_GOTO_ON_FALSE(out_handle, ESP_ERR_NO_MEM, err, TAG, "no memory for led matrix device");

    //Initialize refresh timer
    gptimer_config_t refresh_timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = LED_MATRIX_TIMER_FREQ, //1MHz timer
        .intr_priority = 0,
    };
    gptimer_new_timer(&refresh_timer_config, &led_config->refresh_timer);

    //gptimer alarm setup
    uint32_t alarm_count = (uint32_t)log2f(LED_MATRIX_TIMER_FREQ/(led_config->refresh_rate * (led_config->height)/2));

    gptimer_alarm_config_t alarm_config = {
        .alarm_count = alarm_count,
        .reload_count = 0,
        .flags.auto_reload_on_alarm = 1,
    };
    gptimer_set_alarm_action(led_config->refresh_timer, &alarm_config);

    //register timer ISR
    gptimer_event_callbacks_t event_cb = {
        .on_alarm = led_matrix_refresh_cb,
    };
    gptimer_register_event_callbacks(led_config->refresh_timer, &event_cb, out_handle);

    //Initialize GPIO pins
    uint64_t gpio_bit_mask = (
        (1ULL<<led_config->io_assign->a)|
        (1ULL<<led_config->io_assign->b)|
        (1ULL<<led_config->io_assign->c)|
        (1ULL<<led_config->io_assign->d)|
        (1ULL<<led_config->io_assign->r1)|
        (1ULL<<led_config->io_assign->r2)|
        (1ULL<<led_config->io_assign->g1)|
        (1ULL<<led_config->io_assign->g2)|
        (1ULL<<led_config->io_assign->b1)|
        (1ULL<<led_config->io_assign->b2)|
        (1ULL<<led_config->io_assign->oe)|
        (1ULL<<led_config->io_assign->clk)|
        (1ULL<<led_config->io_assign->lat)
    );

    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = gpio_bit_mask,
        .pull_down_en = 0,
        .pull_up_en = 0,
    };
    gpio_config(&io_conf);

    //Initialize frame buffer 1
    out_handle->buffer_1 = (led_matrix_rgb_t*)calloc(led_config->height * led_config->width, sizeof(led_matrix_rgb_t));
    ESP_GOTO_ON_FALSE(out_handle->buffer_1, ESP_ERR_NO_MEM, err, TAG, "no memory for frame buffer 1");

    //Create led matrix struct
    out_handle->refresh_rate = led_config->refresh_rate;
    out_handle->width = led_config->width;
    out_handle->height = led_config->height;
    out_handle->pwm_level = led_config->pwm_level;
    out_handle->refresh_timer = led_config->refresh_timer;
    out_handle->io_assign = led_config->io_assign;

    *led_matrix_handle = out_handle;

    return ESP_OK;
err:
    free(out_handle->buffer_1);
    gptimer_disable(led_config->refresh_timer);
    gptimer_del_timer(led_config->refresh_timer);
    free(out_handle);
    return ret;
}

esp_err_t led_matrix_start_refresh(led_matrix_handle_t led_matrix_handle)
{   
    if (led_matrix_handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    gptimer_enable(led_matrix_handle->refresh_timer);
    gptimer_start(led_matrix_handle->refresh_timer);
    
    return ESP_OK;
}

esp_err_t led_matrix_stop_refresh(led_matrix_handle_t led_matrix_handle)
{
    if (led_matrix_handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    gptimer_stop(led_matrix_handle->refresh_timer);
    gptimer_disable(led_matrix_handle->refresh_timer);
    return ESP_OK;
}

void led_matrix_draw_char(led_matrix_handle_t led_matrix_handle, char ch, led_matrix_rgb_t color, uint8_t x, uint8_t y)
{   
    uint8_t width = led_matrix_handle->width;
    uint16_t xy_offset = x + y*width;
    led_matrix_rgb_t *buffer = led_matrix_handle->buffer_1;
    led_matrix_rgb_t off_rgb = {
        .red = 0,
        .blue = 0,
        .green = 0,
    };

    //Convert char to font array index
    ch = ch & 0x7F;
    if (ch < ' ') 
    {
        ch = 0;
    }
    else 
    {
        ch -= ' ';
    }
    uint8_t ch_ind = (uint8_t)ch;
    
    //Get character from font array
    const unsigned char* ch_font = &LED_MATRIX_FONT[ch_ind][0];

    //Send character to frame buffer
    uint8_t i, j;
    uint8_t ch_bit;

    for (i = 0 ; i < LED_MATRIX_CHAR_WIDTH ; i++)
    {
        for (j = 0 ; j < LED_MATRIX_CHAR_HEIGHT ; j++)
        {
            ch_bit = (ch_font[i] >> j) & 1;
            if (ch_bit) 
            {   
                buffer[xy_offset + i + j*width] = color;
            }
            else 
            {
                buffer[xy_offset + i + j*width] = off_rgb;
            }
        }
    }
}

void led_matrix_draw_str(led_matrix_handle_t led_matrix_handle, char* str, uint8_t size, led_matrix_rgb_t color, uint8_t x, uint8_t y)
{   
    uint8_t i;
    uint8_t x_ch = x;
    uint8_t y_ch = y;

    for (i = 0 ; i < size ; i++)
    {   
        led_matrix_draw_char(led_matrix_handle, str[i], color, x_ch, y_ch);
        printf("Printing %c at (%d, %d)\n", str[i], x_ch, y_ch);

        x_ch += LED_MATRIX_CHAR_WIDTH;
        //Check for text-wrapping condition
        if (x_ch + LED_MATRIX_CHAR_WIDTH >= led_matrix_handle->width)
        {
            x_ch = 0;
            y_ch += LED_MATRIX_CHAR_HEIGHT;
        }
        //Check for overflow condition
        if (y_ch + LED_MATRIX_CHAR_HEIGHT >= led_matrix_handle->height) break;
    }
}

void led_matrix_set_buffer(led_matrix_handle_t led_matrix_handle, led_matrix_rgb_t *in_buffer)
{
    memcpy(led_matrix_handle->buffer_1, in_buffer, led_matrix_handle->width*led_matrix_handle->height*sizeof(led_matrix_rgb_t));
}

void led_matrix_clear_buffer(led_matrix_handle_t led_matrix_handle)
{   
    led_matrix_rgb_t *init_buffer = (led_matrix_rgb_t*)calloc(led_matrix_handle->height*led_matrix_handle->width, sizeof(led_matrix_rgb_t));
    memcpy(led_matrix_handle->buffer_1, init_buffer, led_matrix_handle->height*led_matrix_handle->width*sizeof(led_matrix_rgb_t));
    free(init_buffer);
}

void led_matrix_print_buffer(led_matrix_handle_t led_matrix_handle)
{
    led_matrix_rgb_t* buffer = led_matrix_handle->buffer_1;
    uint8_t height = led_matrix_handle->height;
    uint8_t width = led_matrix_handle->width;

    char on_char = '0';
    char off_char = '.';

    char* str = (char*)malloc(width);

    led_matrix_rgb_t led;

    uint8_t row, col;

    printf("Start\n");
    for (row = 0 ; row < height ; row++)
    {
        for (col = 0 ; col < width ; col++)
        {
            led = buffer[col + row*width];
            if((uint16_t)(led.red + led.green + led.blue) > 0)
            {
                str[col] = on_char;
            }
            else
            {
                str[col] = off_char;
            }
        }
        printf("%.*s\n", width, str);
    }
    printf("End\n");

    free(str);
}