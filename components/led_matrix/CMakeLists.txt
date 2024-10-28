set(srcs "fonts" "led_matrix_control.c"
         )

set(include "."
            )

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS ${include}
                    REQUIRES driver)