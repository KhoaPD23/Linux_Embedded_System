#include "main.h"
#include "strutils.h"

int main(void)
{
    char str1[] = "  Hello World!  ";
    char str2[] = "12345";
    char str3[] = "abcde";

    printf("Chuoi ban dau: '%s'\n", str1);
    str_trim(str1);
    printf("Sau khi trim: '%s'\n", str1);

    str_reverse(str3);
    printf("Chuoi dao nguoc: '%s'\n", str3);

    int number;
    if(str_to_int(str2, &number))
	{
        printf("Chuyen doi '%s' thanh so nguyen: %d\n", str2, number);
    }

	else 
	{
        printf("Khong the chuyen doi '%s' thanh so nguyen.\n", str2);
    }

    return 0;
}
