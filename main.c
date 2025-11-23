#include <stdio.h>
#include "Inc/Uart.h"
int main(void) {
    uart_module_t* ctx = NULL;
    uart_module_config_t config = {
        .path = "/dev/ttyUSB0",
        .bits = EIGHT_BITS
    };
    ctx = uart_module_init(&config);



    uart_module_destroy(ctx);
    return 0;
}