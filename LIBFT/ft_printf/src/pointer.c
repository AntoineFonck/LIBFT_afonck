/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:40:22 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/27 18:51:48 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_pointer_prec_min(int hexlen, t_flags *flags, int fd, uintptr_t hex)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= hexlen ? flags->precision : hexlen) - 2;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
	padlen = nbpad + nbzero + 2 + (flags->precision < hexlen ? 0 : 0);
	write(fd, "0x", 2);
	pad_zero(nbzero, fd);
	/*while (nbzero > 0)
	  {
	  ft_putchar_fd('0', fd);
	  nbzero--;
	  }*/
	ft_uintptrtoa_base(hex, 16, fd);
	if (flags->precision < flags->field_width)
	{
		pad_space(nbpad, fd);
		/* while (nbpad)
		   {
		   ft_putchar_fd(' ', fd);
		   nbpad--;
		   }*/
	}
	return (padlen);
}

int	pad_pointer_prec(int hexlen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width -
		(flags->precision >= hexlen ? flags->precision : hexlen) - 2;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
	padlen = nbpad + nbzero + 2 + (flags->precision < hexlen ? 0 : 0);
	if (flags->precision < flags->field_width)
	{
		pad_space(nbpad, fd);
		/* while (nbpad)
		   {
		   ft_putchar_fd(' ', fd);
		   nbpad--;
		   }*/
		write(fd, "0x", 2);
		pad_zero(nbzero, fd);
		/* while (nbzero > 0)
		   {
		   ft_putchar_fd('0', fd);
		   nbzero--;
		   }*/
	}
	else
	{
		write(fd, "0x", 2);
		pad_zero(nbzero, fd);
		/* while (nbzero > 0)
		   {
		   ft_putchar_fd('0', fd);
		   nbzero--;
		   }*/
	}
	return (padlen);
}

int	pad_pointer(int hexlen, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	if (flags->precision)
		return (pad_pointer_prec(hexlen, flags, fd));
	nbpad = flags->field_width - hexlen - ((HASH_FLAG) ? 2 : 0);
	padlen = 0;
	padlen += (nbpad > 0 ? nbpad : 0) + ((HASH_FLAG) ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	if ((ZERO_FLAG))
		write(fd, "0x", 2);
	while (nbpad > 0)
	{
		if ((ZERO_FLAG))
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		nbpad--;
	}
	if (!(ZERO_FLAG))
		write(fd, "0x", 2);
	return (padlen);
}

int	special_convert_pointer(uintptr_t hex, int fd, t_flags *flags)
{
	int full_len;
	int hexlen;

	full_len = 0;
	hexlen = ft_uintptrtoalen_base(hex, 16);
	if ((MIN_FLAG))
	{
	//if (!flags->precision)
	//ft_uintptrtoa_base(hex, 16, fd);
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