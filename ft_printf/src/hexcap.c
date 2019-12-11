/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexcap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 09:50:42 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 15:59:11 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_hex_prec_mincap(int hexlen, t_flags *flags, int fd, uintmax_t hex)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_w -
		(flags->prec >= hexlen ? flags->prec : hexlen) -
		((flags->on & HASH) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->prec >= hexlen ? flags->prec : hexlen)
		- hexlen;
	padlen = nbpad + nbzero + ((flags->on & HASH) ? 2 : 0)
		+ (flags->prec < hexlen ? 0 : 0);
	if ((flags->on & HASH))
		write(fd, "0X", 2);
	pad_zero(nbzero, fd);
	ft_uitocapa_base(hex, 16, fd);
	if (flags->prec < flags->field_w)
		pad_space(nbpad, fd);
	return (padlen);
}

int	special_hexzero(int fd, t_flags *flags)
{
	int spacelen;
	int fullen;

	spacelen = flags->field_w - flags->prec - (flags->on & PREC ? 0 : 1);
	spacelen = spacelen < 0 ? 0 : spacelen;
	fullen = (flags->field_w <= flags->prec ? flags->prec
			: spacelen + flags->prec) + (flags->on & PREC ? 0 : 1);
	if (flags->on & MIN)
	{
		if (flags->on & HASH && !(flags->on & PREC))
			ft_putchar_fd('0', fd);
		pad_zero(flags->prec, fd);
		pad_space(spacelen, fd);
	}
	else
	{
		if (flags->on & ZERO && !(flags->on & PREC))
			pad_zero(spacelen, fd);
		else
			pad_space(spacelen, fd);
		pad_zero(flags->prec, fd);
		if (flags->on & HASH && !(flags->on & PREC))
			ft_putchar_fd('0', fd);
	}
	return (fullen);
}

int	convert_cap_hex(va_list args, int fd, t_flags *flags)
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
		return (special_convert_hex(hex, fd, flags, 'X'));
	hexlen = ft_uitocapa_base(hex, 16, fd);
	return (hexlen);
}
