/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:00:04 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 16:46:50 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	flags_spec(t_flags *flags, int nbpad, int fd, intmax_t number)
{
	if (!(flags->on & MIN))
		pad_space(nbpad, fd);
	if ((flags->on & PLUS) && number >= 0)
		ft_putchar_fd('+', fd);
	if ((flags->on & SPACE) && number >= 0 && !(flags->on & PLUS))
		ft_putchar_fd(' ', fd);
}

void	flags_specfloat(t_flags *flags, int nbpad, int fd, double nb)
{
	if (!(flags->on & MIN))
	{
		if ((flags->on & PLUS) && nb >= 0 && flags->on & ZERO && (1 / nb > 0))
			ft_putchar_fd('+', fd);
		if ((flags->on & SPACE) && nb >= 0 && !(flags->on & PLUS)
				&& flags->on & ZERO && (1 / nb > 0))
			ft_putchar_fd(' ', fd);
		if (flags->on & ZERO)
			pad_zero(nbpad, fd);
		else
			pad_space(nbpad, fd);
		if ((flags->on & PLUS) && nb >= 0 && !(flags->on & ZERO) && 1 / nb > 0)
			ft_putchar_fd('+', fd);
		if ((flags->on & SPACE) && nb >= 0 && !(flags->on & PLUS)
				&& !(flags->on & ZERO) && (1 / nb > 0))
			ft_putchar_fd(' ', fd);
	}
	else
	{
		if ((flags->on & PLUS) && nb >= 0 && (1 / nb > 0))
			ft_putchar_fd('+', fd);
		if ((flags->on & SPACE) && nb >= 0 && !(flags->on & PLUS) \
			&& (1 / nb > 0))
			ft_putchar_fd(' ', fd);
	}
}

void	print_float(double number, int preclen, t_flags *flags, int fd)
{
	if (number == 0 && !(1 / number > 0) && !(flags->on & ZERO))
		ft_putchar_fd('-', fd);
	if (flags->on & ZERO || (number == 0 && !(1 / number > 0)))
		ft_ftoa_fd(ft_absfloat(number), preclen, fd);
	else
		ft_ftoa_fd(number, preclen, fd);
}

int		pad_float_prec(double number, int preclen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;
	int nbrlen;

	nbrlen = ft_floatlen(number, preclen) - (!(1 / number > 0) ? 1 : 0) +
		((flags->on & HASH) && (flags->on & PREC) && flags->prec == 0);
	nbpad = flags->field_w - (flags->prec >= nbrlen ?
			flags->prec : nbrlen) - !(1 / number > 0) -
		((flags->on & PLUS || flags->on & SPACE) && (1 / number > 0));
	nbpad = (nbpad < 0 ? 0 : nbpad);
	nbzero = (flags->prec >= nbrlen ? flags->prec : nbrlen) - nbrlen
		+ ((flags->on & HASH) && (flags->on & PREC) && flags->prec == 0);
	padlen = nbpad + nbzero + ((1 / number > 0) ?
			(flags->on & PLUS) || (flags->on & SPACE) : 0);
	if (number == 0 && !(1 / number > 0) && (flags->on & ZERO))
		ft_putchar_fd('-', fd);
	flags_specfloat(flags, nbpad, fd, number);
	print_float(number, preclen, flags, fd);
	if ((flags->on & HASH) && (flags->on & PREC) && flags->prec == 0)
		ft_putchar_fd('.', fd);
	if ((flags->on & MIN))
		pad_space(nbpad, fd);
	return (padlen);
}
