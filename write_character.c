#include "main.h"

/**
 * write_character - Prints a character
 * @ch: Character to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_character(char ch, char buffer[],
	int flags, int width, int precision, int size)
{ /* The character stored at the left, and padding is on the buffer's right */
	int i = 0;
	char paddingChar = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		paddingChar = '0';

	buffer[i++] = ch;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = paddingChar;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_integer - Prints an integer
 * @isNegative: Indicates if the number is negative.
 * @index: Index of the number in the buffer.
 * @buffer: Buffer array to handle print.
 * @flags: Active flags.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int write_integer(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char paddingChar = ' ', extraChar = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';
	if (isNegative)
		extraChar = '-';
	else if (flags & F_PLUS)
		extraChar = '+';
	else if (flags & F_SPACE)
		extraChar = ' ';

	return (write_number(isNegative, index, buffer, flags,
				width, precision, length, paddingChar, extraChar));
}

/**
 * write_number - Write a number using a buffer
 * @isNegative: Number indicating if the number is negative.
 * @index: Index at which the number starts in the buffer.
 * @buffer: Buffer array.
 * @flags: Flags specifier.
 * @width: Width specifier.
 * @precision: Precision specifier.
 * @length: Length of the number.
 * @paddingChar: Character representing the padding.
 * @extraChar: Character representing the extra character.
 *
 * Return: Number of characters printed.
 */
int write_number(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int length,
	char paddingChar, char extraChar)
{
	int i, paddingStart = 1;

	if (precision == 0 && index == BUFF_SIZE - 2
			&& buffer[index] == '0' && width == 0)
		return (0); /* printf(".0d", 0) - no character is printed */
	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = paddingChar = ' '; /* width is displayed with padding ' ' */
	if (precision > 0 && precision < length)
		paddingChar = ' ';
	while (precision > length)
		buffer[--index] = '0', length++;
	if (extraChar != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = paddingChar;
		buffer[i] = '\0';
		if (flags & F_MINUS && paddingChar == ' ') /*extra char*/
		{
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra char to the left of padding [padding > buffer] */
		{
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	if (extraChar)
		buffer[--index] = extraChar;
	return (write(1, &buffer[index], length));
}

/**
 * write_unsigned - Writes an unsigned number
 * @isNegative: Number indicating if the number is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of characters
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters written.
 */
int write_unsigned(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position index */
	int length = BUFF_SIZE - index - 1, i = 0;
	char paddingChar = ' ';

	UNUSED(isNegative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0); /* printf(".0u", 0) - no character is printed */

	if (precision > 0 && precision < length)
		paddingChar = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = paddingChar;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Assign extra char  [buffer>padding] */
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra char to the left of padding [padding > buffer] */
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * write_pointer_address - Write a memory address
 * @buffer: Array of characters
 * @index: Index at which the number starts in the buffer
 * @length: Length of the number
 * @width: Width specifier
 * @flags: Flags specifier
 * @paddingChar: Character representing the padding
 * @extraChar: Character representing extra character
 * @paddingStart: Index at which padding should start
 *
 * Return: Number of characters written.
 */
int write_pointer_address(char buffer[], int index, int length,
	int width, int flags, char paddingChar, char extraChar, int paddingStart)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = paddingChar;
		buffer[i] = '\0';
		if (flags & F_MINUS && paddingChar == ' ') /*extra char assign*/
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else /* Assign extra char to the left of padding */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extraChar)
		buffer[--index] = extraChar;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
