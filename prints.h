#ifndef PRINTS_H
#define PRINTS_H

/* Headers */
#include <stdarg.h>
#include <stdlib.h>

int _puts(char *str, int fd);
int _putchar(char c);
int print_integer(int num);
void printMsg(cmd_t cmd_info, char *);
int _dprintf(int fd, const char *format, ...);
#endif
