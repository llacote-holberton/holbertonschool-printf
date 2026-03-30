#include <stddef.h>
#include "main.h"

/**
 * convert_decimal_up_to_base_16 - converts a decimal into a string
 *   representing the n in base n
 * @n: the integer to convert (initially "number" but needed space).
 * @base: the target base to convert it into.
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
char *convert_unsigned_decimal_up_to_base_16(unsigned int n, unsigned int base,
																		char *buffer, size_t buffer_size)
{
	char *digit_writer;
	char *digits;

	if (!n || base < 2 || base > 16 || buffer_size > CONVERT_MAX_BUFFER)
		return ("");
	/* Digits covering up to base16 (hexadecimal) */
	digits = "0123456789abcdef";
	digit_writer = buffer + buffer_size;
	*digit_writer = '\0';

	do {
		*(--digit_writer) = digits[n % base];
		n = n / base;
	} while (n);

	return (digit_writer);
}

/**
 * convert_signed_decimal_up_to_base_16 - converts a decimal into a string
 *   representing the n in base n
 * @n: the integer to convert (initially "number" but needed space).
 * @base: the target base to convert it into.
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
char *convert_signed_decimal_up_to_base_16(int n, unsigned int base,
																		char *buffer, size_t buffer_size)
{
	char *digit_writer;
	char *digits;
	int n_is_negative;

	if (!n || base < 2 || base > 16 || buffer_size > CONVERT_MAX_BUFFER)
		return (""); /* How to properly inform "out of bounds request" ? */
		/* Digits covering up to base16 (hexadecimal) */
	digits = "0123456789abcdef";
	/* Pointer used to write digits in buffer. */
	/* Since we get digits "from the least relevant first" the best is to */
	/*   directly store from the array's end. */
	digit_writer = buffer + buffer_size;
	/* AND since we'll return a string we can immediately write the EOL char. */
	*digit_writer = '\0';

	/* Need to know the sign. */
	n_is_negative = (n < 0);
	/* Now we do a while which "moonwalks" through the array by */
	/*   dividing n iteratively, getting "lowest significant" digit */
	/* each time then "updating n "*/
	/* Number not null so we are sure we can do at least one division */
	do {
		/* Move pointer BEFORE derefencing to not overwrite EOL. */
		*(--digit_writer) = digits[n % base];  /* Remainder gives us the digit. */
		n = n / base;    /* We reduce number "by one dimension" for next cycle. */
	} while (n);               /* Process will make it end "as 0" so "false". */

	if (n_is_negative)   /* How to cover case no cell left in array for sign? */
		*(--digit_writer) = '-'; /* BEWARE of not mixing "" and ''! */

	return (digit_writer);
}
