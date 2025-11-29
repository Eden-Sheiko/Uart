#include <stdio.h>
#include "Inc/Uart.h"
int main(void) {
    uart_module_t* ctx = NULL;
    uart_module_config_t config = {
        .path = "/dev/ttyUSB0",
        .baudrate = UART_BAUD_115200,
        .bits_per_byte = EIGHT_BITS,
        .stop_bit = 1,
        .parity_bit = 0,
        .flow_control = 0,
        .timeout = 1
    };
    ctx = uart_module_init(&config);





    uart_module_destroy(ctx);
    return 0;
}