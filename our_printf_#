#include "main.h"

void print_buffer(char outputBuffer[], int *bufferIndex);

/**
 * our_printf_# - Custom printf function
 * @formatString: Format string.
 * Return: Number of characters printed.
 */
int our_printf_#(const char *formatString, ...) 
{
    int index, totalPrinted = 0, charsPrinted = 0;
    int flags, fieldWidth, precision, lengthModifier, bufferIndex = 0;
    va_list argList;
    char outputBuffer[BUFFER_SIZE];

    if (formatString == NULL)
        return (-1);

    va_start(argList, formatString);

    for (index = 0; formatString && formatString[index] != '\0'; index++)
    {
        if (formatString[index] != '%')
        {
            outputBuffer[bufferIndex++] = formatString[index];
            if (bufferIndex == BUFFER_SIZE)
                print_buffer(outputBuffer, &bufferIndex);  /* we call on putcharr function:we can compile our own putchar file */
            charsPrinted++;
        }
        else
        {
            print_buffer(outputBuffer, &bufferIndex);
            flags = get_flags(formatString, &index);
            fieldWidth = get_width(formatString, &index, argList);
            precision = get_precision(formatString, &index, argList);
            lengthModifier = get_length_modifier(formatString, &index);
            ++index;
            charsPrinted = handle_print(formatString, &index, argList, outputBuffer,
                                        flags, fieldWidth, precision, lengthModifier);
            if (charsPrinted == -1)
                return (-1);
            totalPrinted += charsPrinted;
        }
    }
}

