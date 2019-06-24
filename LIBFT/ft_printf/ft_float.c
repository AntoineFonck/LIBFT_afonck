/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c     	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:56:56 by afonck            #+#    #+#             */
/*   Updated: 2019/06/24 14:24:14 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

void	flags_spec(t_flags *flags, int nbpad, int fd, intmax_t number)
{
	if (!(MIN_FLAG))
		pad_space(nbpad, fd);
	if ((PLUS_FLAG) && number >= 0)
		ft_putchar_fd('+', fd);
	if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG))
		ft_putchar_fd(' ', fd);
}

int		pad_float_prec(double number, int preclen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;
	int nbrlen;

	nbrlen = ft_floatlen(number, preclen) - (number < 0 ? 1 : 0);
	nbpad = flags->field_width - (flags->precision >= nbrlen ? flags->precision
		: nbrlen) - (number < 0 ? 1 : 0) - (((PLUS_FLAG) || (SPACE_FLAG)) && number >= 0 ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= nbrlen ? flags->precision : nbrlen) - nbrlen;
	padlen = nbpad + nbzero + (number >= 0 ? (PLUS_FLAG) || (SPACE_FLAG) : 0);
	flags_spec(flags, nbpad, fd, number);
	pad_zero(nbzero, fd);
	ft_ftoa(number, preclen, fd);
	if ((MIN_FLAG))
		pad_space(nbpad, fd);
	return (padlen);
}

int		float_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(MIN_FLAG))
		len += pad_float_prec(number, preclen, flags, fd);
	else
	{
		if (number < 0 && (ZERO_FLAG))
			ft_putchar_fd('-', fd);
		len += pad_float_prec(number, preclen, flags, fd);
	}
	return (len);
}

int		float_no_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(MIN_FLAG))
	{
		if ((PLUS_FLAG) && (ZERO_FLAG) && number >= 0)
			ft_putchar_fd('+', fd);
		if (number < 0 && (ZERO_FLAG))
			ft_putchar_fd('-', fd);
		len += pad_float(number, flags, fd);
		if ((PLUS_FLAG) && !(ZERO_FLAG) && number >= 0)
			ft_putchar_fd('+', fd);
		ft_ftoa(number, preclen, fd);
	}
	else if ((MIN_FLAG))
	{
		if ((PLUS_FLAG) && number >= 0)
			ft_putchar_fd('+', fd);
		else if ((SPACE_FLAG) && number >= 0)
			ft_putchar_fd(' ', fd);
		ft_ftoa(number, preclen, fd);
		len += pad_float(number, flags, fd);
	}
	return (len);
}

int		pad_float(double number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_floatlen(number, 6);
	if (((PLUS_FLAG) || (SPACE_FLAG)) && number >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (number >= 0 ? (PLUS_FLAG) || (SPACE_FLAG) : 0);
	if ((ZERO_FLAG) && !(MIN_FLAG))
	{
		if ((SPACE_FLAG) && !(PLUS_FLAG) && number >= 0)
			ft_putchar_fd(' ', fd);
		pad_zero(nbpad, fd);
		//printf("PADLEN = %d\n", padlen);
		return (padlen);
	}
	if ((SPACE_FLAG) && !(PLUS_FLAG) && number >= 0)
		ft_putchar_fd(' ', fd);
	pad_space(nbpad, fd);
	//if (number < 0 && !(MIN_FLAG))
	//	ft_putchar_fd('-', fd);
	//printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int		special_convert_float(double number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision)
	{
		full_len += float_precision(number, flags->precision, fd, flags);
		return (full_len + ft_floatlen(number, flags->precision));
	}
	else if (!flags->precision && (PREC_FLAG))
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
	double	number;
	int		nblen;

	nblen = 0;
	number = va_arg(args, double);
	if (is_activated(flags) || (PREC_FLAG))
		return (special_convert_float(number, fd, flags));
	nblen += ft_ftoa(number, 6, fd);
	return (nblen);
}
