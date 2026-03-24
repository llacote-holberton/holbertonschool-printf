#ifndef MAIN_H
#define MAIN_H

/* Required so compiler "understands" va_list as variable type. */
#include <stdarg.h>

/* On screen printer of formatted strings (limited format support) */
int _printf(const char *format, ...);

/* "Unit functions" indirected through _printf to output specific data types. */
/* Except the last two each will be in its own .c file. */
int print_character(va_list);
int print_string(va_list);
int print_decimal(va_list);
int print_unsigned(va_list);
int print_octal(va_list);
int print_hexadecimal(va_list);

#endif
