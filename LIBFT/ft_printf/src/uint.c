/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:31:06 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/27 18:11:13 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../libft.h"
#include "ft_printf.h"

//POSSIBLE TO DO A FILE ONLY FOR PRECISION 
int	pad_uint_prec(uintmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - (flags->precision >= ft_unbrlen(number)
			? flags->precision : ft_unbrlen(number));
	if (((PLUS_FLAG) || (SPACE_FLAG)))
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= ft_unbrlen(number) ?
			flags->precision : ft_unbrlen(number)) -
			ft_unbrlen(number);
	padlen = nbpad + nbzero + ((PLUS_FLAG) || (SPACE_FLAG));
	if (!(MIN_FLAG))
		pad_space(nbpad, fd);
	pad_zero(nbzero, fd);
	ft_uitoa_base(number, 10, fd);
	if (MIN_FLAG)
		pad_space(nbpad, fd);
	return (padlen);
}

int	uint_precision(uintmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(MIN_FLAG))
	{
		len += pad_uint_prec(number, flags, fd);
		//if ((PLUS_FLAG) && flags->field_width > flags->precision && number >= 0)
		//	ft_putchar_fd('+', fd);
	}
	else
	{
	//if ((PLUS_FLAG) && number > 0)
	//ft_putchar_fd('+', fd);
		len += pad_uint_prec(number, flags, fd);
	}
	return (len);
}

int	uint_no_precision(uintmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(MIN_FLAG))
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

int	pad_uint(uintmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_unbrlen(number);
	//printf("nbrlen is %d\n", ft_unbrlen(number));
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad;
	if ((ZERO_FLAG) && !(MIN_FLAG))
	{
		if ((SPACE_FLAG) && !(PLUS_FLAG))
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

int	special_convert_uint(uintmax_t number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision)
		full_len += uint_precision(number, fd, flags);
	else
		full_len += uint_no_precision(number, fd, flags);
	return (full_len + ft_unbrlen(number));
}

int	convert_uint(va_list args, int fd, t_flags *flags)
{
	uintmax_t number;

	if (HH_FLAG)
		number = (unsigned char)va_arg(args, unsigned int);
	else if (H_FLAG)
		number = (unsigned short)va_arg(args, unsigned int);
	else if (L_FLAG)
		number = (unsigned long)va_arg(args, unsigned long);
	else if (LL_FLAG)
		number = (unsigned long long)va_arg(args, unsigned long long);
	else
		number = va_arg(args, unsigned int);
	if (is_activated(flags))
		return (special_convert_uint(number, fd, flags));
	ft_uitoa_base(number, 10, fd);
	return (ft_unbrlen(number));
}
