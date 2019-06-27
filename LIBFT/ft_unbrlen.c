/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:36:37 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/27 15:19:53 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_unbrlen(uintmax_t n)
{
	unsigned int	nbdigits;

	nbdigits = 0;
	if (n == 0)
		return (1);
	if (n < nbdigits)
		nbdigits++;
	while (n != 0)
	{
		n = n / 10;
		nbdigits++;
	}
	return (nbdigits);
}
