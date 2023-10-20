#include "main.h"

/**
 * get_width - Calculates width to printing
 * @formatString: Formatted string in which to print the arguments.
 * @currentIndex: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *formatString, int *currentIndex, va_list argList)
{
	int currentIndex;
	int width = 0;

	for (currentIndex = *currentIndex + 1; format[currentIndex] != '\0';
			currentIndex++)
	{
		if (is_digit(format[currentIndex]))
		{
			width *= 10;
			width += format[currentIndex] - '0';
		}
		else if (format[currentIndex] == '*')
		{
			currentIndex++;
			width = va_arg(List, int currentIndex);
			break;
		}
		else
			break;
	}

	*currentIndex = currentIndex - 1;

	return (width);
}

