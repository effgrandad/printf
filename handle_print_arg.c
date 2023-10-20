
#include "main.h"

/**
 * handle_print_argument - Prints an argument based on its type
 * @formatString: Formatted string in which to print the arguments.
 * @currentIndex: Current index.
 * @argList: List of arguments to be printed.
 * @outputBuffer: Buffer array to handle print.
 * @activeFlags: Active flags
 * @fieldWidth: Get width.
 * @precision: Precision specification
 * @castSize: Size specifier
 * Return: 1 or 2;
 */
int handle_print_argument(const char *formatString, int *currentIndex,
		va_list argList, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int castSize)
{
	int i, unknownLength = 0, printedChars = -1;
	format_specifier_t formatSpecifiers[] = {
		{'c', print_character}, {'s', print_string}, {'%', print_percent},
		{'i', print_integer}, {'d', print_integer}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal},
		{'x', print_hexadecimal},
		{'X', print_hexadecimal_upper}, {'p', print_pointer_value},
		{'S', print_non_printable_chars},
		{'r', print_reversed_string}, {'R', print_rot13_string}, {'\0', NULL}
	};
	for (i = 0; formatSpecifiers[i].specifier != '\0'; i++)
		if (formatString[*currentIndex] == formatSpecifiers[i].specifier)
			return (formatSpecifiers[i].function(argList,
						outputBuffer, activeFlags, fieldWidth, precision, castSize));

	if (formatSpecifiers[i].specifier == '\0')
	{
		if (formatString[*currentIndex] == '\0')
			return (-1);
		unknownLength += write(1, "%%", 1);
		if (formatString[*currentIndex - 1] == ' ')
			unknownLength += write(1, " ", 1);
		else if (fieldWidth)
		{
			--(*currentIndex);
			while (formatString[*currentIndex] != ' ' &&
					formatString[*currentIndex] != '%')
				--(*currentIndex);
			if (formatString[*currentIndex] == ' ')
				--(*currentIndex);
			return (1);
		}
		unknownLength += write(1, &formatString[*currentIndex], 1);
		return (unknownLength);
	}
	return (printedChars0);
}

