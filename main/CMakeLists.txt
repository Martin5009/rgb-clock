idf_component_register(SRCS "rgb_clk_main.c"
                    INCLUDE_DIRS "." 
                    REQUIRES i2c_ds3231 led_matrix driver console esp_wifi)