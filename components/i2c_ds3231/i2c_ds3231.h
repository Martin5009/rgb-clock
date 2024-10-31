#ifndef I2C_DS3231_H
#define I2C_DS3231_H

#include <stdint.h>
#include "driver/i2c_master.h"
#include "esp_err.h"

enum i2c_ds3231_hr_mode{I2C_DS3231_24HR_MODE = 0b00000000, I2C_DS3231_12HR_MODE = 0b01000000};
typedef enum i2c_ds3231_hr_mode i2c_ds3231_hr_mode;

//DS3231 time in decimal format
typedef struct {
    uint8_t second;     //00-59
    uint8_t minute;     //00-59
    uint8_t hour;       //00-23
    uint8_t day;        //01-31
    uint8_t month;      //01-12
} i2c_ds3231_dec_time_t;

//DS3231 Configuration
typedef struct {
    i2c_device_config_t ds3231_device;
    i2c_ds3231_hr_mode hr_mode;
} i2c_ds3231_config_t;

//DS3231 Device
struct i2c_ds3231_t{
    i2c_master_dev_handle_t i2c_dev;
    i2c_ds3231_hr_mode hr_mode;
    uint8_t *buffer;
};
typedef struct i2c_ds3231_t i2c_ds3231_t;

//DS3231 Device Handle
typedef struct i2c_ds3231_t *i2c_ds3231_handle_t;

/**
 * @brief Init DS3231 device
 * 
 * @param[in] bus_handle I2C master bus handle
 * @param[in] ds3231_config Configuration of DS3231
 * @param[out] ds3231_handle Handle of DS3231
 * @return ESP_OK: Init success. ESP_FAIL: Init failure.
*/
esp_err_t i2c_ds3231_init(i2c_master_bus_handle_t bus_handle, const i2c_ds3231_config_t *ds3231_config, i2c_ds3231_handle_t *ds3231_handle);

/**
 * @brief Set time on DS3231
 * 
 * @param[in] ds3231_handle DS3231 device handle
 * @param[in] dec_time Time to set
 * @return ESP_OK: Time successfully set. ESP_FAIL: Failed to set time.
*/
esp_err_t i2c_ds3231_set_time(i2c_ds3231_handle_t ds3231_handle, const i2c_ds3231_dec_time_t *dec_time);

/**
 * @brief Get time from DS3231
 * 
 * @param[in] ds3231_handle DS3231 device handle
 * @param[out] dec_time Time fetched from DS3231
 * @return ESP_OK: Time successfully fetched. ESP_FAIL: Failed to fetch time.
*/
esp_err_t i2c_ds3231_get_time(i2c_ds3231_handle_t ds3231_handle, i2c_ds3231_dec_time_t *dec_time);

/**
 * @brief Write data to DS3231
 * 
 * @param[in] ds3231_handle DS3231 device handle
 * @param[in] address Register address
 * @param[in] data Data to write
 * @param[in] size Size of written data in bytes
 * 
 * @return ESP_OK: Write success. ESP_FAIL: Write failure.
*/
esp_err_t i2c_ds3231_write(i2c_ds3231_handle_t ds3231_handle, uint32_t address, const uint8_t *data, uint8_t size);

/**
 * @brief Read data from DS3231
 * 
 * @param[in] ds3231_handle DS3231 device handle
 * @param[in] address Register address
 * @param[out] data Data to read
 * @param[in] size Size of read data in bytes
 * 
 * @return ESP_OK: Read success. ESP_FAIL: Read failure.
*/
esp_err_t i2c_ds3231_read(i2c_ds3231_handle_t ds3231_handle, uint32_t address, uint8_t *data, uint8_t size);

/**
 * @brief Print i2c_ds3231_dec_time_t struct
 * 
 * @param[in] dec_time Time to print
 * @param[out] str_buffer Buffer into which the string prints
 */
void i2c_ds3231_print_dec_time(i2c_ds3231_dec_time_t *dec_time, char* str_buffer, bool incl_date);

#endif