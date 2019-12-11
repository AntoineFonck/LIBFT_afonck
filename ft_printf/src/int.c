/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:06:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 16:54:19 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	int_no_precision(intmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->on & MIN))
	{
		if ((flags->on & PLUS) && (flags->on & ZERO) && number >= 0)
			ft_putchar_fd('+', fd);
		if (number < 0 && (flags->on & ZERO))
			ft_putchar_fd('-', fd);
		len += pad_int(number, flags, fd);
		if ((flags->on & PLUS) && !(flags->on & ZERO) && number >= 0)
			ft_putchar_fd('+', fd);
		ft_putnbr_fd(ft_absolute(number), fd);
		return (len);
	}
	if ((flags->on & PLUS) && number >= 0)
		ft_putchar_fd('+', fd);
	else if ((flags->on & SPACE) && number >= 0)
		ft_putchar_fd(' ', fd);
	else if (number == -9223372036854775807 - 1)
		ft_putchar_fd('-', fd);
	ft_putnbr_fd(number, fd);
	len += pad_int(number, flags, fd);
	return (len);
}

int	pad_int(intmax_t nb, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_w - ft_nbrlen(nb);
	if (((flags->on & PLUS) || (flags->on & SPACE)) && nb >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (nb >= 0 ? (flags->on & PLUS) || (flags->on & SPACE) : 0);
	if ((flags->on & ZERO) && !(flags->on & MIN) && !((flags->on & PREC) \
		&& (flags->prec == 0)))
	{
		if ((flags->on & SPACE) && !(flags->on & PLUS) && nb >= 0)
			ft_putchar_fd(' ', fd);
		pad_zero(nbpad, fd);
		return (padlen);
	}
	if ((flags->on & SPACE) && !(flags->on & PLUS) && !(flags->on & MIN) \
		&& nb >= 0)
		ft_putchar_fd(' ', fd);
	pad_space(nbpad, fd);
	if (nb < 0 && !(flags->on & MIN))
		ft_putchar_fd('-', fd);
	return (padlen);
}

int	special_zero(int fd, t_flags *flags)
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

int	special_convert_int(intmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (((flags->on & PREC) && flags->prec == 0) && number == 0)
		return (special_zero(fd, flags));
	else if (flags->prec || (flags->on & PREC))
	{
		if (!(flags->on & MIN))
			len += pad_int_prec(number, flags, fd);
		else
			len += pad_int_prec(number, flags, fd);
	}
	else
		len += int_no_precision(number, fd, flags);
	return (len + ft_nbrlen(number));
}

int	convert_int(va_list args, int fd, t_flags *flags)
{
	intmax_t number;

	if (flags->on & HH)
		number = (signed char)va_arg(args, int);
	else if (flags->on & H)
		number = (short)va_arg(args, int);
	else if (flags->on & L)
		number = va_arg(args, long);
	else if (flags->on & LL)
		number = va_arg(args, long long);
	else
		number = va_arg(args, int);
	if (is_activated(flags) || flags->on & PREC)
		return (special_convert_int(number, fd, flags));
	else
	{
		if (number == -9223372036854775807 - 1)
			ft_putchar_fd('-', fd);
		ft_putnbr_fd(number, fd);
	}
	return (ft_nbrlen(number));
}
