#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned_number - Prints an unsigned number
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed.
 */
int print_unsigned_number(va_list argList, char outputBuffer[],   		/* change prototype */
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(argList, unsigned long int);

	num = convert_size_unsigned(num, lengthModifier);

	if (num == 0)
		outputBuffer[i--] = '0';

	outputBuffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		outputBuffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsigned(0, i, outputBuffer, flags, fieldWidth, precision, lengthModifier));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal_number - Prints an unsigned number in octal notation
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed
 */
int print_octal_number(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(argList, unsigned long int);
	unsigned long int initialNum = num;

	UNUSED(fieldWidth);

	num = convert_size_unsigned(num, lengthModifier);

	if (num == 0)
		outputBuffer[i--] = '0';

	outputBuffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		outputBuffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && initialNum != 0)
		outputBuffer[i--] = '0';

	i++;

	return (write_unsigned(0, i, outputBuffer, flags, fieldWidth, precision, lengthModifier));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal_number - Prints an unsigned number in hexadecimal notation
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal_number(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	return (print_hexadecimal(argList, "0123456789abcdef", outputBuffer,
		flags, 'x', fieldWidth, precision, lengthModifier));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexadecimal_upper - Prints an unsigned number in upper hexadecimal notation
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal_upper(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	return (print_hexadecimal(argList, "0123456789ABCDEF", outputBuffer,
		flags, 'X', fieldWidth, precision, lengthModifier));
}

/************** PRINT HEXADECIMAL NUMBER IN LOWER OR UPPER **************/
/**
 * print_hexadecimal - Prints a hexadecimal number in lower or upper
 * @argList: List of arguments
 * @mapTo: Array of values to map the number to
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @flagChar: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list argList, char mapTo[], char outputBuffer[],
	int flags, char flagChar, int fieldWidth, int precision, int lengthModifier)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(argList, unsigned long int);
	unsigned long int initialNum = num;

	UNUSED(fieldWidth);

	num = convert_size_unsigned(num, lengthModifier);

	if (num == 0)
		outputBuffer[i--] = '0';

	outputBuffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		outputBuffer[i--] = mapTo[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && initialNum != 0)
	{
		outputBuffer[i--] = flagChar;
		outputBuffer[i--] = '0';
	}

	i++;

	return (write_unsigned(0, i, outputBuffer, flags, fieldWidth, precision, lengthModifier));
}

