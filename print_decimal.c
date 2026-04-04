#include "main.h"
#include <unistd.h>
#include <stdarg.h>

/**
 * recursive_int - Function aux for diplay the numbers
 * @n: The number (unsigned for manage INT_MIN)
 * @count: Pointer to the "internal print counter"
 * Return: -1 on failure, 0 on success.
 *
 * NOTE: prototype changed to include a pointer to "caller counter"
 *   in order to separate the logic for counting successful writes
 *   and the logic for "bubbling up the error code case arising".
 *   Of course it wasn't the only way to do so, but I find it simple.
 *  Also, func returns 0 on success and not 1 to avoid any confusion
 *   on responsability and meaning of its return (since now the count
 *   is taken care of with a cross-func shared integer pointer).
 */
int recursive_int(unsigned int n, int *count)
{
	char digit;

	/* While number is >= 10 we "consume" recursively with division by 10 */
	if (n / 10)
	{
		if (recursive_int(n / 10, count) < 0)
			return (-1);
	}

	/* Process for the unit digit of number in stack frame */
	digit = (n % 10) + '0';
	/* Works but hard to read. */
	/*return ((write(1, &digit, 1) < 0) ? -1 : ++(*count)); */
	if ((write(1, &digit, 1) < 0))
		return (-1);
	(*count)++;
	return (0);
}

/**
 * print_decimal - Manage specifiers %d et %i
 * @args: Variadic list
 * Return: Number of characters display
 */
int print_decimal(va_list args)
{
	int n = va_arg(args, int);
	unsigned int abs_n;
	int count = 0;

	/* Gestion du signe négatif */
	if (n < 0)
	{
		if (write(1, "-", 1) < 0)
			return (-1);
		count++;
		abs_n = (unsigned int)(-n);
	}
	else
		abs_n = (unsigned int)n;

	/* Appel de la fonction récursive pour afficher les chiffres */
	/* count += recursive_int(abs_n); */
	/* Changed to allow "error bubbling up". Counter incremented inside. */
	if (recursive_int(abs_n, &count) < 0)
		return (-1);
	/* Above stops when one digit cannot be printed (count is then "lost"). */

	return (count);
}
