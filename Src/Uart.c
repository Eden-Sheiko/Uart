#include "../Inc/Uart.h"

struct uart_module {
    int             fd;
    struct termios  m_termios;
};