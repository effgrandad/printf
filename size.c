#include "main.h"


/**
 * calculate_cast_size - Calculates the size to cast the argument
 * @formatString: Formatted string in which to print the arguments
 * @currentIndex: Current index in the format string
 *
 * Return: Cast size.
 */
int calculate_cast_size(const char *formatString, int *currentIndex)
{
	int currentIdx = *currentIndex + 1;
	int castSize = 0;

	if (formatString[currentIdx] == 'l'
	{
			castSize = S_LONG;
	}
	else if (formatString[currentIdx] == 'h')
	{
		castSize = S_SHORT;
	}
	if (castSize == 0)
	{
		*currentIndex = currentIdx - 1;
	}
	else
	{
		*currentIndex = currentIdx;
	}
	return (castSize);
}
