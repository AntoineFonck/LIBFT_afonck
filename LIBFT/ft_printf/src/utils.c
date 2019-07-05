/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:41:48 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/05 12:17:20 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pad_zero(int nbzero, int fd)
{
	/*
	char buf[nbzero];

	if (nbzero > 0)
	{
		ft_memset(buf, '0', nbzero);
		write(fd, buf, nbzero);
	}
	*/
	if (nbzero > 0)
	{
		while (nbzero > 0)
		{
			write(fd, "0", 1);
			nbzero--;
		}
	}
}

void	pad_space(int nbpad, int fd)
{
	/*
	char buf[nbpad];

	if (nbpad > 0)
	{
		ft_memset(buf, ' ', nbpad);
		write(fd, buf, nbpad);
	}
	*/
	if (nbpad > 0)
	{
		while (nbpad > 0)
		{
			write(fd, " ", 1);
			nbpad--;
		}
	}
}
