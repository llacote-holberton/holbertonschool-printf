#include <stddef.h>
#include "main.h"

/**
 * change_integer_base - converts a decimal into a string
 *   representing the n in a base deduced from charset length (without EOL).
 * @n: the integer to convert (initially "number" but needed space).
 * @charset: the set of symbols to represent number in new base
 *   (used in order of apparition from left to right).
 * @buffer: char array which will store "digits" of conversion.
 * @buffer_size: required for control AND to know provided array's end
 *   so we can "jump to it" with our pointer.
 *
 * Return: string representing new character.
 *
 * NOTE: buffer MUST be passed as "provided by caller" because...
 *   a) Static may lead to undesired behaviour (like simultaneous calls).
 *   b) The smart approach of using a pointer on the buffer and returning it
 *        once "set at the right address" cannot work if the buffer lifetime
 *        is tied to a specific instance of the function (stack frame).
 */
char *change_integer_base(unsigned int n, char *charset,
																							char *buffer, size_t buffer_size)
{
	char *digit_writer;
	unsigned int base = 0;
	char seen[256] = {0};

	if (!charset || buffer_size > CONVERT_MAX_BUFFER)
		return (CONVERT_ERROR);

	/* We must first "compute" the target base */
	/* To avoid a full recopy while checking for duplicate chars we use */
	/*   the classic "boolean table" trick. */
	while (charset[base])
	{
		/* Character already put once in charset, pursuing would lead */
		/*   to unprecise / ambiguous representations. */
		/* Casting as unsigned ensures int value is within table range. */
		if (seen[(unsigned char)charset[base]])
			return (CONVERT_ERROR);
		/* Marking char as "seen once" in provided set. */
		seen[(unsigned char)charset[base]] = 1;
		base++;
	}
	if (base < 2)
		return (CONVERT_ERROR);

	digit_writer = buffer + buffer_size;
	*digit_writer = '\0';

	do {
		*(--digit_writer) = charset[n % base];
		n = n / base;
	} while (n);

	return (digit_writer);
}
