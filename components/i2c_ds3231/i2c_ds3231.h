#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "driver/i2c_master.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_types.h"
#include "sdkconfig.h"

#define I2C_DS3231_ADR_BYTE_LEN 1
#define I2C_DS3231_BUFFER_BYTE_LEN 20
#define I2C_DS3231_DEV_ADDRESS 0x68
#define I2C_DS3231_SEC_ADDRESS 0x00
#define I2C_DS3231_MIN_ADDRESS 0x01
#define I2C_DS3231_HRS_ADDRESS 0x02
#define I2C_DS3231_DAY_ADDRESS 0x04
#define I2C_DS3231_MON_ADDRESS 0x05
#define I2C_DS3231_YRS_ADDRESS 0x06

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

//Configuration for DS3231
typedef struct {
    i2c_device_config_t ds3231_device;
    i2c_ds3231_hr_mode hr_mode;
} i2c_ds3231_config_t;

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
 * @param[in] time Time to set
 * @return ESP_OK: Time successfully set. ESP_FAIL: Failed to set time.
*/
esp_err_t i2c_ds3231_set_time(i2c_ds3231_handle_t ds3231_handle, const i2c_ds3231_dec_time_t *dec_time);

/**
 * @brief Get time from DS3231
 * 
 * @param[in] ds3231_handle DS3231 device handle
 * @param[out] time Time fetched from DS3231
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
 * @brief Convert DS3231 decimal time to DS3231 register time
 * 
 * @param[in] time_dec Time in decimal format
 * @param[out] time_reg Time in DS3231 register format
*/
esp_err_t i2c_ds3231_dec_to_reg(const i2c_ds3231_dec_time_t *dec_time, i2c_ds3231_reg_time_t *reg_time);

/**
 * @brief Convert DS3231 register time to DS3231 decimal time
 * 
 * @param[in] time_reg Time in register format
 * @param[out] time_dec Time in decimal format
*/
esp_err_t i2c_ds3231_reg_to_dec(const i2c_ds3231_reg_time_t *reg_time, i2c_ds3231_dec_time_t *dec_time);

/**
 * @brief Convert bcd time into DS3231 register format
 * 
 * @param[in] bcd_time Time in BCD format
 * @param[out] reg_time Time in DS3231 register format
*/
esp_err_t i2c_ds3231_bcd_to_reg(const i2c_ds3231_bcd_time_t *bcd_time, i2c_ds3231_reg_time_t *reg_time);

/**
 * @brief Convert DS3231 register to bcd format
 * @param[in] bcd_time Time in DS3231 register format
 * @param[out] reg_time Time in BCD format
*/
esp_err_t i2c_ds3231_reg_to_bcd(const i2c_ds3231_reg_time_t *reg_time, i2c_ds3231_bcd_time_t *bcd_time);

/**
 * @brief Convert bcd time to decimal time
 * 
 * @param[in] bcd_time Time in bcd format
 * @param[out] dec_time Time in decimal format
 */
esp_err_t i2c_ds3231_bcd_to_dec(const i2c_ds3231_bcd_time_t *bcd_time, i2c_ds3231_dec_time_t *dec_time);

/**
 * @brief Convert decimal time to bcd time
 * 
 * @param[in] dec_time Time in decimal format
 * @param[out] bcd_time Time in bcd format
 */
esp_err_t i2c_ds3231_dec_to_bcd(const i2c_ds3231_dec_time_t *dec_time, i2c_ds3231_bcd_time_t *bcd_time);

/**
 * @brief Generate a bcd_num object based on a decimal number
*/
bcd_num i2c_ds3231_make_bcd_num(int dec_num);

/**
 * @brief Generate a decimal number based on a bcd_num object
*/
int i2c_ds3231_make_dec_num(bcd_num num);

/**
 * @brief Print i2c_ds3231_dec_time_t struct
 */
void i2c_ds3231_print_dec_time(i2c_ds3231_dec_time_t *dec_time);