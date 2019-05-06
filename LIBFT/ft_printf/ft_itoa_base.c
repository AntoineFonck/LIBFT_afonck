#include <stdio.h>
#include <stdlib.h>

char *itoa_base(int value, int base)
{
    static  char buf[50];
    char    *ptr;
    int     num;
    //int	    ascii_offset;

    ptr = &buf[49];
    *ptr = '\0';
    num = value;
    if (value < 0 && base == 10)
        value *= -1;
    if (value == 0)
        *--ptr = '0' + (value % base);
    while (value != 0)
    {
	//ascii_offset = 0;
	//if (value % base > 9)
	//	ascii_offset = 39;
        //*--ptr = '0' + ((value % base) + ascii_offset);
	*--ptr = "0123456789abcdef"[value % base];
        value /= base;
    }
    if (num < 0 && base == 10)
        *--ptr = '-';
    return (ptr);
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("%s\n", itoa_base(atoi(argv[1]), atoi(argv[2])));
	}
	return (0);
}
