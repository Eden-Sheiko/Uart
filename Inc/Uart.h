#ifndef UARTWRAPPERLINUX_UART_H
#define UARTWRAPPERLINUX_UART_H
#ifndef  __linux__
#error This code should NOT be compiled on Linux.
#endif

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <stdlib.h> // for heap memory
#include <stdint.h>
#include <stdbool.h>

typedef enum uart_buadrate_speed {
    some_param,
}uart_buadrate_speed_t;

typedef enum uart_bits_per_byte {
    FIVE_BITS =     1U,
    SIX_BITS,
    SEVEN_BITS,
    EIGHT_BITS,
    CLEAR_ALL
}uart_bits_per_byte_t;

typedef struct uart_module uart_module_t;

typedef struct uart_module_config {
    const char*             path;
    uart_bits_per_byte_t    bits;
}uart_module_config_t;

typedef enum uart_module_status {
    UART_MODULE_OK = 0,
    UART_MODULE_ARG_NULL_ERROR

}uart_module_status_t;


uart_module_t* uart_module_init(uart_module_config_t* cfg);

uart_module_status_t set_parity(uart_module_t* cfx, bool state);

uart_module_status_t set_stop_bit(uart_module_t* cfx, bool state);

uart_module_status_t set_number_of_bits_(uart_module_t* cfx, uart_bits_per_byte_t state);

uart_module_status_t hardware_flow_control(uart_module_t* cfx, bool state);

uart_module_status_t canonical_mode(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_destroy(uart_module_t* cfx);


#endif //UARTWRAPPERLINUX_UART_H