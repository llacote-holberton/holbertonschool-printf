/* Orchestrator function for formatted printing */
#include "main.h"
#include <stdarg.h> /* Required for variadic parsing.    */
#include <unistd.h> /* Required for write standard func. */

#include <stdio.h> /* Temporary */

/* "Local helpers for _printf */

/**
 * get_supported_formats - Initializes a correspondance table
 *   for _printf to know which characters matches supported formats.
 * Return: a pointer to the first element of a table of function pointers.
 *
 * NOTE: wouldn't have managed to "extract" the table from _printf body
 *   to use a helper function without help from IA. Double pointers are hard.
 */
int (**get_supported_formats(void))(va_list)
{
	static int (*table[128])(va_list); /* all entries automatically NULL */
	/* Affecting only the "character index" which we want to support.    */
	/*  Value should always be the name of a function declared in main.h */
	/* table['c'] = print_character; */
	/* table['s'] = print_string;    */
	/* table['d'] = print_decimal;   */
	/* table['i'] = print_decimal;   */ /* @note behaves like 'd' in printf. */
	/* table['o'] = print_octal;     */
	/* table['u'] = print_unsigned;   */
	/* table['x'] = print_hexadecimal_lowercase;   */
	/* table['X'] = print_hexadecimal_uppercase;   */

	return (table);
}

/**
 * print_single_char - Helper function to print
 *   just a single character without call to variadic.
 * @c: character to print.
 * Return: 1 if success (to increment total count of chars printed).
 */
int print_single_char(char c)
{
	if (c == '\0')
		return (-1);
	else
		return (write(1, &c, 1));
}

/**
 * _printf - Prints formatted strings to standard output.
 * @format: string mixing literal characters, format introducer (%)
 *     and format identifiers ('c', 'i', 's', 'f').
 *     The chain of format introducer and format identifier creates
 *       a "conversion command".
 * @...: variadic number of additional arguments.
 *   This chain of arguments must normally have a number of arguments
 *   equal to the number of "conversion commands".
 *
 * Return: integer representing total number of characters outputted.
 *
 * Description: outputs a string composed of literal characters
 *   and formatable named components on the file descriptor 1
 *   which is usually an end-user's interface (ex terminal screen).
 *
 */
int _printf(const char *format, ...)
{
	int (**supported_formats)(va_list);
	char conversion_delimiter = '%';

	va_list components; /* Variadic list of "string components" */
	int total;          /* Total number of characters outputted */
	unsigned int i = 0; /* Cursor used to traverse "format"     */

	supported_formats = get_supported_formats();

	if (format == NULL) /* Guard clause */
		return (-1);      /* Seems fair to return negative for error. */

	va_start(components, format);
	while (format[i])
	{
		if (format[i] == conversion_delimiter && format[i + 1] != '\0')
		{
			if (format[i + 1] == '%')
				print_single_char(format[i++]);
			else if (supported_formats[(int)format[i + 1]])
			{
				supported_formats[(int)format[i + 1]](components);
				i += 1;
			}
			else
				print_single_char(format[i]);
		}
		else
		{
			print_single_char(format[i]);
		}
		i++;
	}

	/* @remove random printf to avoid "unused variable" compil error. */
	/* printf("%s\n", format); */
	/* Thanks ChatGPT for this tip. Avoids "unused variable" error. */
	(void)supported_formats;
	(void)conversion_delimiter;
	(void)format;

	va_end(components);

	total = 0;
	return (total);
}

