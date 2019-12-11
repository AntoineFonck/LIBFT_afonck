/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:00:21 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 15:59:20 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_oct_prec_min(int octlen, t_flags *flags, int fd, uintmax_t oct)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_w -
		(flags->prec >= octlen ? flags->prec : octlen) -
		(flags->prec <= octlen ? (flags->on & HASH) : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->prec >= octlen ? flags->prec : octlen) - octlen;
	padlen = nbpad + nbzero +
		((flags->on & HASH) && flags->prec <= octlen ? 1 : 0);
	if ((flags->on & HASH) && flags->prec <= octlen)
		write(fd, "0", 1);
	pad_zero(nbzero, fd);
	ft_uitoa_base(oct, 8, fd);
	if (flags->prec < flags->field_w)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_oct_prec(int octlen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_w -
		(flags->prec >= octlen ? flags->prec : octlen) -
		(flags->prec <= octlen ? (flags->on & HASH) : 0);
	nbpad = (nbpad < 0 ? 0 : nbpad);
	nbzero = (flags->prec >= octlen ? flags->prec : octlen) - octlen;
	padlen = nbpad + nbzero +
		((flags->on & HASH) && flags->prec <= octlen ? 1 : 0);
	if (flags->prec < flags->field_w)
	{
		pad_space(nbpad, fd);
		if ((flags->on & HASH) && flags->prec <= octlen)
			write(fd, "0", 1);
		pad_zero(nbzero, fd);
	}
	else
	{
		if ((flags->on & HASH) && flags->prec <= octlen)
			write(fd, "0", 1);
		pad_zero(nbzero, fd);
	}
	return (padlen);
}

int	special_octzero(int fd, t_flags *flags)
{
	int len;

	len = flags->field_w + ((flags->on & HASH) && !flags->field_w ? 1 : 0);
	if (flags->on & HASH)
	{
		if (flags->on & PREC && !(flags->on & MIN))
			pad_space(len - 1, fd);
		if (!(flags->on & PREC) && !(flags->on & MIN))
			pad_zero(len - 1, fd);
		write(1, "0", 1);
		if (flags->on & MIN)
			pad_space(len - 1, fd);
		return (len);
	}
	pad_space(len, fd);
	return (len);
}

int	special_convert_oct(uintmax_t oct, int fd, t_flags *flags)
{
	int full_len;
	int octlen;

	full_len = 0;
	octlen = ft_uintlen_base(oct, 8);
	if (oct == 0 && (flags->on & PREC || flags->on & HASH) && flags->prec == 0)
		return (special_octzero(fd, flags));
	if (flags->on & MIN)
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

	if (flags->on & HH)
		oct = (unsigned char)va_arg(args, unsigned int);
	else if (flags->on & H)
		oct = (unsigned short)va_arg(args, unsigned int);
	else if (flags->on & L)
		oct = (unsigned long)va_arg(args, unsigned long);
	else if (flags->on & LL)
		oct = (unsigned long long)va_arg(args, unsigned long long);
	else
		oct = va_arg(args, unsigned int);
	if (is_activated(flags) || flags->on & PREC)
		return (special_convert_oct(oct, fd, flags));
	octlen = ft_uitoa_base(oct, 8, fd);
	return (octlen);
}
