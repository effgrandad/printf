#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int our_printf(const char *formatString, ...);
int handle_print_argument(const char *formatString, int *currentIndex, va_list argList, char outputBuffer[],
	int activeFlags, int fieldWidth, int precision, int castSize);

/****************** FUNCTIONS ******************/

		/*c_functions[functions.c]*/
int print_character(va_list argList, char outputBuffer[],      
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_string(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_percent(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_integer(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_binary(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier)

		/*c_function_one[functions1.c]*/
int print_unsigned_number(va_list argList, char outputBuffer[],   		
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_octal_number(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_hexadecimal_number(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_hexadecimal(va_list argList, char mapTo[], char outputBuffer[],
	int flags, char flagChar, int fieldWidth, int precision, int lengthModifier);
int print_hexadecimal_upper(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);

		/*c_functions_2[functions2.c]*/
int print_pointer_value(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_non_printable_chars(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_reversed_string(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);
int print_rot13_string(va_list argList, char outputBuffer[],
	int flags, int fieldWidth, int precision, int lengthModifier);

		/*active flags[]get_flags*/
int calculate_active_flags(const char *formatString, int *currentIndex);

		/*precise*/
int calculate_precision(const char *formatString, int *currentIndex, va_list argList);
		/*get width*/
int_get_width(constant char *formatString, int *currentIndex, va_list argList);

		/*size*/
int calculate_cast_size(const char *formatString, int *currentIndex);

		/*utils*/
int is_character_printable(char ch);
int append_hexadecimal_code(char asciiCode, char buffer[], int index);
int_is_digit_character(char ch);
long int cast_number_to_specified_size(long int number, int size);
long int cast_unsigned_number_to_specified_size(unsigned long int number, int size);

		/*handlers_c_writer*/
int write_character(char ch, char buffer[],
	int flags, int width, int precision, int size);
int write_integer(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int length, char paddingChar, char extraChar);
int write_unsigned(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int size);
int write_pointer_address(char buffer[], int index, int length,
	int width, int flags, char paddingChar, char extraChar, int paddingStart);

#endif /* MAIN_H */

