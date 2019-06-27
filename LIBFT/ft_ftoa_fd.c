/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:21:42 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 14:25:19 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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

int			ft_ftoa_fd(double n, int afterpoint, int fd)
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
