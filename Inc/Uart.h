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

typedef struct uart_module uart_module_t;

typedef struct uart_module_config {
    const char*             path;
}uart_module_config_t;

typedef enum uart_module_status {
    UART_MODULE_OK = 0,

}uart_module_status_t;

typedef enum uart_buadrate_speed {

}uart_buadrate_speed_t;

uart_module_t* uart_module_init(uart_module_config_t* cfg);

uart_module_status_t uart_module_destroy(uart_module_t* cfx);


#endif //UARTWRAPPERLINUX_UART_H