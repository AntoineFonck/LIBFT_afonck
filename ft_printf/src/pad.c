/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:00:08 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 16:55:55 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	pad_oct(int octlen, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	if (flags->prec)
		return (pad_oct_prec(octlen, flags, fd));
	nbpad = flags->field_w - octlen - ((flags->on & HASH) ? 1 : 0);
	padlen = 0;
	padlen += (nbpad > 0 ? nbpad : 0) + ((flags->on & HASH) ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	if ((flags->on & HASH) && (flags->on & ZERO) && !(flags->on & PREC))
		write(fd, "0", 1);
	while (nbpad > 0)
	{
		if ((flags->on & ZERO) && !(flags->on & PREC))
			ft_putchar_fd('0', fd);
		else
			ft_putchar_fd(' ', fd);
		nbpad--;
	}
	if (((flags->on & HASH) && !(flags->on & ZERO)) || (flags->on & HASH \
		&& flags->on & ZERO && flags->on & PREC))
		write(fd, "0", 1);
	return (padlen);
}

int	pad_uint_prec(uintmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_w - (flags->prec >= ft_unbrlen(number)
			? flags->prec : ft_unbrlen(number));
	if (((flags->on & PLUS) || (flags->on & SPACE)))
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->prec >= ft_unbrlen(number) ?
			flags->prec : ft_unbrlen(number)) -
		ft_unbrlen(number);
	padlen = nbpad + nbzero + ((flags->on & PLUS) || (flags->on & SPACE));
	if (!(flags->on & MIN))
		pad_space(nbpad, fd);
	pad_zero(nbzero, fd);
	ft_uitoa_base(number, 10, fd);
	if (flags->on & MIN)
		pad_space(nbpad, fd);
	return (padlen);
}

int	pad_uint(uintmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_w - ft_unbrlen(number);
	nbpad = (nbpad < 0 ? 0 : nbpad);
	padlen = nbpad;
	if ((flags->on & ZERO) && !(flags->on & MIN))
	{
		if ((flags->on & SPACE) && !(flags->on & PLUS))
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

int	pad_int_prec(intmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;
	int nbrlen;

	nbrlen = ft_nbrlen(number) - (number < 0 ? 1 : 0);
	nbpad = flags->field_w -
		(flags->prec >= nbrlen ? flags->prec : nbrlen) -
		(number < 0 ? 1 : 0) -
		(((flags->on & PLUS) || (flags->on & SPACE)) && number >= 0 ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->prec >= nbrlen ? flags->prec : nbrlen) - nbrlen;
	padlen = 0;
	flags_spec(flags, nbpad, fd, number);
	if (number < 0)
		ft_putchar_fd('-', fd);
	pad_zero(nbzero, fd);
	ft_putnbr_fd(ft_absolute(number), fd);
	if (flags->on & MIN)
		pad_space(nbpad, fd);
	padlen = nbpad + nbzero + (number >= 0 ? (flags->on & PLUS) \
		|| (flags->on & SPACE) : 0);
	return (padlen);
}

int	pad_str(int number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_w - number;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad;
	if ((flags->on & ZERO) && !(flags->on & MIN))
	{
		pad_zero(nbpad, fd);
		return (padlen);
	}
	pad_space(nbpad, fd);
	return (padlen);
}
