/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:00:21 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/27 18:00:16 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

// CAREFUL ABOUT NBPAD STUFF:D
int	pad_oct_prec_min(int octlen, t_flags *flags, int fd, uintmax_t oct)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= octlen ? flags->precision : octlen) -
		(flags->precision <= octlen ? (HASH_FLAG) : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= octlen ? flags->precision : octlen) - octlen;
	padlen = nbpad + nbzero +
		((HASH_FLAG) && flags->precision <= octlen ? 1 : 0);
	if ((HASH_FLAG) && flags->precision <= octlen)
		write(fd, "0", 1);
	pad_zero(nbzero, fd);
	ft_uitoa_base(oct, 8, fd);
	if (flags->precision < flags->field_width)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_oct_prec(int octlen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= octlen ? flags->precision : octlen) -
		(flags->precision <= octlen ? (HASH_FLAG) : 0);
	nbpad = (nbpad < 0 ? 0 : nbpad);
	//if (nbpad < 0)
	//	nbpad = 0;
	nbzero = (flags->precision >= octlen ? flags->precision : octlen) - octlen;
	padlen = nbpad + nbzero +
		((HASH_FLAG) && flags->precision <= octlen ? 1 : 0);
	if (flags->precision < flags->field_width)
	{
		pad_space(nbpad, fd);
		if ((HASH_FLAG) && flags->precision <= octlen)
			write(fd, "0", 1);
		pad_zero(nbzero, fd);
	}
	else
	{
		if ((HASH_FLAG) && flags->precision <= octlen)
			write(fd, "0", 1);
		pad_zero(nbzero, fd);
	}
	return (padlen);
}

int	pad_oct(int octlen, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	if (flags->precision)
		return (pad_oct_prec(octlen, flags, fd));
	nbpad = flags->field_width - octlen - ((HASH_FLAG) ? 1 : 0);
	padlen = 0;
	padlen += (nbpad > 0 ? nbpad : 0) + ((HASH_FLAG) ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	if ((HASH_FLAG) && (ZERO_FLAG))
		write(fd, "0", 1);
	while (nbpad > 0)
	{
		if ((ZERO_FLAG))
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		nbpad--;
	}
	if ((HASH_FLAG) && !(ZERO_FLAG))
		write(fd, "0", 1);
	return (padlen);
}

int	special_convert_oct(uintmax_t oct, int fd, t_flags *flags)
{
	int full_len;
	int octlen;

	full_len = 0;
	octlen = ft_uintlen_base(oct, 8);
	if (MIN_FLAG)
	{
		full_len += pad_oct_prec_min(octlen, flags, fd, oct);
		return (full_len + octlen);
	}
	full_len += pad_oct(octlen, flags, fd);
	ft_uitoa_base(oct, 8, fd);
	return (full_len + octlen);
}

int	convert_oct(va_list args, int fd, t_flags *flags)
{
	uintmax_t	oct;
	int			octlen;

	if (HH_FLAG)
		oct = (unsigned char)va_arg(args, unsigned int);
	else if (H_FLAG)
		oct = (unsigned short)va_arg(args, unsigned int);
	else if (L_FLAG)
		oct = (unsigned long)va_arg(args, unsigned long);
	else if (LL_FLAG)
		oct = (unsigned long long)va_arg(args, unsigned long long);
	else
		oct = va_arg(args, unsigned int);
	if (is_activated(flags))
		return (special_convert_oct(oct, fd, flags));
	octlen = ft_uitoa_base(oct, 8, fd);
	return (octlen);
}
