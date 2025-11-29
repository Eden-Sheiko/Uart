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

typedef enum uart_baudrate {
    UART_BAUD_0       = B0,
    UART_BAUD_50      = B50,
    UART_BAUD_75      = B75,
    UART_BAUD_110     = B110,
    UART_BAUD_134     = B134,
    UART_BAUD_150     = B150,
    UART_BAUD_200     = B200,
    UART_BAUD_300     = B300,
    UART_BAUD_600     = B600,
    UART_BAUD_1200    = B1200,
    UART_BAUD_1800    = B1800,
    UART_BAUD_2400    = B2400,
    UART_BAUD_4800    = B4800,
    UART_BAUD_9600    = B9600,
    UART_BAUD_19200   = B19200,
    UART_BAUD_38400   = B38400,
    UART_BAUD_57600   = B57600,
    UART_BAUD_115200  = B115200,
    UART_BAUD_230400  = B230400,
    UART_BAUD_460800  = B460800
} uart_baudrate_t;

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
    uart_baudrate_t         baudrate;
    uart_bits_per_byte_t    bits_per_byte;
    bool                    stop_bit;
    bool                    parity_bit;
    bool                    flow_control;
    uint8_t                 timeout;
}uart_module_config_t;

typedef enum uart_module_status {
    UART_MODULE_OK = 0,
    UART_MODULE_ARG_NULL_ERROR,
    UART_MODULE_WRONG_ARG_ERROR,
    UART_MOUDLE_SETTING_BAUD_ERROR,
    UART_MODULE_APPLY_SETTINGS_ERROR,
    UART_MODULE_ERROR

}uart_module_status_t;


uart_module_t* uart_module_init(uart_module_config_t* cfg);

uart_module_status_t uart_module_user_config(uart_module_t* cfx, uart_module_config_t* cfg);

uart_module_status_t uart_module_apply(uart_module_t* cfx);

uart_module_status_t uart_module_set_parity(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_set_stop_bit(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_set_baudrate(uart_module_t* cfx, uart_baudrate_t baud);

uart_module_status_t uart_module_set_bits_per_byte(uart_module_t* cfx, uart_bits_per_byte_t state);

uart_module_status_t uart_module_hardware_flow_control(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_canonical_mode(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_destroy(uart_module_t* cfx);

uart_module_status_t uart_module_echo(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_signal_chars(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_software_flow_control(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_special_handling(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_output_modes(uart_module_t* cfx, bool state);

uart_module_status_t uart_module_vmin_vtime(uart_module_t* cfx, uint8_t vmin, uint8_t vtime);



//read and write
size_t uart_read(uart_module_t* handle, uint8_t* data, size_t length);

size_t uart_write(uart_module_t* handle, uint8_t* data, size_t length);



#endif //UARTWRAPPERLINUX_UART_H