#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * print_octal - Prints next variadic argument "as an octal number".
 * @components: variadic list holding component to read.
 * Return: number of characters printed or -1 on error.
 *
 * NOTES
 * 1. The caller guarantees that the specifier requests
 *     "printing as a character". However no guarantee that
 *     the "next variadic parameter" is indeed of the right type.
 * 2. We arbitrarily consider that the provided number will be
 *     of "unsigned integer" type.
 */
int print_octal(va_list components)
{
	unsigned int source; /* Arbitrary choice to restrict to unsigned. */
	char buffer[CONVERT_MAX_BUFFER]; /* To store conversion digits.  */
	char *converted;     /* Pointer to start of converted string      */
	int length;          /* Size of converted string.                 */
	int written;      /* Counts printed and can hold potential error. */

	source = va_arg(components, unsigned int);
	converted = convert_unsigned_decimal_up_to_base_16(source,
											8, buffer, CONVERT_MAX_BUFFER);

	/* Was gonna do a whole "step by step calculate length", useless! */
	/* while (converted) */
	length = (buffer + CONVERT_MAX_BUFFER) - converted;
	written = write(1, converted, length);

	return (written);
}
