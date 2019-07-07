#include "libft.h"

int	ft_putwstr_fd(wchar_t *str, int fd)
{
	int	full_len;

	full_len = 0;
	if (str == NULL)
		return (-1);
	while (*str)
	{
		full_len += ft_putwchar_fd(*str, fd);
		str++;
	}
	return (full_len);
}
