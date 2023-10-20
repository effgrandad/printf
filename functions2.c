#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer_value - Prints the value of a pointer variable
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed.
 */
int print_pointer_value(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	char extraCharacter = 0, paddingChar = ' ';
	int index = BUFFER_SIZE - 2, length = 2, paddingStart = 1; /* length=2, for '0x' */
	unsigned long addressValue;
	char mapping[] = "0123456789abcdef";
	void *address = va_arg(argList, void *);

	UNUSED(fieldWidth);
	UNUSED(lengthModifier);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	outputBuffer[BUFFER_SIZE - 1] = '\0';
	UNUSED(precision);

	addressValue = (unsigned long)address;

	while (addressValue > 0)
	{
		outputBuffer[index--] = mapping[addressValue % 16];
		addressValue /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';
	if (flags & F_PLUS)
		extraCharacter = '+', length++;
	else if (flags & F_SPACE)
		extraCharacter = ' ', length++;

	index++;

	return (write_pointer_value(outputBuffer, index, length,
		fieldWidth, flags, paddingChar, extraCharacter, paddingStart));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable_chars - Prints ASCII codes in hexadecimal of non-printable characters
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed.
 */
int print_non_printable_chars(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	int i = 0, offset = 0;
	char *string = va_arg(argList, char *);

	UNUSED(flags);
	UNUSED(fieldWidth);
	UNUSED(precision);
	UNUSED(lengthModifier);

	if (string == NULL)
		return (write(1, "(null)", 6);

	while (string[i] != '\0')
	{
		if (is_printable_character(string[i]))
			outputBuffer[i + offset] = string[i];
		else
			offset += append_hexadecimal_code(string[i], outputBuffer, i + offset);

		i++;
	}

	outputBuffer[i + offset] = '\0';

	return (write(1, outputBuffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reversed_string - Prints a reversed string.
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed.
 */
int print_reversed_string(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	char *str;
	int i, count = 0;

	UNUSED(outputBuffer);
	UNUSED(flags);
	UNUSED(fieldWidth);
	UNUSED(lengthModifier);

	str = va_arg(argList, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char character = str[i];

		write(1, &character, 1);
		count++;
	}
	return count;
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13_string - Print a string in ROT13.
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @fieldWidth: Get width
 * @precision: Precision specification
 * @lengthModifier: Size specifier
 * Return: Number of characters printed.
 */
int print_rot13_string(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(argList, char *);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == str[i])
			{
				x = output[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!input[j])
		{
			x = str[i];
			write(1, &x, 1);
			count+= 1;
		}
	}
	return count;
}

