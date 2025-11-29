#include "../Inc/Uart.h"

struct uart_module {
    int             fd;
    struct termios  m_termios;
    uart_baudrate_t output_buadrate;
    uart_baudrate_t input_buadrate;
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
        if (tcgetattr(handle->fd, &handle->m_termios) != 0) {
            /* log error */
            goto err_close_fd;
        }
        return handle;
    }


    err_clean:
        free(handle);
        return NULL;
    err_close_fd:
        close(handle->fd);
        free(handle);
        return NULL;

    err:
        return NULL;
}


uart_module_status_t uart_module_user_config(uart_module_t* cfx, uart_module_config_t* cfg) {
    if (cfx == NULL || cfg == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    uart_module_set_baudrate(cfx, cfg->baudrate);
    uart_module_set_bits_per_byte(cfx, cfg->bits_per_byte);
    uart_module_set_stop_bit(cfx, cfg->stop_bit);
    uart_module_set_parity(cfx, cfg->parity_bit);
    uart_module_hardware_flow_control(cfx, cfg->flow_control);
    uart_module_vmin_vtime(cfx, 0 ,cfg->timeout);

    if (tcsetattr(cfx->fd, TCSANOW, &cfx->m_termios) != 0) {
        return UART_MODULE_APPLY_SETTINGS_ERROR;
    }

    return UART_MODULE_OK;
}

uart_module_status_t uart_module_set_parity(uart_module_t* cfx, bool state) {
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

uart_module_status_t uart_module_set_stop_bit(uart_module_t* cfx, bool state) {
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

uart_module_status_t uart_module_set_bits_per_byte(uart_module_t* cfx, uart_bits_per_byte_t state) {
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
            return UART_MODULE_WRONG_ARG_ERROR;
            break;
    }

    return UART_MODULE_OK;
}

uart_module_status_t uart_module_hardware_flow_control(uart_module_t* cfx, bool state) {
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

uart_module_status_t uart_module_canonical_mode(uart_module_t* cfx, bool state) {
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

uart_module_status_t uart_module_echo(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_lflag |= ECHO;
        cfx->m_termios.c_lflag |= ECHOE;
        cfx->m_termios.c_lflag |= ECHONL;
    } else {
        cfx->m_termios.c_lflag &= ~ECHO;
        cfx->m_termios.c_lflag &= ~ECHOE;
        cfx->m_termios.c_lflag &= ~ECHONL;
    }
    return UART_MODULE_OK;
}

uart_module_status_t uart_module_signal_chars(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_lflag |= ISIG;

    } else {
        cfx->m_termios.c_lflag &= ~ISIG;
    }
    return UART_MODULE_OK;
}

uart_module_status_t uart_module_software_flow_control(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_lflag |= IXON | IXOFF | IXANY;

    } else {
        cfx->m_termios.c_lflag &= ~(IXON | IXOFF | IXANY);
    }
    return UART_MODULE_OK;
}

uart_module_status_t uart_module_special_handling(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_lflag |= IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL;
    } else {
        cfx->m_termios.c_lflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    }
    return UART_MODULE_OK;
}

uart_module_status_t uart_module_output_modes(uart_module_t* cfx, bool state) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    if (state) {
        cfx->m_termios.c_oflag |= OPOST;
        cfx->m_termios.c_oflag |= ONLCR;
    } else {
        cfx->m_termios.c_oflag &= ~OPOST;
        cfx->m_termios.c_oflag &= ~ONLCR;
    }
    return UART_MODULE_OK;
}

uart_module_status_t uart_module_vmin_vtime(uart_module_t* cfx, uint8_t vmin, uint8_t vtime) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    cfx->m_termios.c_cc[VMIN] = vmin;
    cfx->m_termios.c_cc[VTIME] = vtime;

    return UART_MODULE_OK;
}

uart_module_status_t uart_module_set_baudrate(uart_module_t* cfx, uart_baudrate_t baud) {
    if (cfx == NULL) {
        return UART_MODULE_ARG_NULL_ERROR;
    }
    cfx->input_buadrate = baud;
    cfx->output_buadrate = baud;
    if (cfsetispeed(&cfx->m_termios, cfx->input_buadrate) != 0) {
        return UART_MOUDLE_SETTING_BAUD_ERROR;
    }
    if (cfsetospeed(&cfx->m_termios, cfx->output_buadrate) != 0) {
        return UART_MOUDLE_SETTING_BAUD_ERROR;
    }
    return UART_MODULE_OK;
}


