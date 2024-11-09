#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "driver/i2c_master.h"
#include "esp_check.h"
#include "i2c_ds3231.h"

#define I2C_DS3231_ADR_BYTE_LEN 1
#define I2C_DS3231_BUFFER_BYTE_LEN 20
#define I2C_DS3231_DEV_ADDRESS 0x68
#define I2C_DS3231_SEC_ADDRESS 0x00
#define I2C_DS3231_MIN_ADDRESS 0x01
#define I2C_DS3231_HRS_ADDRESS 0x02
#define I2C_DS3231_DAY_ADDRESS 0x04
#define I2C_DS3231_MON_ADDRESS 0x05
#define I2C_DS3231_YRS_ADDRESS 0x06

static const char TAG[] = "i2c-ds3231";

//DS3231 time in BCD format
typedef struct {
    struct bcd_num *second;     //00-59
    struct bcd_num *minute;     //00-59
    struct bcd_num *hour;       //00-23
    struct bcd_num *day;        //01-31
    struct bcd_num *month;      //01-12
} i2c_ds3231_bcd_time_t;

//DS3231 time in register format
typedef struct {
    uint8_t second;     //00-59
    uint8_t minute;     //00-59
    uint8_t hour;       //00-23
    uint8_t day;        //01-31
    uint8_t month;      //01-12
} i2c_ds3231_reg_time_t;

//BCD (binary-coded decimal) number object
struct bcd_num{
    uint8_t ones;
    uint8_t tens;
    uint8_t hundreds;
};
typedef struct bcd_num bcd_num;

//Helper Functions

/**
 * @brief Generate a bcd_num object based on a decimal number
*/
bcd_num i2c_ds3231_make_bcd_num(int dec_num) 
{
    bcd_num out_bcd;
    
    out_bcd.ones = dec_num%10;
    out_bcd.tens = (dec_num/10)%10;
    out_bcd.hundreds = (dec_num/100)%10;
    
    return out_bcd;
}

/**
 * @brief Generate a decimal number based on a bcd_num object
*/
int i2c_ds3231_make_dec_num(bcd_num num)
{
    return num.ones + 10*num.tens + 100*num.hundreds;
}

/**
 * @brief Convert bcd time into DS3231 register format
 * 
 * @param[in] bcd_time Time in BCD format
 * @param[out] reg_time Time in DS3231 register format
*/
esp_err_t i2c_ds3231_bcd_to_reg(const i2c_ds3231_bcd_time_t *bcd_time, i2c_ds3231_reg_time_t *reg_time)
{
    reg_time->second = ((bcd_time->second->tens << 4) & 0b01110000) | (bcd_time->second->ones & 0b00001111);
    reg_time->minute = ((bcd_time->minute->tens << 4) & 0b01110000) | (bcd_time->minute->ones & 0b00001111);
    reg_time->hour = ((bcd_time->hour->tens << 4) & 0b00110000) | (bcd_time->hour->ones & 0b00001111);
    reg_time->day = ((bcd_time->day->tens << 4) & 0b00110000) | (bcd_time->day->ones & 0b00001111);
    reg_time->month = ((bcd_time->month->tens << 4) & 0b00010000) | (bcd_time->month->ones & 0b00001111);
    
    return ESP_OK;
}

/**
 * @brief Convert DS3231 register to bcd format
 * @param[in] bcd_time Time in DS3231 register format
 * @param[out] reg_time Time in BCD format
*/
esp_err_t i2c_ds3231_reg_to_bcd(const i2c_ds3231_reg_time_t *reg_time, i2c_ds3231_bcd_time_t *bcd_time)
{
    bcd_time->second->ones = (reg_time->second) & 0b00001111;
    bcd_time->second->tens = (reg_time->second >> 4) & 0b00000111;

    bcd_time->minute->ones = (reg_time->minute) & 0b00001111;
    bcd_time->minute->tens = (reg_time->minute >> 4) & 0b00000111;

    bcd_time->hour->ones = (reg_time->hour) & 0b00001111;
    bcd_time->hour->tens = (reg_time->hour >> 4) & 0b00000011;

    bcd_time->day->ones = (reg_time->day) & 0b00001111;
    bcd_time->day->tens = (reg_time->day >> 4) & 0b00000011;

    bcd_time->month->ones = (reg_time->month) & 0b00001111;
    bcd_time->month->tens = (reg_time->month >> 4) & 0b00000001;
    
    return ESP_OK;
}

/**
 * @brief Convert bcd time to decimal time
 * 
 * @param[in] bcd_time Time in bcd format
 * @param[out] dec_time Time in decimal format
 */
esp_err_t i2c_ds3231_bcd_to_dec(const i2c_ds3231_bcd_time_t *bcd_time, i2c_ds3231_dec_time_t *dec_time)
{
    dec_time->second =(uint8_t)i2c_ds3231_make_dec_num(*bcd_time->second);
    dec_time->minute =(uint8_t)i2c_ds3231_make_dec_num(*bcd_time->minute);
    dec_time->hour =(uint8_t)i2c_ds3231_make_dec_num(*bcd_time->hour);
    dec_time->day =(uint8_t)i2c_ds3231_make_dec_num(*bcd_time->day);
    dec_time->month =(uint8_t)i2c_ds3231_make_dec_num(*bcd_time->month);

    return ESP_OK;
}

/**
 * @brief Convert decimal time to bcd time
 * 
 * @param[in] dec_time Time in decimal format
 * @param[out] bcd_time Time in bcd format
 */
esp_err_t i2c_ds3231_dec_to_bcd(const i2c_ds3231_dec_time_t *dec_time, i2c_ds3231_bcd_time_t *bcd_time)
{
    *bcd_time->second = i2c_ds3231_make_bcd_num(dec_time->second);
    *bcd_time->minute = i2c_ds3231_make_bcd_num(dec_time->minute);
    *bcd_time->hour = i2c_ds3231_make_bcd_num(dec_time->hour);
    *bcd_time->day = i2c_ds3231_make_bcd_num(dec_time->day);
    *bcd_time->month = i2c_ds3231_make_bcd_num(dec_time->month);

    return ESP_OK;
}

/**
 * @brief Convert DS3231 decimal time to DS3231 register time
 * 
 * @param[in] time_dec Time in decimal format
 * @param[out] time_reg Time in DS3231 register format
*/
esp_err_t i2c_ds3231_dec_to_reg(const i2c_ds3231_dec_time_t *dec_time, i2c_ds3231_reg_time_t *reg_time)
{
    bcd_num bcd_sec = i2c_ds3231_make_bcd_num(0);
    bcd_num bcd_min = i2c_ds3231_make_bcd_num(0);
    bcd_num bcd_hrs = i2c_ds3231_make_bcd_num(0);
    bcd_num bcd_day = i2c_ds3231_make_bcd_num(0);
    bcd_num bcd_mon = i2c_ds3231_make_bcd_num(0);

    //Initialize bcd time struct
    i2c_ds3231_bcd_time_t bcd_time = {
        .second = &bcd_sec,
        .minute = &bcd_min,
        .hour = &bcd_hrs,
        .day = &bcd_day,
        .month = &bcd_mon
    };

    i2c_ds3231_dec_to_bcd(dec_time, &bcd_time);
    i2c_ds3231_bcd_to_reg(&bcd_time, reg_time);

    return ESP_OK;
}

/**
 * @brief Convert DS3231 register time to DS3231 decimal time
 * 
 * @param[in] time_reg Time in register format
 * @param[out] time_dec Time in decimal format
*/
esp_err_t i2c_ds3231_reg_to_dec(const i2c_ds3231_reg_time_t *reg_time, i2c_ds3231_dec_time_t *dec_time)
{
    bcd_num bcd_sec = i2c_ds3231_make_bcd_num(0);
    bcd_num bcd_min = i2c_ds3231_make_bcd_num(0);
    bcd_num bcd_hrs = i2c_ds3231_make_bcd_num(0);
    bcd_num bcd_day = i2c_ds3231_make_bcd_num(0);
    bcd_num bcd_mon = i2c_ds3231_make_bcd_num(0);

    //Initialize bcd time struct
    i2c_ds3231_bcd_time_t bcd_time = {
        .second = &bcd_sec,
        .minute = &bcd_min,
        .hour = &bcd_hrs,
        .day = &bcd_day,
        .month = &bcd_mon
    };

    i2c_ds3231_reg_to_bcd(reg_time, &bcd_time);
    i2c_ds3231_bcd_to_dec(&bcd_time, dec_time);

    return ESP_OK;
}

//Interface Functions

esp_err_t i2c_ds3231_init(i2c_master_bus_handle_t bus_handle, const i2c_ds3231_config_t *ds3231_config, i2c_ds3231_handle_t *ds3231_handle)
{   
    esp_err_t ret = ESP_OK;

    //Allocate space in memory for DS3231 device struct
    i2c_ds3231_handle_t out_handle;
    out_handle = (i2c_ds3231_handle_t)calloc(1, sizeof(i2c_ds3231_handle_t));
    ESP_GOTO_ON_FALSE(out_handle, ESP_ERR_NO_MEM, err, TAG, "no memory for i2c ds3231 device");

    i2c_device_config_t i2c_dev_conf = {
        .scl_speed_hz = ds3231_config->ds3231_device.scl_speed_hz,
        .device_address = ds3231_config->ds3231_device.device_address,
    };

    if (out_handle->i2c_dev == NULL) {
        ESP_GOTO_ON_ERROR(i2c_master_bus_add_device(bus_handle, &i2c_dev_conf, &(out_handle->i2c_dev)), err, TAG, "i2c new bus failed");
    }

    out_handle->buffer = (uint8_t*)calloc(1, I2C_DS3231_BUFFER_BYTE_LEN + I2C_DS3231_ADR_BYTE_LEN);
    ESP_GOTO_ON_FALSE(out_handle->buffer, ESP_ERR_NO_MEM, err, TAG, "no memory for i2c ds3231 write buffer");

    out_handle->hr_mode = ds3231_config->hr_mode;
    *ds3231_handle = out_handle;

    return ESP_OK;

err:
    if (out_handle && out_handle->i2c_dev) {
        i2c_master_bus_rm_device(out_handle->i2c_dev);
    }
    free(out_handle);
    return ret;
}

esp_err_t i2c_ds3231_set_time(i2c_ds3231_handle_t ds3231_handle, const i2c_ds3231_dec_time_t *dec_time)
{
    //Initialize register time struct 
    i2c_ds3231_reg_time_t reg_time = {
        .second = 0,
        .minute = 0,
        .hour = 0,
        .day = 0,
        .month = 0
    };

    i2c_ds3231_dec_to_reg(dec_time, &reg_time);

    reg_time.hour |= ds3231_handle->hr_mode; //Set 24/12 hour mode bit

    //Write to DS3231
    i2c_ds3231_write(ds3231_handle, I2C_DS3231_SEC_ADDRESS, &reg_time.second, 1);
    i2c_ds3231_write(ds3231_handle, I2C_DS3231_MIN_ADDRESS, &reg_time.minute, 1);
    i2c_ds3231_write(ds3231_handle, I2C_DS3231_HRS_ADDRESS, &reg_time.hour, 1);
    i2c_ds3231_write(ds3231_handle, I2C_DS3231_DAY_ADDRESS, &reg_time.day, 1);
    i2c_ds3231_write(ds3231_handle, I2C_DS3231_MON_ADDRESS, &reg_time.month, 1);

    return ESP_OK;
}

esp_err_t i2c_ds3231_get_time(i2c_ds3231_handle_t ds3231_handle, i2c_ds3231_dec_time_t *dec_time)
{
    //Initialize register time struct
    i2c_ds3231_reg_time_t reg_time = {
        .second = 0,
        .minute = 0,
        .hour = 0,
        .day = 0,
        .month = 0
    };

    //Load contents of DS3231 timekeeping registers
    i2c_ds3231_read(ds3231_handle, I2C_DS3231_SEC_ADDRESS, &reg_time.second, 1);
    i2c_ds3231_read(ds3231_handle, I2C_DS3231_MIN_ADDRESS, &reg_time.minute, 1);
    i2c_ds3231_read(ds3231_handle, I2C_DS3231_HRS_ADDRESS, &reg_time.hour, 1);
    i2c_ds3231_read(ds3231_handle, I2C_DS3231_DAY_ADDRESS, &reg_time.day, 1);
    i2c_ds3231_read(ds3231_handle, I2C_DS3231_MON_ADDRESS, &reg_time.month, 1);

    //Register -> Decimal
    i2c_ds3231_reg_to_dec(&reg_time, dec_time);

    return ESP_OK;
}

esp_err_t i2c_ds3231_write(i2c_ds3231_handle_t ds3231_handle, uint32_t address, const uint8_t *data, uint8_t size)
{
    ESP_RETURN_ON_FALSE(ds3231_handle, ESP_ERR_NO_MEM, TAG, "no mem for buffer");

    //Set first N bytes of buffer to address, where N = I2C_DS3231_ADR_BYTE_LEN
    for (int i=0 ; i<I2C_DS3231_ADR_BYTE_LEN ; i++) {
        ds3231_handle->buffer[i] = (address & (0xff << ((I2C_DS3231_ADR_BYTE_LEN - 1 - i) * 8))) >> ((I2C_DS3231_ADR_BYTE_LEN - 1 - i)*8);
    }
    
    //Copy data to buffer
    memcpy(ds3231_handle->buffer + I2C_DS3231_ADR_BYTE_LEN, data, size);

    return i2c_master_transmit(ds3231_handle->i2c_dev, ds3231_handle->buffer, I2C_DS3231_ADR_BYTE_LEN + size, -1);
}

esp_err_t i2c_ds3231_read(i2c_ds3231_handle_t ds3231_handle, uint32_t address, uint8_t *data, uint8_t size)
{
    ESP_RETURN_ON_FALSE(ds3231_handle, ESP_ERR_NO_MEM, TAG, "no mem for buffer");

    for (int i=0 ; i<I2C_DS3231_ADR_BYTE_LEN ; i++) {
        ds3231_handle->buffer[i] = (address & (0xff << ((I2C_DS3231_ADR_BYTE_LEN - 1 - i) * 8))) >> ((I2C_DS3231_ADR_BYTE_LEN - 1 - i)*8);
    }

    return i2c_master_transmit_receive(ds3231_handle->i2c_dev, ds3231_handle->buffer, I2C_DS3231_ADR_BYTE_LEN, data, size, -1);
}

void i2c_ds3231_print_dec_time(i2c_ds3231_dec_time_t *dec_time, char* str_buffer, bool incl_date)
{   
    if (incl_date){
        sprintf(str_buffer, "%02u/%02u %02u:%02u", dec_time->month, dec_time->day, dec_time->hour, dec_time->minute);
    }
    else {
        sprintf(str_buffer, "%02u:%02u", dec_time->hour, dec_time->minute);
    }
}