#ifndef MAIN_H
#define MAIN_H


#include <stdarg.h> /* Required for "va_list" variable type. */
#include <stddef.h> /* Required for "size_t"  variable type. */

/* On screen printer of formatted strings (limited format support) */
int _printf(const char *format, ...);

/* "Unit functions" indirected through _printf to output specific data types.*/
/* Except the last two each will be in its own .c file. */
int print_character(va_list);
int print_string(va_list);
int print_decimal(va_list);
int print_uint(va_list);
int print_binary(va_list);
int print_octal(va_list);
int print_hexadecimal_lowercase(va_list);
int print_hexadecimal_uppercase(va_list);

/* Helper functions and related constants */
/* Base 10 to base 2 <= x <= 16 number conversion helper. */
/* @warning DO NOT USE '=' AND DO NOT end with ; */
#define CONVERT_MAX_BUFFER 65
#define CONVERT_ERROR NULL
char *change_integer_base(unsigned int n, char *charset,
										char *buffer, size_t buffer_size);
#endif
