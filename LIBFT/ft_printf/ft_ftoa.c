/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:21:42 by afonck            #+#    #+#             */
/*   Updated: 2019/06/24 14:32:54 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

double ft_pow(double x, int y) {
	double r = 1;

	while (y > 0)
	{
		if (y & 1)
			r *= x;
		x *= x;
		y >>= 1;
	}
	return (r);
}

static int handle_decimal(double n, double fpart, int afterpoint, int fd, int morezero)
{
	int length;

	length = 0;
	if (afterpoint != 0) 
	{
		ft_putchar_fd('.', fd);
		length++; 
		fpart = fpart * ft_pow(10, afterpoint);
		printf("FPART after pow = %f\n", fpart);
		fpart = (n >= 0 ? fpart + 0.5 : fpart - 0.5);
		fpart = ft_absolute(fpart);
		//morezero = afterpoint - ft_floatlen(fpart, afterpoint);//- ft_nbrlen((unsigned long)fpart);
		morezero = afterpoint - ft_nbrlen((long)fpart);
		printf("afterpoint = %d et nbrlen fpart = %d and the fpart too = %ld\n", afterpoint, ft_nbrlen((long)fpart), (long)fpart);
		printf("morezero = %d and fpart = %ld\n", morezero, (long)fpart);
		if (morezero > 0)
		{
			printf("HEREEEEEEEEEEEEEEE0");
			pad_zero(morezero, fd);
			length += morezero;
		}
		printf("HEREEEEEEEEEEEEEEE2");
		length += ft_nbrlen(ft_absolute((long)fpart));
		ft_uitoaprint_base(ft_absolute((unsigned long)fpart), 10, fd);
	}
	printf("length of deci = %d\n", length);
	return (length);
}

int ft_ftoa(double n, int afterpoint, int fd) 
{ 
	int len;
	int ipart;
	double fpart;
	int morezero;

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
	printf("FPART = %f\n", fpart);
	len += handle_decimal(n, fpart, afterpoint, fd, morezero);
	printf("full float len = %d\n", len);
	return (len);
}

int ft_floatlen(double n, int afterpoint)
{
	int len;
	int ipart;
	double fpart;

	len = 0;
	ipart = ((int)n);
	fpart = n - (double)ipart;
	fpart = fpart * ft_pow(10, afterpoint);
	fpart = (n >= 0 ? fpart + 0.5 : fpart - 0.5);
	len += ft_nbrlen(ipart);
	printf("[DEBUG] IN FLOAT LEN, len = %d after += IPART\n", len);
	if (afterpoint != 0)
	{
		if (ft_absolute((long)fpart) != 0)
			len += ft_nbrlen(ft_absolute((long)fpart)) + 1; // +1 --> '.'
		else
			len += afterpoint + 1;
	}
	printf("[DEBUG] IN FLOAT LEN, len = %d\n", len);
	return (len);
}
