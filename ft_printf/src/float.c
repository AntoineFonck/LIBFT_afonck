/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:10:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 16:39:28 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		float_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->on & MIN))
	{
		if (!(1 / number > 0) && (flags->on & ZERO) && number != 0)
			ft_putchar_fd('-', fd);
		len += pad_float_prec(number, preclen, flags, fd);
	}
	else
	{
		if (!(1 / number > 0) && (flags->on & ZERO) && number != 0)
			ft_putchar_fd('-', fd);
		len += pad_float_prec(number, preclen, flags, fd);
	}
	return (len);
}

int		float_no_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->on & MIN))
	{
		if ((flags->on & PLUS) && (flags->on & ZERO) && (1 / number > 0))
			ft_putchar_fd('+', fd);
		if (!(1 / number > 0) && number == 0)
			ft_putchar_fd('-', fd);
		len += pad_float(number, flags, fd);
		if (!(1 / number > 0) && number != 0)
			ft_putchar_fd('-', fd);
		if ((flags->on & PLUS) && !(flags->on & ZERO) && (1 / number > 0))
			ft_putchar_fd('+', fd);
		ft_ftoa_fd(ft_absfloat(number), preclen, fd);
		return (len);
	}
	if ((flags->on & PLUS) && (1 / number > 0))
		ft_putchar_fd('+', fd);
	else if ((flags->on & SPACE) && (1 / number > 0))
		ft_putchar_fd(' ', fd);
	if (!(1 / number > 0) && number == 0)
		ft_putchar_fd('-', fd);
	ft_ftoa_fd(number, preclen, fd);
	return (len += pad_float(number, flags, fd));
}

int		pad_float(double number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_w - ft_floatlen(number, 6);
	if (((flags->on & PLUS) || (flags->on & SPACE)) && (1 / number > 0))
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + ((1 / number > 0) ? (flags->on & PLUS) \
		|| (flags->on & SPACE) : 0);
	if ((flags->on & ZERO) && !(flags->on & MIN))
	{
		if ((flags->on & SPACE) && !(flags->on & PLUS) && number < 0)
			ft_putchar_fd(' ', fd);
		pad_zero(nbpad, fd);
		return (padlen);
	}
	if ((flags->on & SPACE) && !(flags->on & PLUS) && (1 / number > 0))
		ft_putchar_fd(' ', fd);
	pad_space(nbpad, fd);
	return (padlen);
}

int		special_convert_float(double number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->prec)
	{
		full_len += float_precision(number, flags->prec, fd, flags);
		return (full_len + ft_floatlen(number, flags->prec));
	}
	else if (!flags->prec && (flags->on & PREC))
	{
		full_len += float_precision(number, 0, fd, flags);
		return (full_len + ft_floatlen(number, 0));
	}
	else
	{
		full_len += float_no_precision(number, 6, fd, flags);
		return (full_len + ft_floatlen(number, 6));
	}
}

int		convert_float(va_list args, int fd, t_flags *flags)
{
	long double	numberldb;
	double		numberdb;
	int			nblen;

	nblen = 0;
	numberldb = 0;
	numberdb = 0;
	if (flags->on & BIGL)
		numberldb = va_arg(args, long double);
	else
		numberdb = va_arg(args, double);
	if (flags->on & BIGL)
	{
		if (is_activated(flags) || (flags->on & PREC) ||
				(!(1 / numberldb > 0) && numberldb == 0))
			return (special_convert_float(numberldb, fd, flags));
		nblen += ft_ftoa_fd(numberldb, 6, fd);
		return (nblen);
	}
	if (is_activated(flags) || (flags->on & PREC) ||
			(!(1 / numberdb > 0) && numberdb == 0))
		return (special_convert_float(numberdb, fd, flags));
	nblen += ft_ftoa_fd(numberdb, 6, fd);
	return (nblen);
}
