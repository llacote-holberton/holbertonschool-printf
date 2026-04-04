#include "main.h"
#include <unistd.h>
#include <stdarg.h>

/**
 * print_string - Display a strings characters.
 * @args: A variadic list with a string to display.
 * * Return: number of char displays.
 */
int print_string(va_list args)
{
	char *str;
	int i = 0;
	int write_success;

	/* On récupère l'argument de type char* */
	str = va_arg(args, char *);

	/* Si la chaîne est NULL, le standard printf affiche "(null)" */
	if (str == NULL)
	str = "(null)";

	/* On boucle sur la chaîne et on affiche chaque caractère */
	while (str[i] != '\0')
	{
		write_success = write(1, &str[i], 1);
		if (write_success < 0)
			return (-1);
		i++;
	}

	/* retourne le nombre de caractères écrits (i) */
	return (i);
}
