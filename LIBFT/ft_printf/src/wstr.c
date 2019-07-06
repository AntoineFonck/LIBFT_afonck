/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:47:58 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/06 14:48:39 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_wstrlen(wchar_t *wstr)
{
	int full_len;

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

int	ft_putwstr_fd(wchar_t *str, int fd)
{
	int full_len;

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
