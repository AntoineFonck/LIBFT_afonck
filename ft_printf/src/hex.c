/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 11:04:22 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 15:57:47 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_hex_prec_min(int hexlen, t_flags *flags, int fd, uintmax_t hex)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_w -
		(flags->prec >= hexlen ? flags->prec : hexlen) -
		((flags->on & HASH) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->prec >= hexlen ? flags->prec : hexlen) - hexlen;
	padlen = nbpad + nbzero + ((flags->on & HASH) ? 2 : 0)
		+ (flags->prec < hexlen ? 0 : 0);
	if ((flags->on & HASH))
		write(fd, "0x", 2);
	pad_zero(nbzero, fd);
	ft_uitoa_base(hex, 16, fd);
	if (flags->prec < flags->field_w)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_hex_prec(int hexlen, t_flags *flags, int fd, char letter)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_w -
		(flags->prec >= hexlen ? flags->prec : hexlen) -
		((flags->on & HASH) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->prec >= hexlen ? flags->prec : hexlen) - hexlen;
	padlen = nbpad + nbzero + ((flags->on & HASH) ? 2 : 0)
		+ (flags->prec < hexlen ? 0 : 0);
	if (flags->prec < flags->field_w)
		pad_space(nbpad, fd);
	if ((flags->on & HASH))
		letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
	pad_zero(nbzero, fd);
	return (padlen);
}

int	pad_hex(int hexlen, t_flags *flags, int fd, char letter)
{
	int nbpad;
	int padlen;

	if (flags->prec || flags->on & PREC)
		return (pad_hex_prec(hexlen, flags, fd, letter));
	nbpad = flags->field_w - hexlen - ((flags->on & HASH) ? 2 : 0);
	padlen = 0;
	padlen += (nbpad > 0 ? nbpad : 0) + ((flags->on & HASH) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	if ((flags->on & HASH) && (flags->on & ZERO))
		letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
	while (nbpad > 0)
	{
		if ((flags->on & ZERO))
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		nbpad--;
	}
	if ((flags->on & HASH) && !(flags->on & ZERO))
		letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
	return (padlen);
}

int	special_convert_hex(uintmax_t hex, int fd, t_flags *flags, char letter)
{
	int full_len;
	int hexlen;

	full_len = 0;
	hexlen = ft_uintlen_base(hex, 16);
	if (((flags->on & HASH) || (flags->on & PREC)) && hex == 0)
		return (special_hexzero(fd, flags));
	if (flags->on & MIN)
	{
		if (letter == 'x')
			full_len += pad_hex_prec_min(hexlen, flags, fd, hex);
		else if (letter == 'X')
			full_len += pad_hex_prec_mincap(hexlen, flags, fd, hex);
		return (full_len + hexlen);
	}
	full_len += pad_hex(hexlen, flags, fd, letter);
	if (letter == 'x')
		ft_uitoa_base(hex, 16, fd);
	else if (letter == 'X')
		ft_uitocapa_base(hex, 16, fd);
	return (full_len + hexlen);
}

int	convert_hex(va_list args, int fd, t_flags *flags)
{
	uintmax_t	hex;
	int			hexlen;

	if (flags->on & HH)
		hex = (unsigned char)va_arg(args, unsigned int);
	else if (flags->on & H)
		hex = (unsigned short)va_arg(args, unsigned int);
	else if (flags->on & L)
		hex = (unsigned long)va_arg(args, unsigned long);
	else if (flags->on & LL)
		hex = (unsigned long long)va_arg(args, unsigned long long);
	else
		hex = va_arg(args, unsigned int);
	if (is_activated(flags) || flags->on & PREC)
		return (special_convert_hex(hex, fd, flags, 'x'));
	hexlen = ft_uitoa_base(hex, 16, fd);
	return (hexlen);
}
