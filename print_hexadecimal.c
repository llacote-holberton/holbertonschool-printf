#include "main.h"
#include <unistd.h>

/**
 * hex_helper - Engine of hexadecimal conversion
 * @n: The number of conversion
 * @base: The chain "0123456789abcdef" ou "0123456789ABCDEF"
 * Return: Numbers of char printed
 */
static int hex_helper(unsigned int n, char *base)
{
	int count = 0;
	char c;

	if (n / 16)
		count += hex_helper(n / 16, base);

	c = base[n % 16];
	write(1, &c, 1);

	return (count + 1);
}

/**
 * print_hexadecimal_lowercase - Manage %x
 * @args: va_list
 * Return: Number of char
 */
int print_hexadecimal_lowercase(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);

	return (hex_helper(n, "0123456789abcdef"));
}

/**
 * print_hexadecimal_uppercase - Manage %X
 * @args: va_list
 * Return: Number of char
 */
int print_hexadecimal_uppercase(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);

	return (hex_helper(n, "0123456789ABCDEF"));
}
