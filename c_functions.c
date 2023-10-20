#include "main.h"
/**
 * print_character - Prints a character
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed
 */
int print_character(va_list argList, char outputBuffer[],       /* change prototype */
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	char c = va_arg(argList, int);

	return (write_character(c, outputBuffer, flags, fieldWidth, precision, lengthModifier));
}

/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width.
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	int length = 0, i;
	char *str = va_arg(argList, char *);

	UNUSED(outputBuffer);
	UNUSED(flags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(lengthModifier);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (fieldWidth > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = fieldWidth - length; i > 0; i--)
				write(1, " ", 1);
			return (fieldWidth);
		}
		else
		{
			for (i = fieldWidth - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (fieldWidth);
		}
	}

	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width.
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	UNUSED(argList);
	UNUSED(outputBuffer);
	UNUSED(flags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(lengthModifier);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_integer - Print integer
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width.
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed
 */
int print_integer(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	int i = BUFFER_SIZE - 2;
	int isNegative = 0;
	long int n = va_arg(argList, long int);
	unsigned long int num;

	n = convert_size_number(n, lengthModifier);

	if (n == 0)
		outputBuffer[i--] = '0';

	outputBuffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		isNegative = 1;
	}

	while (num > 0)
	{
		outputBuffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(isNegative, i, outputBuffer, flags, fieldWidth, precision, lengthModifier));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width.
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed.
 */
int print_binary(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(outputBuffer);
	UNUSED(flags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(lengthModifier);

	n = va_arg(argList, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

