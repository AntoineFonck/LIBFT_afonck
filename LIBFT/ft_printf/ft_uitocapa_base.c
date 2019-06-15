#include <stdio.h>
#include "../libft.h"

int	ft_uitocapaprint_base(unsigned int value, int base, int fd)
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
			ascii_offset = 7;
		*--ptr = '0' + ((value % base) + ascii_offset);
		value /= base;
	}
	write(fd, ptr, ft_strlen(ptr));
	return (ft_strlen(ptr));
}
