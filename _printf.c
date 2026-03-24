/* Orchestrator function for formatted printing */
#include "main.h"
#include <stdarg.h>

#include <stdio.h> /* Temporary */
/**
 * _printf - Prints formatted strings to standard output.
 * @format: string mixing literal characters, format introducer (%)
 *     and format identifiers ('c', 'i', 's', 'f').
 *     The chain of format introducer and format identifier creates
 *       a "conversion command".
 * @...: variadic number of additional arguments.
 *   This chain of arguments must normally have a number of arguments
 *   equal to the number of "conversion commands".
 *
 * Return: integer representing total number of characters outputted.
 * 
 * Description: outputs a string composed of literal characters 
 *   and formatable named components on the file descriptor 1
 *   which is usually an end-user's interface (ex terminal screen).
 *
 */
int _printf(const char *format, ...)
{
  int total;  /* Total number of characters outputted */

  /* @remove random printf to avoid "unused variable" compil error. */
  printf("%s\n", format);

  total = 0;
  return (total);
}

