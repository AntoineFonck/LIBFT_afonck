/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:06:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/24 11:53:18 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int	pad_int_prec(intmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;
	int nbrlen;

	nbrlen = ft_nbrlen(number) - (number < 0 ? 1 : 0);
	nbpad = flags->field_width - (flags->precision >= nbrlen ? flags->precision : nbrlen) \
		- (number < 0 ? 1 : 0) - (((flags->state & PLUS) || (flags->state & SPACE)) && number >= 0 ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= nbrlen ? flags->precision : nbrlen) - nbrlen;
	padlen = nbpad + nbzero + (number >= 0 ? (flags->state & PLUS) || (flags->state & SPACE) : 0);
	if (!(flags->state & MINUS))
		pad_space(nbpad, fd);
	if ((flags->state & PLUS) && number >= 0)
		ft_putchar_fd('+', fd);
	if ((flags->state & SPACE) && number >= 0 && !(flags->state & PLUS))
		ft_putchar_fd(' ', fd);
	if (number < 0)
		ft_putchar_fd('-', fd);
	pad_zero(nbzero, fd);
	ft_putnbr_fd(ft_absolute(number), fd);
	if ((flags->state & MINUS))
		pad_space(nbpad, fd);
	return (padlen);
}

int	int_precision(intmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->state & MINUS))
	{
		len += pad_int_prec(number, flags, fd);
	}
	else
	{
		if (number < 0 && (flags->state & ZERO))
			ft_putchar_fd('-', fd);
		len += pad_int_prec(number, flags, fd);
	}
	return (len);
}

int	int_no_precision(intmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->state & MINUS))
	{
		if ((flags->state & PLUS) && (flags->state & ZERO) && number >= 0)
			ft_putchar_fd('+', fd);
		if (number < 0 && (flags->state & ZERO))
			ft_putchar_fd('-', fd);
		len += pad_int(number, flags, fd);
		if ((flags->state & PLUS) && !(flags->state & ZERO) && number >= 0)
			ft_putchar_fd('+', fd);
		ft_putnbr_fd(ft_absolute(number), fd);
		//printf("WTF NUMBER = %jd\n", ft_absolute(number));
	}
	else if ((flags->state & MINUS))
	{
		if ((flags->state & PLUS) && number >= 0)
			ft_putchar_fd('+', fd);
		else if ((flags->state & SPACE) && number >= 0)
			ft_putchar_fd(' ', fd);
		ft_putnbr_fd(number, fd);
		len += pad_int(number, flags, fd);
	}
	return (len);
}

int	pad_int(intmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_nbrlen(number);
	if (((flags->state & PLUS) || (flags->state & SPACE)) && number >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (number >= 0 ? (flags->state & PLUS) || (flags->state & SPACE) : 0);
	if ((flags->state & ZERO) && !(flags->state & MINUS))
	{
		if ((flags->state & SPACE) && !(flags->state & PLUS) && number >= 0)
			ft_putchar_fd(' ', fd);
		pad_zero(nbpad, fd);
		printf("PADLEN = %d\n", padlen);
		return (padlen);
	}
	if ((flags->state & SPACE) && !(flags->state & PLUS) && number >= 0)
		ft_putchar_fd(' ', fd);
	pad_space(nbpad, fd);
	if (number < 0 && !(flags->state & MINUS))
		ft_putchar_fd('-', fd);
	printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int	special_convert_int(intmax_t number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision)
		full_len += int_precision(number, fd, flags);
	else
		full_len += int_no_precision(number, fd, flags);
	return (full_len + ft_nbrlen(number));
}

int	convert_int(va_list args, int fd, t_flags *flags)
{
	intmax_t number;

	if (flags->state & HH)
		number = (signed char)va_arg(args, int);
	else if (flags->state & H)
		number = (short)va_arg(args, int);
	else if (flags->state & L)
		number = va_arg(args, long);
	else if (flags->state & LL)
		number = va_arg(args, long long);
	else
		number = va_arg(args, int);
	if (is_activated(flags))
		return (special_convert_int(number, fd, flags));
	ft_putnbr_fd(number, fd);
	return (ft_nbrlen(number));
}
