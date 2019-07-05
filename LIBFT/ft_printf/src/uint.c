/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:31:06 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/05 12:26:50 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

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
		len += pad_uint_prec(number, flags, fd);
	else
		len += pad_uint_prec(number, flags, fd);
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
	nbpad = (nbpad < 0 ? 0 : nbpad);
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
	}
	while (nbpad > 0)
	{
		ft_putchar_fd(' ', fd);
		nbpad--;
	}
	return (padlen);
}

int	special_zero_u(int fd, t_flags *flags)
{
	int len;

	len = flags->field_width - (PLUS_FLAG || SPACE_FLAG ? 1 : 0);
	if (len < 0)
		len = 0;
	if (((PLUS_FLAG) || (SPACE_FLAG)) && (MIN_FLAG))
	{
		if (PLUS_FLAG)
			ft_putchar_fd('+', fd);
		else if (SPACE_FLAG)
			ft_putchar_fd(' ', fd);
	}
	pad_space(len, fd);
	if (((PLUS_FLAG) || (SPACE_FLAG)) && !(MIN_FLAG))
	{
		if (PLUS_FLAG)
			ft_putchar_fd('+', fd);
		else if (SPACE_FLAG)
			ft_putchar_fd(' ', fd);
		len++;
	}
	if (((PLUS_FLAG) || (SPACE_FLAG)) && (MIN_FLAG))
		len++;
	return (len);
}

int	special_convert_uint(uintmax_t number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (((PREC_FLAG) && flags->precision == 0) && number == 0)
		return (special_zero_u(fd, flags));
	else if (flags->precision || (PREC_FLAG))
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
	if (is_activated(flags) || PREC_FLAG)
		return (special_convert_uint(number, fd, flags));
	else
	{
		ft_uitoa_base(number, 10, fd);
	}
	return (ft_unbrlen(number));
}
