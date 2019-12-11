/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:31:06 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 16:01:54 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	uint_precision(uintmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->on & MIN))
		len += pad_uint_prec(number, flags, fd);
	else
		len += pad_uint_prec(number, flags, fd);
	return (len);
}

int	uint_no_precision(uintmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->on & MIN))
	{
		len += pad_uint(number, flags, fd);
		ft_uitoa_base(number, 10, fd);
	}
	else
	{
		ft_uitoa_base(number, 10, fd);
		len += pad_uint(number, flags, fd);
	}
	return (len);
}

int	special_zero_u(int fd, t_flags *flags)
{
	int len;

	len = flags->field_w - (flags->on & PLUS || flags->on & SPACE ? 1 : 0);
	if (len < 0)
		len = 0;
	if (((flags->on & PLUS) || (flags->on & SPACE)) && (flags->on & MIN))
	{
		if (flags->on & PLUS)
			ft_putchar_fd('+', fd);
		else if (flags->on & SPACE)
			ft_putchar_fd(' ', fd);
	}
	pad_space(len, fd);
	if (((flags->on & PLUS) || (flags->on & SPACE)) && !(flags->on & MIN))
	{
		if (flags->on & PLUS)
			ft_putchar_fd('+', fd);
		else if (flags->on & SPACE)
			ft_putchar_fd(' ', fd);
		len++;
	}
	if (((flags->on & PLUS) || (flags->on & SPACE)) && (flags->on & MIN))
		len++;
	return (len);
}

int	special_convert_uint(uintmax_t number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (((flags->on & PREC) && flags->prec == 0) && number == 0)
		return (special_zero_u(fd, flags));
	else if (flags->prec || (flags->on & PREC))
		full_len += uint_precision(number, fd, flags);
	else
		full_len += uint_no_precision(number, fd, flags);
	return (full_len + ft_unbrlen(number));
}

int	convert_uint(va_list args, int fd, t_flags *flags)
{
	uintmax_t number;

	if (flags->on & HH)
		number = (unsigned char)va_arg(args, unsigned int);
	else if (flags->on & H)
		number = (unsigned short)va_arg(args, unsigned int);
	else if (flags->on & L)
		number = (unsigned long)va_arg(args, unsigned long);
	else if (flags->on & LL)
		number = (unsigned long long)va_arg(args, unsigned long long);
	else
		number = va_arg(args, unsigned int);
	if (is_activated(flags) || flags->on & PREC)
		return (special_convert_uint(number, fd, flags));
	else
	{
		ft_uitoa_base(number, 10, fd);
	}
	return (ft_unbrlen(number));
}
