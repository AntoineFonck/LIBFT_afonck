/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:26:11 by afonck            #+#    #+#             */
/*   Updated: 2018/12/06 17:39:00 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		res;
	char	*s1rep;
	char	*s2rep;

	i = 0;
	res = 0;
	s1rep = (char *)s1;
	s2rep = (char *)s2;
	while (i < n)
	{
		if (s1rep[i] > s2rep[i] || s1rep[i] < s2rep[i])
		{
			res = (unsigned char)s1rep[i] - (unsigned char)s2rep[i];
			return (res);
		}
		i++;
	}
	return (0);
}
