#include "../Inc/Uart.h"

struct uart_module {
    int             fd;
    struct termios  m_termios;
};

uart_module_t* uart_module_init(uart_module_config_t* cfg) {
    uart_module_t* handle = NULL;
    int res = 0;
    handle = calloc(1, sizeof(uart_module_t));
    if (handle == NULL) {
        /* error (heap memory management) */
        goto err;
    }
    if (cfg == NULL) {
        /* log no config was loaded going with default. */
        goto err_clean;
    } else {
        /* log config was loaded and its ... bla bla /dev */
        res = handle->fd = open(cfg->path, O_RDWR);
        if (res < 0) {
            /* log error */
            goto err_clean;
        }
        return handle;
    }


    err_clean:
        free(handle);
        return NULL;

    err:
        return NULL;
}
