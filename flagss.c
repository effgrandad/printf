#include "main.h"

/**
 * calculate_active_flags - Calculates active flags
 * @formatString: Formatted string in which to print the arguments
 * @currentIndex: Current index in the format string
 * Return: Active flags
 */
int calculate_active_flags(const char *formatString, int *currentIndex)
{
    int j, currentIdx;
    int activeFlags = 0;
    const char FLAGS_CHARS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (currentIdx = *currentIndex + 1; formatString[currentIdx] != '\0'; currentIdx++)
    {
        for (j = 0; FLAGS_CHARS[j] != '\0'; j++)
        {
            if (formatString[currentIdx] == FLAGS_CHARS[j])
            {
                activeFlags |= FLAGS_ARRAY[j];
                break;
            }
        }

        if (FLAGS_CHARS[j] == 0)
        {
            break;
        }
    }

    *currentIndex = currentIdx - 1;

    return activeFlags;
}
