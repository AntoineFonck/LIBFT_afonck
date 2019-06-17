#include <stdio.h>
#include "../libft.h"

int	ft_uitoaprint_base(uintmax_t value, int base, int fd)
{
	char	buf[50];
	char    *ptr;
	int     num;
	int	    ascii_offset;

	ptr = &buf[49];
	*ptr = '\0';
	num = value;
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
	write(fd, ptr, ft_strlen(ptr));
	return (ft_strlen(ptr));
}

int	ft_uitoalen_base(uintmax_t value, int base)
{
	char	buf[50];
	char    *ptr;
	int     num;
	int	    ascii_offset;

	ptr = &buf[49];
	*ptr = '\0';
	num = value;
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
	return (ft_strlen(ptr));
}