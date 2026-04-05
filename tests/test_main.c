#include <stdio.h>
#include <limits.h>
#include "../main.h"


/* Helper required because a static directly in macro */
/*   would actually be "reinitialized" since each     */
/*   macro creates a new "copy". */
/**
 * tests_counter - Autoincrements each time a macro is called.
 *
 * Return: up to date counter.
 */
static int tests_counter(void)
{
	static int n;  /* ONE shared counter, automatically set to 0. */

	return (++n);
}

/* Couldn't have found this myself honestly.   */
/* This is a "macro", a cool way to have smart */
/* "automatic copy/paste" of instructions with */
/*  option to provide dynamic context to it.   */
#define TEST_0_ARGS(label, fmt)                      \
do {                                                   \
	printf("\n=== TEST %02d: %s ===\n",               \
	tests_counter(), label);                  \
	printf("Underscore: ");                         \
	fflush(stdout);                                 \
	len = _printf(fmt);                         \
	printf("\nStdLibrary: ");                       \
	len2 = printf(fmt);                          \
	printf("\nLengths: [%d, %d]\n", len, len2);     \
} while (0)

#define TEST_1_ARGS(label, fmt, arg)                       \
do {                                                   \
	printf("\n=== TEST %02d: %s ===\n",               \
	tests_counter(), label);                  \
	printf("Underscore: ");                         \
	fflush(stdout);                                 \
	len = _printf(fmt, arg);                    \
	printf("\nStdLibrary: ");                       \
	len2 = printf(fmt, arg);                     \
	printf("\nLengths: [%d, %d]\n", len, len2);     \
} while (0)

#define TEST_2_ARGS(label, fmt, arg1, arg2)           \
do {                                                   \
	printf("\n=== TEST %02d: %s ===\n",               \
	tests_counter(), label);                  \
	printf("Underscore: ");                         \
	fflush(stdout);                                 \
	len = _printf(fmt, arg1, arg2);                    \
	printf("\nStdLibrary: ");                       \
	len2 = printf(fmt, arg1, arg2);                     \
	printf("\nLengths: [%d, %d]\n", len, len2);     \
} while (0)

#define TEST_3_ARGS(label, fmt, arg1, arg2, arg3)           \
do {                                                   \
	printf("\n=== TEST %02d: %s ===\n",               \
	tests_counter(), label);                  \
	printf("Underscore: ");                         \
	fflush(stdout);                                 \
	len = _printf(fmt, arg1, arg2, arg3);                    \
	printf("\nStdLibrary: ");                       \
	len2 = printf(fmt, arg1, arg2, arg3);                     \
	printf("\nLengths: [%d, %d]\n", len, len2);     \
} while (0)

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
	unsigned int ui = 4294967295;
	char *str_null = NULL;
	char *base08_set = "01234567";
	char *base16_set = "0123456789abcdef";

	printf("==== START AUTOMATED TESTS ON FORMATTERS ====\n");
	TEST_1_ARGS("Strings",  "%s",       "Hello World");
	TEST_1_ARGS("NULL String",  "%s",       str_null);
	TEST_0_ARGS("Double % as literal'",  "%%");
	TEST_0_ARGS("Final % as literal'",  "Beware the last %");
	TEST_1_ARGS("Double % as string",  "%s",       "%% should end as %");
	TEST_1_ARGS("Final % as string",  "%s",       "Beware the last %");
	TEST_2_ARGS("Integers", "%d, %i",        -1024, 2024);
	TEST_2_ARGS("INT_MIN & INT_MAX", "%d, %d", INT_MIN, INT_MAX);
	TEST_1_ARGS("Double percent",  "%%",       "Hello World");
	TEST_1_ARGS("Lone EOL 'as character'",  "%c", '\0');
	TEST_0_ARGS("Lone EOL 'as literal'",  "\0");
	TEST_0_ARGS("Single plain ASCII character ('z') as literal", "z");
	TEST_0_ARGS("Single plain UTF8 character ('é') as literal", "é");
	TEST_2_ARGS("Unsigned",  "%u, %u", INT_MIN, INT_MAX);
	TEST_2_ARGS("Binary",  "%b, %b", INT_MIN, INT_MAX);
	TEST_2_ARGS("Octal",  "%o, %o", INT_MIN, INT_MAX);
	TEST_3_ARGS("Hexadecimal - lower",  "%x, %x, %x", 0, 42, ui);
	TEST_3_ARGS("Hexadecimal - UPPER",  "%X, %X, %X", 0, 42, ui);
	printf("==== END AUTOMATED TESTS ON FORMATTERS ====\n");
	printf("\n==== START AUTOMATED TESTS ON UTILS FUNCS ====\n");
	big_decimal = -224466777;
	big_converted = change_integer_base(
					big_decimal, base16_set, convert_buff, (size_t)65);
	TEST_1_ARGS("Big_N printed as hexa'",  "%s", big_converted);
	big_converted = change_integer_base(
					big_decimal, base08_set, convert_buff, (size_t)65);
	TEST_1_ARGS("Big_N printed as octal'",  "%s", big_converted);

	return (0);
}

/***
 *
 * ATTEMPT TO MAKE A HELPER FUNCTION FOR TESTS
 *   but only "moves" the problem of being constrained
 *   by variadic arguments.
 *
 *int test_wrapper(char t_name, void *t_data, char t_type)
 * {
 * static t_number;
 * int len;
 * int len2;
 * static initialized = 0;
 *
 * if (! initialized)
 *   test_number = 0;
 * printf("\n\n=== Test %d: %s ===\n", t_number, t_name);
 * len = _printf("Underscore: %s\n", "Hello World");
 * len2 = printf("StdLibrary: %s\n", "Hello World");
 * printf("Lengths: [%d, %d]\n\n", len, len2);
  }
 */
