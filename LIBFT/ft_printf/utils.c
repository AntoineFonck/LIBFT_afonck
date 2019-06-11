#include "../libft.h"

void pad_zero(int nbzero, int fd)
{
	char buf[nbzero];

	ft_memset(buf, '0', nbzero);
	write(fd, buf, nbzero);
}

void pad_space(int nbpad, int fd)
{
	char buf[nbpad];

	ft_memset(buf, ' ', nbpad);
	write(fd, buf, nbpad);
}
