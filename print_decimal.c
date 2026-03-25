#include "main.h"
#include <unistd.h>
#include <stdarg.h>

/**
 * recursive_int - Function aux for diplay the numbers
 * @n: The number (unsigned for manage INT_MIN)
 * Return: Numbers of charcaters display
 */
int recursive_int(unsigned int n)
{
    int count = 0;
    char digit;

    if (n / 10)
        count += recursive_int(n / 10);

    digit = (n % 10) + '0';
    write(1, &digit, 1);
    return (count + 1);
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
        write(1, "-", 1);
        count++;
        abs_n = (unsigned int)(-n);
    }
    else
    {
        abs_n = (unsigned int)n;
    }

    /* Appel de la fonction récursive pour afficher les chiffres */
    count += recursive_int(abs_n);

    return (count);
}
