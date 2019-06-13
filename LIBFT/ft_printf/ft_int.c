/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:06:33 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/13 15:56:06 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int pad_int_prec(int number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - (flags->precision >= ft_nbrlen(number) ? flags->precision : ft_nbrlen(number)) - (number < 0 ? 1 : 0);
	if ((flags->plus || flags->space) && number >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= ft_nbrlen(number) ? flags->precision : ft_nbrlen(number)) - ft_nbrlen(number) + (number < 0 ? 1 : 0);
	padlen = nbpad + nbzero + (number >= 0 ? flags->plus || flags->space : 0);
	printf("nbpad=%d, nbzero=%d, padlen=%d\n", nbpad, nbzero, padlen);
	if (!flags->minus)
		pad_space(nbpad, fd);
	if (flags->plus && number >= 0)
		ft_putchar_fd('+', fd);
	if (flags->space && number >= 0 && !flags->plus)
		ft_putchar_fd(' ', fd);
	if (number < 0 && !flags->minus)
		ft_putchar_fd('-', fd);
	pad_zero(nbzero, fd);
	ft_putnbr_fd(ft_absolute(number), fd);
	if (flags->minus)
		pad_space(nbpad, fd);
	return (padlen);
}

int int_precision(int number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!flags->minus)
	{
		len += pad_int_prec(number, flags, fd);
		//if (flags->plus && flags->field_width > flags->precision && number >= 0)
		//	ft_putchar_fd('+', fd);
	}
	else
	{
		//if (flags->plus && number > 0)
		//	ft_putchar_fd('+', fd);
		if (number < 0)
			ft_putchar_fd('-', fd);
		len += pad_int_prec(number, flags, fd);
	}
	return (len);
}

int int_no_precision(int number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!flags->minus)
	{
		if (flags->plus && flags->zero && number >= 0)
			ft_putchar_fd('+', fd);
		if (number < 0)
			ft_putchar_fd('-', fd);
		len += pad_int(number, flags, fd);
		if (flags->plus && !flags->zero && number >= 0)
			ft_putchar_fd('+', fd);
		ft_putnbr_fd(ft_absolute(number), fd);
	}
	else
	{
		if (flags->plus && number >= 0)
			ft_putchar_fd('+', fd);
		else if (flags->space && number >= 0)
			ft_putchar_fd(' ', fd);
		ft_putnbr_fd(number, fd);
		len += pad_int(number, flags, fd);
	}
	return (len);
}

int pad_int(int number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_nbrlen(number);
	if ((flags->plus || flags->space) && number >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (number >= 0 ? flags->plus || flags->space : 0);
	if (flags->zero && !flags->minus)
	{
		if (flags->space && !flags->plus)
		{
			ft_putchar_fd(' ', fd);
			nbpad--;
		}
		while (nbpad > 0)
		{
			ft_putchar_fd('0', fd);
			nbpad--;
		}
		return (padlen);
	}
	while (nbpad > 0)
	{
		ft_putchar_fd(' ', fd);
		nbpad--;
	}
	//printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int special_convert_int(int number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision)
		full_len += int_precision(number, fd, flags);
	else
		full_len += int_no_precision(number, fd, flags);
	return (full_len + ft_nbrlen(number));
}

int convert_int(va_list args, int fd, t_flags *flags)
{
	int number;

	number = va_arg(args, int);
	if (is_activated(flags))
		return (special_convert_int(number, fd, flags));
	ft_putnbr_fd(number, fd);
	return (ft_nbrlen(number));
}