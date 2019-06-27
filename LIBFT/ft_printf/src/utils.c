/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:41:48 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/24 15:43:06 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	pad_zero(int nbzero, int fd)
{
	char buf[nbzero];

	if (nbzero > 0)
	{
		ft_memset(buf, '0', nbzero);
		write(fd, buf, nbzero);
	}
}

void	pad_space(int nbpad, int fd)
{
	char buf[nbpad];

	if (nbpad > 0)
	{
		ft_memset(buf, ' ', nbpad);
		write(fd, buf, nbpad);
	}
}
