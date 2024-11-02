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

static const char TAG[] = "led_matrix";

static void led_matrix_write_screen(led_matrix_handle_t led_matrix_handle)
{
    //Top and bottom halves of the matrix are driven independently
    led_matrix_rgb_t led_top;
    led_matrix_rgb_t led_bottom;

    //LED matrix struct members
    led_matrix_rgb_t *buffer = led_matrix_handle->buffer_1;
    led_matrix_pwm_levels pwm_level = led_matrix_handle->pwm_level;
    uint8_t width = led_matrix_handle->width;
    uint8_t height = led_matrix_handle->height;
    uint8_t pwm_cnt = led_matrix_handle->pwm_cnt;
    led_matrix_io_t io_assign = *led_matrix_handle->io_assign;

    //matrix GPIO pins
    uint8_t r1;
    uint8_t g1;
    uint8_t b1;
    uint8_t r2;
    uint8_t g2;
    uint8_t b2;
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;

    //Loop variables
    uint8_t row;
    uint8_t col;

    //Normalization factor for converting 0 - 255
    //brightness scale to 0 - pwm_level brightness scale
    float norm = pwm_level/(pow(2, 8*sizeof(led_top.red)) - 1);

    //initialize GPIO output values
    gpio_set_level(io_assign.oe, 0);
    gpio_set_level(io_assign.clk, 0);
    gpio_set_level(io_assign.lat, 0);

    //write to matrix
    for (row = 0 ; row < height/2 ; row++)
    {   
        //create and write row data
        for (col = 0 ; col < width ; col++)
        {   
            led_top = buffer[row*width + col];
            led_bottom = buffer[(height/2 + row)*width + col];
            
            //determine state of R1 G1 B1 and R2 G2 B2 based on PWM counter
            r1 = (led_top.red * norm > pwm_cnt);
            g1 = (led_top.green * norm > pwm_cnt);
            b1 = (led_top.blue * norm > pwm_cnt);

            r2 = (led_bottom.red * norm > pwm_cnt);
            g2 = (led_bottom.green * norm > pwm_cnt);
            b2 = (led_bottom.blue * norm > pwm_cnt);

            gpio_set_level(io_assign.r1, r1);
            gpio_set_level(io_assign.g1, g1);
            gpio_set_level(io_assign.b1, b1);

            gpio_set_level(io_assign.r2, r2);
            gpio_set_level(io_assign.g2, g2);
            gpio_set_level(io_assign.b2, b2);

            //pulse CLK to write color bit
            gpio_set_level(io_assign.clk, 1);
            gpio_set_level(io_assign.clk, 0);
        }
        
        //set OE high to disable LEDs
        gpio_set_level(io_assign.oe, 1);

        //pulse LAT to load shift register contents into matrix
        gpio_set_level(io_assign.lat, 1);
        gpio_set_level(io_assign.lat, 0);

        //set ABCD to row number
        a = (row >> 3) & 0b1;   //bit 3 of row
        b = (row >> 2) & 0b1;   //bit 2 of row
        c = (row >> 1) & 0b1;   //bit 1 of row 
        d = row & 0b1;          //bit 0 of row 

        gpio_set_level(io_assign.a, a);
        gpio_set_level(io_assign.b, b);
        gpio_set_level(io_assign.c, c);
        gpio_set_level(io_assign.d, d);

        //set OE low to reenable LEDs
        gpio_set_level(io_assign.oe, 0);
    }

    //turn off final row (to avoid last row appearing brighter than others)
    for (col = 0 ; col < width ; col++)
    {
        led_top = buffer[(height/2-1)*width + col];
        led_bottom = buffer[(height-1)*width + col];

        gpio_set_level(io_assign.r1, 0);
        gpio_set_level(io_assign.g1, 0);
        gpio_set_level(io_assign.b1, 0);

        gpio_set_level(io_assign.r2, 0);
        gpio_set_level(io_assign.g2, 0);
        gpio_set_level(io_assign.b2, 0);

        //pulse CLK to write color bit
        gpio_set_level(io_assign.clk, 1);
        gpio_set_level(io_assign.clk, 0);
    }

    gpio_set_level(io_assign.oe, 1);

    gpio_set_level(io_assign.lat, 1);
    gpio_set_level(io_assign.lat, 0);

    gpio_set_level(io_assign.a, (((height/2-1) >> 3) & 0b1));
    gpio_set_level(io_assign.b, (((height/2-1) >> 2) & 0b1));
    gpio_set_level(io_assign.c, (((height/2-1) >> 1) & 0b1));
    gpio_set_level(io_assign.d, ((height/2-1) & 0b1));

    gpio_set_level(io_assign.oe, 0);
}


static void led_matrix_refresh_task(void *pvParameters)
{   
    const TickType_t xBlockTime = pdMS_TO_TICKS(LED_MATRIX_REFRESH_TIMEOUT_MS);
    uint32_t ulNotifiedValue;

    led_matrix_handle_t led_matrix_handle = (led_matrix_handle_t)pvParameters;

    //initialize pwm counter
    led_matrix_handle->pwm_cnt = 0;

    for (;;)
    {   
        //TODO: Re-enable timer interrupt when ready
        ulNotifiedValue = ulTaskNotifyTake(pdTRUE, xBlockTime);

        //if (ulNotifiedValue > 0)
        if (1)
        {
            //perform refresh
            led_matrix_write_screen(led_matrix_handle);

            //update pwm counter
            if(led_matrix_handle->pwm_cnt >= led_matrix_handle->pwm_level)
            {
                led_matrix_handle->pwm_cnt = 0;
            }
            else
            {
                led_matrix_handle->pwm_cnt++;
            }

        }
        else
        {
            //timeout error
            printf(TAG);
            printf(": Timed out");
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static bool IRAM_ATTR led_matrix_refresh_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
{   
    gptimer_stop(timer);
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    TaskHandle_t task_handle = (TaskHandle_t)user_data;

    vTaskNotifyGiveFromISR(task_handle, &xHigherPriorityTaskWoken);

    gptimer_start(timer);

    //force context switch upon exit
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken); 

    return (xHigherPriorityTaskWoken == true);
}

esp_err_t led_matrix_init(led_matrix_config_t *led_config, led_matrix_handle_t *led_matrix_handle) 
{   
    esp_err_t ret = ESP_OK;

    //Initialize led matrix struct
    led_matrix_handle_t out_handle;
    out_handle = (led_matrix_handle_t)calloc(1, sizeof(led_matrix_t));
    ESP_GOTO_ON_FALSE(out_handle, ESP_ERR_NO_MEM, err, TAG, "no memory for led matrix device");

    //Create refresh task
    xTaskCreate(led_matrix_refresh_task, "refresh_matrix", 8000, out_handle, led_config->refresh_priority, &led_config->refresh_task);
    ESP_GOTO_ON_FALSE(led_config->refresh_task, ESP_ERR_NO_MEM, err, TAG, "no memory for refresh task stack");
    vTaskSuspend(led_config->refresh_task);

    //Initialize refresh timer
    gptimer_config_t refresh_timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = led_config->refresh_rate * (led_config->height/2),
        .intr_priority = 0,
    };
    gptimer_new_timer(&refresh_timer_config, &led_config->refresh_timer);

    //gptimer alarm setup
    gptimer_alarm_config_t alarm_config = {
        .alarm_count = 1,
        .reload_count = 0,
        .flags.auto_reload_on_alarm = 1,
    };
    gptimer_set_alarm_action(led_config->refresh_timer, &alarm_config);

    //register timer ISR
    gptimer_event_callbacks_t event_cb = {
        .on_alarm = led_matrix_refresh_cb,
    };
    gptimer_register_event_callbacks(led_config->refresh_timer, &event_cb, led_config->refresh_task);

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

    //Create led matrix struct
    out_handle->refresh_rate = led_config->refresh_rate;
    out_handle->width = led_config->width;
    out_handle->height = led_config->height;
    out_handle->pwm_cnt = 0;
    out_handle->pwm_level = led_config->pwm_level;
    out_handle->refresh_task = led_config->refresh_task;
    out_handle->refresh_timer = led_config->refresh_timer;
    out_handle->io_assign = led_config->io_assign;

    //Initialize frame buffer 1
    out_handle->buffer_1 = (led_matrix_rgb_t*)calloc(led_config->height * led_config->width, sizeof(led_matrix_rgb_t));
    ESP_GOTO_ON_FALSE(out_handle->buffer_1, ESP_ERR_NO_MEM, err, TAG, "no memory for frame buffer 1");

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
    vTaskResume(led_matrix_handle->refresh_task);

    //TODO: Re-enable timer interrupt when ready
    gptimer_enable(led_matrix_handle->refresh_timer);
    gptimer_start(led_matrix_handle->refresh_timer);
    
    return ESP_OK;
}

esp_err_t led_matrix_stop_refresh(led_matrix_handle_t led_matrix_handle)
{
    if (led_matrix_handle == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    vTaskSuspend(led_matrix_handle->refresh_task);
    gptimer_stop(led_matrix_handle->refresh_timer);
    gptimer_disable(led_matrix_handle->refresh_timer);
    return ESP_OK;
}

void led_matrix_draw_char(led_matrix_handle_t led_matrix_handle, char ch, led_matrix_rgb_t color, uint8_t x, uint8_t y)
{   
    uint8_t width = led_matrix_handle->width;
    uint8_t buffer_offset = x + y*width;
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
    const uint8_t* ch_font = LED_MATRIX_FONT[ch_ind*LED_MATRIX_CHAR_WIDTH];

    //Send character to frame buffer
    uint8_t i, j;
    uint8_t ch_bit;

    for (i = 0 ; i < LED_MATRIX_CHAR_WIDTH ; i++)
    {
        for (j = 0 ; j < LED_MATRIX_CHAR_HEIGHT ; j++)
        {
            ch_bit = (ch_font[i] >> (LED_MATRIX_CHAR_HEIGHT - j - 1)) & 1;

            if (ch_bit) 
            {
                buffer[buffer_offset + i + j*width] = color;
            }
            else 
            {
                buffer[buffer_offset + i + j*width] = off_rgb;
            }
        }
    }
}

void led_matrix_set_buffer(led_matrix_handle_t led_matrix_handle, led_matrix_rgb_t *in_buffer)
{
    memcpy(led_matrix_handle->buffer_1, in_buffer, sizeof(*led_matrix_handle->buffer_1));
}

void led_matrix_clear_buffer(led_matrix_handle_t led_matrix_handle)
{   
    led_matrix_rgb_t *init_buffer = (led_matrix_rgb_t*)calloc(led_matrix_handle->height * led_matrix_handle->width, sizeof(led_matrix_rgb_t));
    memcpy(led_matrix_handle->buffer_1, init_buffer, led_matrix_handle->height * led_matrix_handle->width * sizeof(led_matrix_rgb_t));
    free(init_buffer);
}