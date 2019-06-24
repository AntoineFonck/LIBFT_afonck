/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:21:42 by afonck            #+#    #+#             */
/*   Updated: 2019/06/24 16:01:22 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

double		ft_pow(double x, int y)
{
	double r;

	r = 1;
	while (y > 0)
	{
		if (y & 1)
			r *= x;
		x *= x;
		y >>= 1;
	}
	return (r);
}

static int	print_deci(double fpart)//, int afterpoint, int fd)
{
	while (fpart > 0)
	{
		printf("fpart in print deci = %f\n", fpart);
		fpart /= 10;
	}
	return (1);
}

static int	handle_decimal(double n, double fpart, int afterpoint, int fd, int morezero)
{
	int length;

	length = 0;
	if (afterpoint != 0)
	{
		ft_putchar_fd('.', fd);
		length++;
		printf("fpart = %f and long fpart = %ld\n", fpart, (long)fpart);
		fpart = fpart * ft_pow(10, afterpoint);
		fpart = (n >= 0 ? fpart + 0.5 : fpart - 0.5);
		printf("fpart = %f and long fpart = %ld\n", fpart, (long)fpart);
		//fpart = ft_absolute(fpart);
		morezero = afterpoint - ft_nbrlen((long)fpart);
		if (morezero > 0)
		{
			pad_zero(morezero, fd);
			length += morezero;
		}
		//length += ft_nbrlen(ft_absolute((long)fpart));
		//ft_uitoaprint_base(ft_absolute((unsigned long)fpart), 10, fd);
		length += ft_nbrlen((long)fpart);
		//ft_uitoaprint_base((unsigned long)fpart, 10, fd);
		//print_deci(fpart, afterpoint, fd);
		print_deci(fpart);
	}
	return (length);
}

int			ft_ftoa(double n, int afterpoint, int fd)
{
	int		len;
	int		ipart;
	double	fpart;
	int		morezero;

	len = 0;
	ipart = (int)n;
	fpart = n - (double)ipart;
	morezero = 0;
	len += ft_nbrlen(ipart);
	if (afterpoint == 0)
	{
		if (fpart >= 0.5)
			ipart += 1;
	}
	ft_putnbr_fd(ipart, fd);
	len += handle_decimal(n, fpart, afterpoint, fd, morezero);
	return (len);
}

int		ft_floatlen(double n, int afterpoint)
{
	int		len;
	int		ipart;
	double	fpart;

	len = 0;
	ipart = ((int)n);
	fpart = n - (double)ipart;
	fpart = fpart * ft_pow(10, afterpoint);
	fpart = (n >= 0 ? fpart + 0.5 : fpart - 0.5);
	len += ft_nbrlen(ipart);
	if (afterpoint != 0)
	{
		if (ft_absolute((long)fpart) != 0)
			len += ft_nbrlen(ft_absolute((long)fpart)) + 1; // +1 --> '.'
		else
			len += afterpoint + 1;
	}
	return (len);
}
