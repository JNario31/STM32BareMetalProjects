#ifndef PRINT_H
#define PRINT_H

// send a null‑terminated string over UART, with CRLF
void puts_uart(const char *s);
void printf_uart(const char *fmt, ...);

#endif
