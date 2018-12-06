/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:41:26 by afonck            #+#    #+#             */
/*   Updated: 2018/12/06 17:37:52 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void		setmemo(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			i;

	p = b;
	i = 0;
	while (i < len)
	{
		*p = (unsigned char)c;
		p++;
		i++;
	}
}

void			ft_bzero(void *s, size_t n)
{
	if (n != 0)
		setmemo(s, '\0', n);
}
