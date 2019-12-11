/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:40:22 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/05 10:44:02 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_pointer_prec_min(int hexlen, t_flags *flags, int fd, uintptr_t hex)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_w -
		(flags->prec >= hexlen ? flags->prec : hexlen) - 2;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->prec >= hexlen ? flags->prec : hexlen) - hexlen;
	padlen = nbpad + nbzero + 2 + (flags->prec < hexlen ? 0 : 0);
	write(fd, "0x", 2);
	pad_zero(nbzero, fd);
	ft_uintptrtoa_base(hex, 16, fd);
	if (flags->prec < flags->field_w)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_pointer_prec(int hexlen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_w -
		(flags->prec >= hexlen ? flags->prec : hexlen) - 2;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->prec >= hexlen ? flags->prec : hexlen) - hexlen;
	padlen = nbpad + nbzero + 2 + (flags->prec < hexlen ? 0 : 0);
	if (flags->prec < flags->field_w)
	{
		pad_space(nbpad, fd);
		write(fd, "0x", 2);
		pad_zero(nbzero, fd);
	}
	else
	{
		write(fd, "0x", 2);
		pad_zero(nbzero, fd);
	}
	return (padlen);
}

int	pad_pointer(int hexlen, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	if (flags->prec)
		return (pad_pointer_prec(hexlen, flags, fd));
	nbpad = flags->field_w - hexlen - 2;
	padlen = 0;
	padlen += (nbpad > 0 ? nbpad : 0) + 2;
	if (nbpad < 0)
		nbpad = 0;
	if ((flags->on & ZERO))
		write(fd, "0x", 2);
	while (nbpad > 0)
	{
		if ((flags->on & ZERO))
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		nbpad--;
	}
	if (!(flags->on & ZERO))
		write(fd, "0x", 2);
	return (padlen);
}

int	special_convert_pointer(uintptr_t hex, int fd, t_flags *flags)
{
	int full_len;
	int hexlen;

	full_len = 0;
	hexlen = ft_uintptrtoalen_base(hex, 16);
	if ((flags->on & MIN))
	{
		full_len += pad_pointer_prec_min(hexlen, flags, fd, hex);
		return (full_len + hexlen);
	}
	full_len += pad_pointer(hexlen, flags, fd);
	ft_uintptrtoa_base(hex, 16, fd);
	return (full_len + hexlen);
}

int	convert_pointer(va_list args, int fd, t_flags *flags)
{
	uintptr_t	hex;
	int			hexlen;

	hex = va_arg(args, uintptr_t);
	if (is_activated(flags))
		return (special_convert_pointer(hex, fd, flags));
	write(fd, "0x", 2);
	hexlen = ft_uintptrtoa_base(hex, 16, fd);
	return (hexlen + 2);
}
