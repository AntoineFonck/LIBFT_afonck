/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:10:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/05 09:30:19 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

//HAVE TO REMOVE AT LEAST 2 FUNCTIONS AND PUT IT IN ANOTHER FILE
void	flags_spec(t_flags *flags, int nbpad, int fd, intmax_t number)
{
	if (!(MIN_FLAG))
		pad_space(nbpad, fd);
	if ((PLUS_FLAG) && number >= 0)
		ft_putchar_fd('+', fd);
	if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG))
		ft_putchar_fd(' ', fd);
}

void	flags_specfloat(t_flags *flags, int nbpad, int fd, double number)
{
	//printf("number = %d\n", 1 / number > 0);
	//printf("HERE nbpad = %d\n", nbpad);
	if (!(MIN_FLAG))
	{
		if ((PLUS_FLAG) && number >= 0 && ZERO_FLAG && (1 / number > 0))
			ft_putchar_fd('+', fd);
		if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG) && ZERO_FLAG && (1 / number > 0))
			ft_putchar_fd(' ', fd);
		if (ZERO_FLAG)
			pad_zero(nbpad, fd);
		else
			pad_space(nbpad, fd);
		if ((PLUS_FLAG) && number >= 0 && !(ZERO_FLAG) && (1 / number > 0))
			ft_putchar_fd('+', fd);
		if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG) && !(ZERO_FLAG) && (1 / number > 0))
			ft_putchar_fd(' ', fd);
	}
	else
	{
		if ((PLUS_FLAG) && number >= 0 && (1 / number > 0))
			ft_putchar_fd('+', fd);
		if ((SPACE_FLAG) && number >= 0 && !(PLUS_FLAG) && (1 / number > 0))
			ft_putchar_fd(' ', fd);
	}
}

int		pad_float_prec(double number, int preclen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;
	int nbrlen;

	nbrlen = ft_floatlen(number, preclen) - (/*number < 0*/!(1 / number > 0) ? 1 : 0) + ((HASH_FLAG)
			&& (PREC_FLAG) && flags->precision == 0);
	nbpad = flags->field_width - (flags->precision >= nbrlen ? flags->precision : nbrlen) - !(1 / number > 0) - ((PLUS_FLAG || SPACE_FLAG) && (1 / number > 0));
	//nbpad = flags->field_width - (flags->precision >= nbrlen ? flags->precision
	//		: nbrlen) + (/*number < 0*/!(1 / number > 0) ? 1 : 0) - (((PLUS_FLAG) || (SPACE_FLAG))
	//			&& /*number >= 0*/(1 / number > 0) ? 1 : 0);
	//ft_printf("FW = %d, prec = %d, nbrlen = %d, weird stuff = %d\n", flags->field_width, flags->precision, nbrlen, !(1 / number > 0));
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= nbrlen ? flags->precision : nbrlen) - nbrlen
		+ ((HASH_FLAG) && (PREC_FLAG) && flags->precision == 0);
	padlen = nbpad + nbzero + (/*number >= 0*/(1 / number > 0) ? (PLUS_FLAG) || (SPACE_FLAG) : 0);
	//ft_printf("nbrlen = %d, nbpad = %d, nbzero = %d, padlen = %d\n", nbrlen, nbpad, nbzero, padlen);
	if (number == 0 && !(1 / number > 0) && (ZERO_FLAG))
		ft_putchar_fd('-', fd);
	flags_specfloat(flags, nbpad, fd, number);
	//pad_zero(nbzero, fd);
	//if (number == 0 && !(1 / number > 0))
	//	ft_putchar_fd(' ', fd);
	if (number == 0 && !(1 / number > 0) && !(ZERO_FLAG))
		ft_putchar_fd('-', fd);
	if (ZERO_FLAG || (number == 0 && !(1 / number > 0)))
		ft_ftoa_fd(ft_absfloat(number), preclen, fd);
	else
		ft_ftoa_fd(number, preclen, fd);
	if ((HASH_FLAG) && (PREC_FLAG) && flags->precision == 0)
		ft_putchar_fd('.', fd);
	if ((MIN_FLAG))
		pad_space(nbpad, fd);
	return (padlen);
}

int		float_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(MIN_FLAG))
	{
		if (!(1 / number > 0) && (ZERO_FLAG) && number != 0)
			ft_putchar_fd('-', fd);
		//if (!(1 / number > 0) && (ZERO_FLAG) && number == 0)
		//	ft_putchar_fd('-', fd);
		len += pad_float_prec(number, preclen, flags, fd);
	}
	else
	{
		if (!(1 / number > 0) && (ZERO_FLAG) && number != 0)
			ft_putchar_fd('-', fd);
		//if (!(1 / number > 0) && (ZERO_FLAG) && number == 0)
		//	ft_putchar_fd('-', fd);
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
		if ((PLUS_FLAG) && (ZERO_FLAG) && (1 / number > 0))//number >= 0)
			ft_putchar_fd('+', fd);
		//if (number < 0 && (ZERO_FLAG))
		//if (!(1 / number > 0) && (ZERO_FLAG) && number != 0)
		//	ft_putchar_fd('-', fd);
		if (!(1 / number > 0) && number == 0)
			ft_putchar_fd('-', fd);
		len += pad_float(number, flags, fd);
		if (!(1 / number > 0) && number != 0)
			ft_putchar_fd('-', fd);
		if ((PLUS_FLAG) && !(ZERO_FLAG) && (1 / number > 0))//number >= 0)
			ft_putchar_fd('+', fd);
		ft_ftoa_fd(ft_absfloat(number), preclen, fd);
	}
	else if ((MIN_FLAG))
	{
		if ((PLUS_FLAG) && (1 / number > 0))//number >= 0)
			ft_putchar_fd('+', fd);
		else if ((SPACE_FLAG) && (1 / number > 0))//number >= 0)
			ft_putchar_fd(' ', fd);
		if (!(1 / number > 0) && number == 0)
			ft_putchar_fd('-', fd);
		ft_ftoa_fd(number, preclen, fd);
		len += pad_float(number, flags, fd);
	}
	return (len);
}

int		pad_float(double number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_floatlen(number, 6);
	if (((PLUS_FLAG) || (SPACE_FLAG)) && (1 / number > 0)) // number >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (/*number >= 0*/(1 / number > 0) ? (PLUS_FLAG) || (SPACE_FLAG) : 0);
	if ((ZERO_FLAG) && !(MIN_FLAG))
	{
		if ((SPACE_FLAG) && !(PLUS_FLAG) && number < 0) //&& !(1 / number > 0))
			ft_putchar_fd(' ', fd);
		pad_zero(nbpad, fd);
		//printf("PADLEN = %d\n", padlen);
		return (padlen);
	}
	if ((SPACE_FLAG) && !(PLUS_FLAG) && (1 / number > 0))// number >= 0)
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
	long double	numberldb;
	double		numberdb;
	int			nblen;

	nblen = 0;
	numberldb = 0;
	numberdb = 0;
	if (BIGL_FLAG)
		numberldb = va_arg(args, long double);
	else
		numberdb = va_arg(args, double);
	if (BIGL_FLAG)
	{
		if (is_activated(flags) || (PREC_FLAG) || (!(1 / numberldb > 0) && numberldb == 0))
			return (special_convert_float(numberldb, fd, flags));
		/*if (!(1 / numberldb > 0) && !(ZERO_FLAG) && numberldb == 0)
		{
			ft_putchar_fd('-', fd);
			nblen++;
		}*/
		nblen += ft_ftoa_fd(numberldb, 6, fd);
	}
	else
	{
		if (is_activated(flags) || (PREC_FLAG) || (!(1 / numberdb > 0) && numberdb == 0))
			return (special_convert_float(numberdb, fd, flags));
		/*
		if (!(1 / numberdb > 0) && !(ZERO_FLAG) && numberdb == 0)
		{
			ft_putchar_fd('-', fd);
			nblen++;
		}*/
		nblen += ft_ftoa_fd(numberdb, 6, fd);
	}
	return (nblen);
}
