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

uart_module_status_t set_parity(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_cflag |= PARENB;
    } else {
        cfx->m_termios.c_cflag &= ~PARENB;
    }
    return UART_MODULE_OK;
}

uart_module_status_t set_stop_bit(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_cflag |= CSTOP;
    } else {
        cfx->m_termios.c_cflag &= ~CSTOP;
    }
    return UART_MODULE_OK;
}

uart_module_status_t set_number_of_bits_(uart_module_t* cfx, uart_bits_per_byte_t state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    switch (state) {
        case FIVE_BITS:
            cfx->m_termios.c_cflag |= CS5;
            break;
        case SIX_BITS:
            cfx->m_termios.c_cflag |= CS6;
            break;
        case SEVEN_BITS:
            cfx->m_termios.c_cflag |= CS7;
            break;
        case EIGHT_BITS:
            cfx->m_termios.c_cflag |= CS8;
            break;
        case CLEAR_ALL:
            cfx->m_termios.c_cflag &= ~CSIZE;
            break;
        default:
            //LOG UNKNOW
            break;
    }

    return UART_MODULE_OK;
}

uart_module_status_t hardware_flow_control(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_cflag |= CRTSCTS;
    } else {
        cfx->m_termios.c_cflag &= ~CRTSCTS;
    }
    return UART_MODULE_OK;
}

uart_module_status_t uart_module_destroy(uart_module_t* cfx) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    free(cfx);
    return UART_MODULE_OK;
}

uart_module_status_t canonical_mode(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_lflag |= ICANON;
    } else {
        cfx->m_termios.c_lflag &= ~ICANON;
    }
    return UART_MODULE_OK;
}