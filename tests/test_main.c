#include <stdio.h>
#include <limits.h>
#include "main.h"

/**
 * main - Test suite for _printf
 */
int main(void)
{
    int len, len2;

    printf("--- TEST 1: Strings ---\n");
    len = _printf("Perso: %s\n", "Hello World");
    len2 = printf("Standard: %s\n", "Hello World");
    printf("Lengths: [%d, %d]\n\n", len, len2);

    printf("--- TEST 2: NULL String ---\n");
    len = _printf("Perso: %s\n", NULL);
    len2 = printf("Standard: %s\n", NULL);
    printf("Lengths: [%d, %d]\n\n", len, len2);

    printf("--- TEST 3: Integers ---\n");
    len = _printf("Perso: %d, %i\n", -1024, 2024);
    len2 = printf("Standard: %d, %i\n", -1024, 2024);
    printf("Lengths: [%d, %d]\n\n", len, len2);

    printf("--- TEST 4: INT_MIN & INT_MAX ---\n");
    len = _printf("Perso: %d, %d\n", INT_MIN, INT_MAX);
    len2 = printf("Standard: %d, %d\n", INT_MIN, INT_MAX);
    printf("Lengths: [%d, %d]\n\n", len, len2);

    printf("--- TEST 5: Percent ---\n");
    len = _printf("Perso: %%\n");
    len2 = printf("Standard: %%\n");
    printf("Lengths: [%d, %d]\n", len, len2);

    return (0);
}
