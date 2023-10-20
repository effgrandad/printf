/**
 * calculate_precision - Calculates the precision for printing
 * @formatString: Formatted string in which to print the arguments
 * @currentIndex: Current index in the format string
 * @argList: List of arguments.
 *
 * Return: Precision.
 */
int calculate_precision(const char *formatString, int *currentIndex,
		va_list argList)
{
	int currentIdx = *currentIndex + 1;
	int precision = -1;

	if (formatString[currentIdx] != '.')
		return (precision);

	precision = 0;

	for (currentIdx += 1; formatString[currentIdx] != '\0'; currentIdx++)
	{
		if (is_digit(formatString[currentIdx]))
		{
			precision *= 10;
			precision += formatString[currentIdx] - '0';
		}
		else if (formatString[currentIdx] == '*')
		{
			currentIdx++;
			precision = va_arg(argList, int);
			break;
		}
		else
		{
			break;
		}
	}

	*currentIndex = currentIdx - 1;

	return (precision);
}

