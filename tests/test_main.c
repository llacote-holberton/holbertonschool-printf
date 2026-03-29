#include <stdio.h>
#include <limits.h>
#include "main.h"


/**
 * main - Test suite for _printf
 *
 * Return: 0
 */
int main(void)
{
	int len, len2;
	int big_decimal;
	char convert_buff[65];
	char *big_converted;

	printf("--- TEST 01: Strings ---\n");
	len = _printf("Underscore: %s\n", "Hello World");
	len2 = printf("StdLibrary: %s\n", "Hello World");
	printf("Lengths: [%d, %d]\n\n", len, len2);

	printf("--- TEST 02: NULL String ---\n");
	len = _printf("Underscore: %s\n", NULL);
	len2 = printf("StdLibrary: %s\n", NULL);
	printf("Lengths: [%d, %d]\n\n", len, len2);

	printf("--- TEST 03: Integers ---\n");
	len = _printf("Underscore: %d, %i\n", -1024, 2024);
	len2 = printf("StdLibrary: %d, %i\n", -1024, 2024);
	printf("Lengths: [%d, %d]\n\n", len, len2);

	printf("--- TEST 04: INT_MIN & INT_MAX ---\n");
	len = _printf("Underscore: %d, %d\n", INT_MIN, INT_MAX);
	len2 = printf("StdLibrary: %d, %d\n", INT_MIN, INT_MAX);
	printf("Lengths: [%d, %d]\n\n", len, len2);

	printf("--- TEST 05: Percent ---\n");
	len = _printf("Underscore: %%\n");
	len2 = printf("StdLibrary: %%\n");
	printf("Lengths: [%d, %d]\n", len, len2);

	printf("--- TEST 06: Lone EOL character ---\n");
	printf("Underscore with char formatter: ");
	len = _printf("%c", '\0');
	printf("\n");
	printf("StdLibrary with char formatter: ");
	len2 = printf("%c", '\0');
	printf("\n");
	printf("Lengths: [%d, %d]\n", len, len2);

	printf("Underscore as literal: ");
	len = _printf("%c", '\0');
	printf("\n");
	printf("StdLibrary as literal: ");
	len2 = printf("%c", '\0');
	printf("\n");
	printf("Lengths: [%d, %d]\n", len, len2);
	

	printf("--- TEST 07a: Single plain ASCII character ('z') ---\n");
	printf("Underscore: ");
	fflush(stdout); /* Forces to empty the stdout buffer. */
	len = _printf("z");
	printf("\n");
	printf("StdLibrary: ");
	len2 = printf("z");
	printf("\n");
	printf("Lengths: [%d, %d]\n", len, len2);

	printf("--- TEST 07b: Single plain UTF8 character ('é') ---\n");
	printf("Underscore: ");
	fflush(stdout); /* Required because no \n on previous printf call */
	len = _printf("é");
	printf("\n");
	printf("StdLibrary: ");
	len2 = printf("é");
	printf("\n");
	printf("Lengths: [%d, %d]\n", len, len2);

	/* TESTS UTILS */
	printf("--- TEST UTILS ---\n");
	big_decimal = -224466777;
	printf("*** Convert to lowercase hexa ***\n");
	big_converted = convert_decimal_up_to_base_16(big_decimal, 16, convert_buff, (size_t)65);
	len = _printf("Underscore: %s\n", big_converted);
	len2 = printf("StdLibrary: %s\n", big_converted);
	printf("Lengths: [%d, %d]\n", len, len2);

	printf("*** Convert to octal ***\n");
	big_converted = convert_decimal_up_to_base_16(big_decimal, 8, convert_buff, (size_t)65);
	len = _printf("Underscore: %s\n", big_converted);
	len2 = printf("StdLibrary: %s\n", big_converted);
	printf("Lengths: [%d, %d]\n", len, len2);

	return (0);
}
