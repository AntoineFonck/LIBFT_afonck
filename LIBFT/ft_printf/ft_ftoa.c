/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:21:42 by afonck            #+#    #+#             */
/*   Updated: 2019/06/25 18:45:07 by sluetzen         ###   ########.fr       */
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
/*
static int	print_deci(double fpart, int afterpoint, int fd)
{
	int i;
	char buf[afterpoint + 1];
	char *ptr;

	i = 0;
	ptr = &buf[afterpoint];
	*ptr = '\0';
	while (i < afterpoint)
	{
		printf("fpart in print deci = %f\n", fpart);
		printf("*ptr = %c\n", ('0' + (char)((long)fpart % 10)));
		*--ptr = '0' + ((long)fpart % 10);
		fpart /= 10;
		i++;
	}
	write(fd, buf, afterpoint);
	return (1);
}
*/
static void	handle_decimal(double n, double fpart, int afterpoint, int fd, int morezero)
{
	if (afterpoint != 0)
	{
		ft_putchar_fd('.', fd);
		fpart = fpart * ft_pow(10, afterpoint);
		fpart = (n >= 0 ? fpart + 0.5 : fpart - 0.5);
		//printf("fpart = %f and long fpart = %ld\n", fpart, (long)fpart);
		fpart = ft_absolute(fpart);
		//printf("fpart = %f and long fpart = %ld\n", fpart, (long)fpart);
		morezero = afterpoint - ft_nbrlen((long)fpart);
		if (morezero > 0)
			pad_zero(morezero, fd);
		//length += ft_nbrlen(ft_absolute((long)fpart));
		//ft_uitoaprint_base(ft_absolute((unsigned long)fpart), 10, fd);
		//printf("length: %d\n", length);
		ft_uitoaprint_base((unsigned long)fpart, 10, fd);
		//print_deci(fpart, afterpoint, fd);
	}
}

int			ft_ftoa(double n, int afterpoint, int fd)
{
	int		len;
	long	ipart;
	double	fpart;
	int		morezero;

	len = afterpoint + (afterpoint > 0 ? 1 : 0);
	ipart = (long)n;
	fpart = n - (double)ipart;
	if (ipart == 0 && !(1 / n > 0))
	{
		len++;
		write(fd, "-", 1);
	}
	morezero = 0;
	len += ft_nbrlen(ipart);
	if (afterpoint == 0)
	{
		if (fpart >= 0.5)
			ipart += 1;
	}
	ft_putnbr_fd(ipart, fd);
	handle_decimal(n, fpart, afterpoint, fd, morezero);
	//len = afterpoint + ft_nbrlen(ipart) + (afterpoint > 0 ? 1 : 0); // the dot
	return (len);
}

int		ft_floatlen(double n, int afterpoint)
{
	int		len;
	long	ipart;
	double	fpart;

	len = 0;
	ipart = (long)n;
	fpart = n - (double)ipart;
	fpart = fpart * ft_pow(10, afterpoint);
	fpart = (n >= 0 ? fpart + 0.5 : fpart - 0.5);
	len += ft_nbrlen(ipart);
	if (afterpoint != 0)
		len += afterpoint + 1;
	if (ipart == 0 && !(1 / n > 0))
		len++;
	return (len);
}
