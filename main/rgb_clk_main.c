#include <stdio.h>
#include <string.h>
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
#include "led_matrix_control.h"
#include "esp_console.h"

#define PROMPT_STR CONFIG_IDF_TARGET

#define I2C_MASTER_FREQUENCY 100000
#define TIME_REFRESH_PERIOD_MS 250

#define DS3231_GPIO_SCL GPIO_NUM_1
#define DS3231_GPIO_SDA GPIO_NUM_2

#define LED_MATRIX_WIDTH 32
#define LED_MATRIX_HEIGHT 32
#define LED_MATRIX_REFRESH_RATE 200
#define LED_MATRIX_REFRESH_PRIORITY 5
#define LED_MATRIX_GPIO_A GPIO_NUM_18
#define LED_MATRIX_GPIO_B GPIO_NUM_5
#define LED_MATRIX_GPIO_C GPIO_NUM_17
#define LED_MATRIX_GPIO_D GPIO_NUM_6
#define LED_MATRIX_GPIO_OE GPIO_NUM_15
#define LED_MATRIX_GPIO_CLK GPIO_NUM_16
#define LED_MATRIX_GPIO_LAT GPIO_NUM_7
#define LED_MATRIX_GPIO_R1 GPIO_NUM_9
#define LED_MATRIX_GPIO_R2 GPIO_NUM_3
#define LED_MATRIX_GPIO_G1 GPIO_NUM_10
#define LED_MATRIX_GPIO_G2 GPIO_NUM_11
#define LED_MATRIX_GPIO_B1 GPIO_NUM_46
#define LED_MATRIX_GPIO_B2 GPIO_NUM_8

#define TIME_DISPLAY_COLOR_R 255
#define TIME_DISPLAY_COLOR_G 255
#define TIME_DISPLAY_COLOR_B 255

enum led_matrix_mode{
    LED_MATRIX_MODE_SLEEP = 1,
    LED_MATRIX_MODE_BLINK = 2,
    LED_MATRIX_MODE_CLOCK = 3,
    LED_MATRIX_MODE_BOARD = 4};
typedef enum led_matrix_mode led_matrix_mode;

//Global Device Handles
i2c_ds3231_handle_t ds3231_handle = NULL;
TaskHandle_t led_matrix_main_handle = NULL;

//Global System Time Mailbox
QueueHandle_t time_mailbox = NULL;

/*--------------------------------------*/
// Tasks
/*--------------------------------------*/

void fetch_time_task(void *pvParameters)
{   i2c_ds3231_handle_t ds3231_handle = (i2c_ds3231_handle_t)pvParameters;


    //Initialize system time mailbox
    time_mailbox = xQueueCreate(1, sizeof(i2c_ds3231_dec_time_t));

    //Initialize master i2c bus
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = -1,
        .scl_io_num = DS3231_GPIO_SCL,
        .sda_io_num = DS3231_GPIO_SDA,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus_handle = NULL;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

    //Initialize DS3231
    i2c_ds3231_config_t i2c_ds3231_config = {
        .ds3231_device.scl_speed_hz = I2C_MASTER_FREQUENCY,
        .ds3231_device.device_address = 0b1101000,
        .hr_mode = I2C_DS3231_24HR_MODE
    };

    ESP_ERROR_CHECK(i2c_ds3231_init(bus_handle, &i2c_ds3231_config, &ds3231_handle));

    i2c_ds3231_dec_time_t time_buffer = {
        .second = 0,
        .minute = 0,
        .hour = 0,
        .day = 0,
        .month = 0,
    };

    for (;;)
    {   
        i2c_ds3231_get_time(ds3231_handle, &time_buffer);

        xQueueOverwrite(time_mailbox, &time_buffer);

        vTaskDelay(pdMS_TO_TICKS(TIME_REFRESH_PERIOD_MS));
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

void led_matrix_sleep_task(void *pvParameters)
{

}

void led_matrix_blink_task(void *pvParameters)
{   
    led_matrix_handle_t led_matrix_handle = (led_matrix_handle_t)pvParameters;
    TickType_t delay = pdMS_TO_TICKS(1000);

    led_matrix_rgb_t red_rgb = {
            .red = 255,
            .green = 127,
            .blue = 127,
        };
    
    led_matrix_rgb_t green_rgb = {
            .red = 127,
            .green = 255,
            .blue = 127,
        };
    
    led_matrix_rgb_t blue_rgb = {
            .red = 127,
            .green = 127,
            .blue = 255,
        };

    for (;;)
    {   
        //Clear screen
        led_matrix_clear_buffer(led_matrix_handle);
        vTaskDelay(delay);

        //Draw the character 'a' at position (0, 0)
        led_matrix_draw_char(led_matrix_handle, 'a', red_rgb, 0, 0);
        vTaskDelay(delay);

        //Draw the character 'b' at position (5, 0)
        led_matrix_draw_char(led_matrix_handle, 'b', green_rgb, 5, 0);
        vTaskDelay(delay);

        //Draw the character 'c' at position (10, 0)
        led_matrix_draw_char(led_matrix_handle, 'c', blue_rgb, 10, 0);
        vTaskDelay(delay);
    }
}

void led_matrix_clock_task(void *pvParameters)
{   
    led_matrix_handle_t led_matrix_handle = (led_matrix_handle_t)pvParameters;

    i2c_ds3231_dec_time_t time_buffer = {
        .second = 0,
        .minute = 0,
        .hour = 0,
        .day = 0,
        .month = 0
    };

    led_matrix_rgb_t time_color = {
        .red = TIME_DISPLAY_COLOR_R,
        .green = TIME_DISPLAY_COLOR_G,
        .blue = TIME_DISPLAY_COLOR_B,
    };

    char time_str[8];

    uint8_t i = 0;

    for (;;)
    { 
        //Fetch current time
        xQueuePeek(time_mailbox, &time_buffer, 0);

        //Convert time to string
        i2c_ds3231_print_dec_time(&time_buffer, time_str, false);
        
        //Draw time string one char at a time
        led_matrix_clear_buffer(led_matrix_handle);
        for (i = 0 ; i < sizeof(time_str) ; i++)
        {
            led_matrix_draw_char(led_matrix_handle, time_str[i], time_color, i*LED_MATRIX_CHAR_WIDTH, 0);
        }

        vTaskDelay(pdMS_TO_TICKS(TIME_REFRESH_PERIOD_MS));
    }
}

void led_matrix_board_task(void *pvParameters)
{

}

void led_matrix_main_task(void *pvParameters)
{
    uint32_t stack_depth = 5000;
    uint32_t priority = 2;
    led_matrix_handle_t led_matrix_handle = NULL;

    uint32_t ulNotifiedValue;

    led_matrix_mode current_mode;

    //Initialize LED matrix
    TaskHandle_t led_matrix_refresh_task = NULL;
    gptimer_handle_t led_matrix_timer = NULL;
    led_matrix_io_t led_matrix_io_assign = {
        .a = LED_MATRIX_GPIO_A,
        .b = LED_MATRIX_GPIO_B,
        .c = LED_MATRIX_GPIO_C,
        .d = LED_MATRIX_GPIO_D,
        .oe = LED_MATRIX_GPIO_OE,
        .clk = LED_MATRIX_GPIO_CLK,
        .lat = LED_MATRIX_GPIO_LAT,
        .r1 = LED_MATRIX_GPIO_R1,
        .r2 = LED_MATRIX_GPIO_R2,
        .g1 = LED_MATRIX_GPIO_G1,
        .g2 = LED_MATRIX_GPIO_G2,
        .b1 = LED_MATRIX_GPIO_B1,
        .b2 = LED_MATRIX_GPIO_B2,
    };
    
    led_matrix_config_t led_matrix_config = {
        .width = LED_MATRIX_WIDTH,
        .height = LED_MATRIX_HEIGHT,
        .pwm_level = LED_MATRIX_PWM_16,
        .refresh_rate = LED_MATRIX_REFRESH_RATE,
        .refresh_task = led_matrix_refresh_task,
        .refresh_priority = LED_MATRIX_REFRESH_PRIORITY,
        .refresh_timer = led_matrix_timer,
        .io_assign = &led_matrix_io_assign,
    };

    led_matrix_init(&led_matrix_config, &led_matrix_handle);

    led_matrix_clear_buffer(led_matrix_handle);
    led_matrix_start_refresh(led_matrix_handle);

    //Create Mode Tasks
    TaskHandle_t sleep_matrix_handle = NULL;
    xTaskCreate(led_matrix_sleep_task, "sleep_matrix", stack_depth, led_matrix_handle, priority, &sleep_matrix_handle);
    vTaskSuspend(sleep_matrix_handle);

    TaskHandle_t blink_matrix_handle = NULL;
    xTaskCreate(led_matrix_blink_task, "blink_matrix", stack_depth, led_matrix_handle, priority, &blink_matrix_handle);
    vTaskSuspend(blink_matrix_handle);

    TaskHandle_t clock_matrix_handle = NULL;
    xTaskCreate(led_matrix_clock_task, "clock_matrix", stack_depth, led_matrix_handle, priority, &clock_matrix_handle);
    vTaskSuspend(clock_matrix_handle);

    TaskHandle_t board_matrix_handle = NULL;
    xTaskCreate(led_matrix_board_task, "board_matrix", stack_depth, led_matrix_handle, priority, &board_matrix_handle);
    vTaskSuspend(board_matrix_handle);

    for (;;)
    {
        ulNotifiedValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if (ulNotifiedValue > 0) {
            switch(ulNotifiedValue) {
                case LED_MATRIX_MODE_SLEEP: 
                    vTaskResume(sleep_matrix_handle);
                    vTaskSuspend(blink_matrix_handle);
                    vTaskSuspend(clock_matrix_handle);
                    vTaskSuspend(board_matrix_handle);
                    break;
                case LED_MATRIX_MODE_BLINK:
                    vTaskSuspend(sleep_matrix_handle);
                    vTaskResume(blink_matrix_handle);
                    vTaskSuspend(clock_matrix_handle);
                    vTaskSuspend(board_matrix_handle);
                    break;
                case LED_MATRIX_MODE_CLOCK:
                    vTaskSuspend(sleep_matrix_handle);
                    vTaskSuspend(blink_matrix_handle);
                    vTaskResume(clock_matrix_handle);
                    vTaskSuspend(board_matrix_handle);
                    break;
                case LED_MATRIX_MODE_BOARD:
                    vTaskSuspend(sleep_matrix_handle);
                    vTaskSuspend(blink_matrix_handle);
                    vTaskSuspend(clock_matrix_handle);
                    vTaskResume(board_matrix_handle);
                    break;
                default:
                    vTaskSuspend(sleep_matrix_handle);
                    vTaskSuspend(blink_matrix_handle);
                    vTaskSuspend(clock_matrix_handle);
                    vTaskSuspend(board_matrix_handle);
                    break;
            }
        }
    }
}

/*--------------------------------------*/
// Console Commands
/*--------------------------------------*/

int console_time_cmd_func(int argc, char **argv)
{
    char *sub_cmd = argv[1];

    i2c_ds3231_dec_time_t time_buffer = {
        .second = 0,
        .minute = 0,
        .hour = 0,
        .day = 0,
        .month = 0,
    };

    char str_buffer[14];

    if (!strcmp(sub_cmd, "set"))
    {   
        //Error Check: Correct number of arguments
        if (argc != 7) {
            printf("ERROR: number of arguments for sub-command SET (%d) does not match expected (5)\n", argc - 2);
             return 1;
        }

        //Error Check: Arguments in range
        if ((atoi(argv[2]) > 12) | (atoi(argv[2]) < 1)) {
            printf("ERROR: month value outside valid range (1-12)\n");
            return 1;
        }
        if ((atoi(argv[3]) > 31) | (atoi(argv[3]) < 1)) {
            printf("ERROR: day value outside valid range (1-31)\n");
            return 1;
        }
        if ((atoi(argv[4]) > 23) | (atoi(argv[4]) < 0)) {
            printf("ERROR: hour value outside valid range (0-23)\n");
            return 1;
        }
        if ((atoi(argv[5]) > 59) | (atoi(argv[5]) < 0)) {
            printf("ERROR: minute value outside valid range (0-59)\n");
            return 1;
        }
        if ((atoi(argv[6]) > 59) | (atoi(argv[6]) < 0)) {
            printf("ERROR: second value outside valid range (0-59)\n");
            return 1;
        }

        time_buffer.month = atoi(argv[2]);
        time_buffer.day = atoi(argv[3]);
        time_buffer.hour = atoi(argv[4]);
        time_buffer.minute = atoi(argv[5]);
        time_buffer.second = atoi(argv[6]);

        i2c_ds3231_set_time(ds3231_handle, &time_buffer);

        i2c_ds3231_print_dec_time(&time_buffer, str_buffer, true);
        printf("time: new time is [");
        printf(str_buffer);
        printf("]\n");

    }
    else if (!strcmp(sub_cmd, "get"))
    {
        if (argc != 2) {
            printf("ERROR: number of arguments for sub-command GET (%d) does not match expected (0)\n", argc - 2);
            return 1;
        }

        xQueuePeek(time_mailbox, &time_buffer, 0);

        i2c_ds3231_print_dec_time(&time_buffer, str_buffer, true);
        printf("time: current time is [");
        printf(str_buffer);
        printf("]\n");
    }
    else {
        printf("time: unrecognized command\n");
        return 1;
    }

    return 0;
}

int console_matrix_cmd_func(int argc, char **argv)
{
    char *sub_cmd = argv[1];

    if (!strcmp(sub_cmd, "mode"))
    {
        if (argc != 3) {
            printf("ERROR: number of arguments for sub-command MODE (%d) does not match expected (1)\n", argc - 2);
            return 1;
        }

        char *mode = argv[2];

        if (!strcmp(mode, "sleep"))
        {
            led_matrix_mode_sel(LED_MATRIX_MODE_SLEEP, led_matrix_main_handle);
        }
        else if (!strcmp(mode, "blink"))
        {
            led_matrix_mode_sel(LED_MATRIX_MODE_BLINK, led_matrix_main_handle);
        }
        else if (!strcmp(mode, "clock"))
        {
            led_matrix_mode_sel(LED_MATRIX_MODE_CLOCK, led_matrix_main_handle);
        }
        else if (!strcmp(mode, "board"))
        {
            led_matrix_mode_sel(LED_MATRIX_MODE_BOARD, led_matrix_main_handle);
        }
        else
        {
            printf("matrix: unrecognized mode");
            return 1;
        }
    }
    else
    {
        printf("matrix: unrecognized command\n");
        return 1;
    }

    return 0;
}

/*--------------------------------------*/
// Functions
/*--------------------------------------*/

void led_matrix_mode_sel(led_matrix_mode mode, TaskHandle_t led_matrix_main_handle)
{
    xTaskNotify(led_matrix_main_handle, mode, eSetValueWithOverwrite);
}

/*--------------------------------------*/
// Entry Point
/*--------------------------------------*/

void app_main(void)
{
    //Start fetch time task for DS3231
    TaskHandle_t fetch_time_handle = NULL;
    xTaskCreate(fetch_time_task, "fetch_time", 2000, ds3231_handle, 2, &fetch_time_handle);

    //Initialize LED matrix with a simple "blink" task
    xTaskCreate(led_matrix_main_task, "mode_sel_matrix", 5000, NULL, 3, &led_matrix_main_handle);
    led_matrix_mode_sel(LED_MATRIX_MODE_BLINK, led_matrix_main_handle);

    //Create console
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt = PROMPT_STR ">";
    repl_config.max_cmdline_length = 0;

    esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_console_new_repl_uart(&hw_config, &repl_config, &repl));

    //Register console commands
    const char *console_time_cmd_hint = "\n    usage:"
                                        "\n        time <sub-command> [<args>]"
                                        "\n"
                                        "\n    sub-commands:"
                                        "\n        set <month> <day> <hour> <minute> <second>"
                                        "\n        get <N/A>"
                                        "\n";
    const char *console_time_cmd_help = "Fetch or set the time on the DS3231 RTC over I2C interface.";

    esp_console_cmd_t console_time_cmd = {
        .command = "time",
        .help = console_time_cmd_help,
        .hint = console_time_cmd_hint,
        .func = console_time_cmd_func,
        .argtable = NULL,
    };
    esp_console_cmd_register(&console_time_cmd);

    const char *console_matrix_cmd_hint = "\n   usage:"
                                          "\n       matrix <sum-command> [<args>]"
                                          "\n"
                                          "\n   sub-commands:"
                                          "\n       mode <mode>"
                                          "\n";
    const char *console_matrix_cmd_help = "Interactively change LED matrix operating mode";

    esp_console_cmd_t console_matrix_cmd = {
        .command = "matrix",
        .help = console_matrix_cmd_help,
        .hint = console_matrix_cmd_hint,
        .func = console_matrix_cmd_func,
        .argtable = NULL,
    };
    esp_console_cmd_register(&console_matrix_cmd);

    esp_console_register_help_command();

    //Start console
    ESP_ERROR_CHECK(esp_console_start_repl(repl));
}