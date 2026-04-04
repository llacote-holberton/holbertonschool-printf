#include <stdarg.h>
#include <unistd.h>

/**
 * print_character - Prints next variadic argument "as a character".
 * @components: variadic list holding component to read.
 * Return: number of characters printed.
 *
 * NOTES
 * 1. The caller guarantees that the specifier requests
 *     "printing as a character". However no guarantee that
 *     the "next variadic parameter" is indeed of the right type.
 * 2. Added a test to avoid "writing '\0'", not for stability but
 *      just to avoid incrementing caller's "total" with invisible char.
 *    For me invisible character should not be "sent" so not counted.
 */
int print_character(va_list components)
{
	char c;
	int write_return;

	c = (char)va_arg(components, int);
	/* Required step to have '\0' counted irrelevant of OS and processor. */
	write_return = (write(1, &c, 1) < 0) ? -1 : 1;

	return (write_return);
}
