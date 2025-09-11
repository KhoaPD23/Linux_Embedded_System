#include "main.h"
#include "strutils.h"

// Ham dao nguoc chuoi
void str_reverse(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i)
	{
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Ham loai bo khoang trang dau va cuoi
void str_trim(char *str)
{
    int start = 0, end = strlen(str) - 1;

    while(isspace((unsigned char)str[start]))
    {
    	start++;
	}
	
    while(end >= start && isspace((unsigned char)str[end]))
    {
    	end--;
	}

    int i = 0;
    while(start <= end)
	{
        str[i++] = str[start++];
    }
    str[i] = '\0';
}

// Ham chuyen chuoi thanh so nguyen an toan
bool str_to_int(char *str, int *out)
{
    char *endptr;
    errno = 0;
    int val = strtol(str, &endptr, 10);

    if(errno != 0 || endptr == str || *endptr != '\0' || val < INT_MIN || val > INT_MAX)
	{
        return false;
    }

    *out = val;
    return true;
}
