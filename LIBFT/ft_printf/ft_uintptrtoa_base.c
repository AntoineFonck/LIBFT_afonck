#include "../libft.h"
#include "ft_printf.h"

int	ft_uintptrtoaprint_base(uintptr_t value, int base, int fd)
{
	char	buf[50];
	char    *ptr;
	int     num;
	int	    ascii_offset;

	ptr = &buf[50];
	*ptr = '\0';
	num = value;
	//if (value < 0 && base == 10)
	//  value *= -1;
	if (value == 0)
		*--ptr = '0' + (value % base);
	while (value != 0)
	{
		ascii_offset = 0;
		if (value % base > 9)
			ascii_offset =  39;
		*--ptr = '0' + ((value % base) + ascii_offset);
		value /= base;
	}
	//if (num < 0 && base == 10)
	//  *--ptr = '-';
	//return (ptr);
	write(fd, ptr, ft_strlen(ptr));
	return (ft_strlen(ptr));
}

int	ft_uintptrtoalen_base(uintptr_t value, int base, int fd)
{
	char	buf[50];
	char    *ptr;
	int     num;
	int	    ascii_offset;

	ptr = &buf[50];
	*ptr = '\0';
	num = value;
	//if (value < 0 && base == 10)
	//  value *= -1;
	if (value == 0)
		*--ptr = '0' + (value % base);
	while (value != 0)
	{
		ascii_offset = 0;
		if (value % base > 9)
			ascii_offset = 39;
		*--ptr = '0' + ((value % base) + ascii_offset);
		value /= base;
	}
	//if (num < 0 && base == 10)
	//  *--ptr = '-';
	//return (ptr);
	return (ft_strlen(ptr));
}