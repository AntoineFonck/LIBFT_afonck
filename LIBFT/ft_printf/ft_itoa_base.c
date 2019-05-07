#include <stdio.h>
#include <stdlib.h>
#include "../libft.h"
#include <unistd.h>

//char *itoa_base(int value, int base)
void	ft_itoaprint_base(unsigned int value, int base)
{
    //static  char buf[50];
	char buf[50];
    char    *ptr;
    int     num;
    int	    ascii_offset;

    ptr = &buf[49];
    *ptr = '\0';
    num = value;
    if (value < 0 && base == 10)
        value *= -1;
    if (value == 0)
        *--ptr = '0' + (value % base);
    while (value != 0)
    {
	ascii_offset = 0;
	if (value % base > 9)
		ascii_offset = 39;
        *--ptr = '0' + ((value % base) + ascii_offset);
	//*--ptr = "0123456789abcdef"[value % base];
        value /= base;
    }
    if (num < 0 && base == 10)
        *--ptr = '-';
    //return (ptr);
    write(1, ptr, ft_strlen(ptr));
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		//printf("%s\n", itoa_base(atoi(argv[1]), atoi(argv[2])));
		ft_itoaprint_base(ft_atoi(argv[1]), ft_atoi(argv[2]));
		printf("\nreal printf hex = %x\n", ft_atoi(argv[1]));
		printf("\nreal printf octal = %o\n", ft_atoi(argv[1]));
	}
	return (0);
}
