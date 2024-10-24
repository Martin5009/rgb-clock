#include "led_matrix.h"

static const char TAG[] = "led_matrix";

esp_err_t led_matrix_init(led_matrix_config_t* led_config, led_matrix_handle_t led_matrix_handle) 
{   
    esp_err_t ret = ESP_OK;

    //Initialize led matrix struct
    led_matrix_handle_t out_handle;
    out_handle = (led_matrix_handle_t)calloc(1, sizeof(led_matrix_handle_t));
    ESP_GOTO_ON_FALSE(out_handle, ESP_ERR_NO_MEM, err, TAG, "no memory for led matrix device");

    //Initialize refresh timer
    gptimer_config_t refresh_timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = led_config->refresh_rate * (led_config->height/2) * LED_MATRIX_PWM_1,
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

    //Create led matrix struct
    out_handle->refresh_rate = led_config->refresh_rate;
    out_handle->width = led_config->width;
    out_handle->height = led_config->height;
    out_handle->refresh_timer = led_config->refresh_timer;
    out_handle->io_assign = led_config->io_assign;

    //Initialize frame buffer 1
    out_handle->buffer_1 = calloc(led_config->height * led_config->width, sizeof(led_matrix_rgb_t));
    ESP_GOTO_ON_FALSE(out_handle->buffer_1, ESP_ERR_NO_MEM, err, TAG, "no memory for frame buffer 1");

    return ESP_OK;

err:
    free(out_handle->buffer_1);
    gptimer_disable(led_config->refresh_timer);
    gptimer_del_timer(led_config->refresh_timer);
    free(out_handle);
    return ret;
}

esp_err_t led_matrix_rm(led_matrix_handle_t led_matrix_handle)
{
    return ESP_OK;
}

esp_err_t led_matrix_start_refresh(led_matrix_handle_t led_matrix_handle)
{
    return ESP_OK;
}

esp_err_t led_matrix_stop_refresh(led_matrix_handle_t led_matrix_handle)
{
    return ESP_OK;
}

static bool IRAM_ATTR led_matrix_refresh_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
{
    return true;
}