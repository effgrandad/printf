#include "main.h"

/**
 * is_character_printable - Evaluates if a character is printable
 * @ch: Character to be evaluated.
 *
 * Return: 1 if ch is printable, 0 otherwise
 */
int is_character_printable(char ch)
{
	if (ch >= 32 && ch < 127)
		return (1);

	return (0);
}

/**
 * append_hexadecimal_code - Append ASCII in hexadecimal code to buffer
 * @buffer: Array of characters.
 * @index: Index at which to start appending.
 * @asciiCode: ASCII code.
 * Return: Always 3
 */
int append_hexadecimal_code(char asciiCode, char buffer[], int index)
{
	char hexMap[] = "0123456789ABCDEF";
	/* The hexadecimal format code is always 2 digits long */
	if (asciiCode < 0)
		asciiCode *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = hexMap[asciiCode / 16];
	buffer[index] = hexMap[asciiCode % 16];

	return (3);
}

/**
 * is_digit_character - Verifies if a character is a digit
 * @ch: Character to be evaluated
 *
 * Return: 1 if ch is a digit, 0 otherwise
 */
int_is_digit_character(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	return (0);
}

/**
 * cast_number_to_specified_size - Casts a number to the specified size
 * @number: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of number
 */
long int cast_number_to_specified_size(long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * cast_unsigned_number_specified_size - Cast unsigned number to specified size
 * @number: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of number
 */
long int cast_unsigned_number_to_specified_size(unsigned long int number,
		int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}
