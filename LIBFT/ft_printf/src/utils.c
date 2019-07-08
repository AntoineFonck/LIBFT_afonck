/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:41:48 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/08 15:13:20 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pad_zero(int nbzero, int fd)
{
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
	if (nbpad > 0)
	{
		while (nbpad > 0)
		{
			write(fd, " ", 1);
			nbpad--;
		}
	}
}

int		is_flag(char c)
{
	if (c == '#' || c == '-' || c == '+' || c == ' ' || c == '0')
		return (1);
	else
		return (0);
}
