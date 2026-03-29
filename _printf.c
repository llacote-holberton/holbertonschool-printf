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
	table['c'] = print_character;
	table['s'] = print_string;
	table['d'] = print_decimal;
	table['i'] = print_decimal;
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
 * @total: pointer to the total to increment.
 * Return: >=0 if success (total is incremented "inplace")
 *   or -1 if failure (bubbling up write error code).
 */
int print_single_char(char c, int *total)
{
	int write_successful = 0;

	write_successful = write(1, &c, 1);
	if (write_successful >= 0)
		*total += write_successful;

	return (write_successful);
}

/**
 * delegate_print - Helper function which encapsulates prints to manage error.
 * @printer: pointer to a dedicated printing function.
 * @components: variadic list to propagate to dedicated printer.
 * @total: pointer to an integer used to count overall amount of printed chars.
 *
 * Return: 0 on success, -1 if error ("bubbling up" return from write.)
 *
 * NOTES:
 * 1/ Had to use a subfunction to make the indirection because taking care
 *    of the "case failure in writing" in _printf
 *    would have made n° of lines explode.
 * 2/ Had to affect total directly "by passing pointer" because
 *    just bubbling up would have ended up with the same problem.
 */
int delegate_print(int (*printer)(va_list), va_list components, int *total)
{
	int count;

	count = printer(components);
	if (count == -1)
		return (-1);
	else
	{
		*total += count;
		return (0);
	}
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
	int total = 0;      /* Total number of characters outputted */
	unsigned int i = 0; /* Cursor used to traverse "format"     */
	int (*subprinter)(va_list); /* Required for printing through delegation.*/
	int subprinter_return = 0; /* Used to bubble up potential error return. */

	if (format == NULL) /* Guard clause */
		return (-1);      /* Seems fair to return negative for error. */
	supported_formats = get_supported_formats();
	va_start(components, format);
	while (format[i])
	{
		if (format[i] == conversion_delimiter && format[i + 1] != '\0')
		{
			if (format[i + 1] == '%')
				subprinter_return = print_single_char('%', &total);
			else if (supported_formats[(int)format[i + 1]])
			{
				subprinter = supported_formats[(int)format[i + 1]];
				subprinter_return = delegate_print(subprinter, components, &total);
			}
			else
			{
				subprinter_return = print_single_char(format[i], &total);
				subprinter_return = print_single_char(format[i + 1], &total);
			}
			i += 2;
			continue;
		}
		else
		{
			subprinter_return = print_single_char(format[i], &total);
			i++;
		}
		if (subprinter_return < 0)
			return (-1);
	}
	va_end(components);
	return (total);
}

