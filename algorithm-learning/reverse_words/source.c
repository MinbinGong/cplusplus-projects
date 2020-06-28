#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int reverseWords(char str[])
{
    char *buffer;
    int tokenReadPos, wordReadPos, wordEnd, writePos = 0;

    tokenReadPos = strlen(str) - 1;

    buffer = (char *)malloc(tokenReadPos + 2);
    if (!buffer)
    {
        return -1;
    }

    while (tokenReadPos >= 0)
    {
        if (str[tokenReadPos] == ' ')
        {
            buffer[writePos++] == str[tokenReadPos--];
        }
        else
        {
            wordEnd = tokenReadPos;

            while (tokenReadPos >= 0 && str[tokenReadPos] != ' ')
            {
                tokenReadPos--;
            }

            wordReadPos = tokenReadPos + 1;

            while (wordReadPos <= wordEnd)
            {
                buffer[writePos++] = str[wordReadPos++];
            }
        }
    }
    buffer[writePos] = '\0';
    strcpy(str, buffer);

    free(buffer);

    return 1;
}

void reverseWords2(char str[])
{
    int start = 0, end = 0, length;

    length = strlen(str);

    reverseString(str, start, length - 1);

    while (end < length)
    {
        if (str[end] != ' ')
        {
            start = end;

            while (end < length && str[end] != ' ')
            {
                end++;
            }

            end--;
            reverseString(str, start, end);
        }
        end++;
    }
}

void reverseString(char str[], int start, int end)
{
    char temp;
    while (end > start)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}