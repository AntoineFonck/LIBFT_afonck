/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:29:53 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/05 13:35:46 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_str(int number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - number;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad;
	if ((ZERO_FLAG) && !(MIN_FLAG))
	{
		pad_zero(nbpad, fd);
		return (padlen);
	}
	pad_space(nbpad, fd);
	return (padlen);
}

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

int	special_convert_wstring(wchar_t *s, int len, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (MIN_FLAG)
	{
		if (len > 0)
			ft_putwstr_fd(s, fd);
		full_len += pad_str(len, flags, fd);
		return (full_len + len);
	}
	full_len += pad_str(len, flags, fd);
	if (len > 0)
		ft_putwstr_fd(s, fd);
	return (full_len + len);
}

int	special_convert_string(char *s, int len, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision < len && flags->precision)
		len = flags->precision;
	else if (!flags->precision && (PREC_FLAG))
		len = 0;
	if (MIN_FLAG)
	{
		if (len > 0)
			write(fd, s, len);
		full_len += pad_str(len, flags, fd);
		return (full_len + len);
	}
	if (PLUS_FLAG)
	{
		full_len += pad_str(len, flags, fd);
		if (len > 0)
			write(fd, s, len);
		return (full_len + len);
	}
	full_len += pad_str(len, flags, fd);
	if (len > 0)
		write(fd, s, len);
	return (full_len + len);
}

int	convert_wstring(va_list args, int fd, t_flags *flags)
{
	wchar_t	*s;
	int		len;

	s = va_arg(args, wchar_t *);
	len = ft_wstrlen(s);
	if (is_activated(flags))
		return (special_convert_wstring(s, len, fd, flags));
	ft_putwstr_fd(s, fd);
	return (len);
}

int	convert_string(va_list args, int fd, t_flags *flags)
{
	char	*s;
	int		len;

	if (L_FLAG)
		return (convert_wstring(args, fd, flags));
	s = va_arg(args, char *);
	len = ft_strlen(s);
	if (is_activated(flags) || (PREC_FLAG))
		return (special_convert_string(s, len, fd, flags));
	write(fd, s, len);
	return (len);
}
