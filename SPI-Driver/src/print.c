#include "print.h"
#include "uart.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

// helper to print unsigned
static void utoa_uart(unsigned u) {
    char buf[10];
    int  i = 0;
    if (u == 0) {
        uart_write('0');
        return;
    }
    while (u && i < (int)sizeof(buf)-1) {
        buf[i++] = '0' + (u % 10);
        u /= 10;
    }
    while (i--) {
        uart_write(buf[i]);
    }
}

static void itoa_uart(int n) {
    if (n < 0) {
        uart_write('-');
        utoa_uart((unsigned)(-n));
    } else {
        utoa_uart((unsigned)n);
    }
}

void printf_uart(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    while (*fmt) {
        if (*fmt == '%') {
            ++fmt;
            switch (*fmt) {
                case 's': {
                    const char *s = va_arg(ap, const char*);
                    while (*s) uart_write(*s++);
                    break;
                }
                case 'd': 
                    itoa_uart(va_arg(ap, int));
                    break;
                case 'u':
                    utoa_uart(va_arg(ap, unsigned));
                    break;
                case '%':
                    uart_write('%');
                    break;
                default:
                    // unknown specifier, just print it
                    uart_write('%');
                    uart_write(*fmt);
            }
        } else {
            uart_write(*fmt);
        }
        ++fmt;
    }
    va_end(ap);
}
