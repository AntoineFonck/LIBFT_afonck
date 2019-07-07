#include "libft.h"

int	ft_wstrlen(wchar_t *wstr)
{
	int	full_len;

	full_len = 0;
	if (wstr == NULL)
		return (-1);
	while (*wstr)
	{
		full_len += ft_wcharlen(ft_nbits(*wstr));
		wstr++;
	}
	return (full_len);
}
