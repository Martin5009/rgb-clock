set(srcs "led_matrix_control.c"
         "led_matrix_char.c"
         )

set(include "."
            "fonts"
            )

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS ${include}
                    REQUIRES driver)