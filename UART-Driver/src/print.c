#include "print.h"
#include "uart.h"

void puts_uart(const char *s) {
    while (*s) {
        uart_write(*s++);
    }
    uart_write('\r');
    uart_write('\n');
}
