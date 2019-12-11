/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:12:16 by sluetzen          #+#    #+#             */
/*   Updated: 2019/12/11 16:14:43 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

t_flags		*init_flags(void)
{
	t_flags *flags;

	if ((flags = (t_flags *)malloc(sizeof(t_flags))) == NULL)
		return (NULL);
	flags->on = 0;
	flags->field_w = 0;
	flags->prec = 0;
	flags->color = 0;
	return (flags);
}

void		check_flags(const char **fmt, t_flags *flags)
{
	while (is_flag(**fmt))
	{
		activate_flags(flags, **fmt);
		(*fmt)++;
	}
}

void		activate_flags(t_flags *flags, char c)
{
	if (c == '#')
		flags->on |= HASH;
	else if (c == '-')
		flags->on |= MIN;
	else if (c == '+')
		flags->on |= PLUS;
	else if (c == ' ')
		flags->on |= SPACE;
	else if (c == '0')
		flags->on |= ZERO;
	else
		return ;
}

int			is_activated(t_flags *flags)
{
	if ((flags->on & HASH) || (flags->on & MIN)
		|| (flags->on & PLUS) || (flags->on & SPACE)
		|| (flags->on & ZERO) || flags->field_w
		|| flags->prec)
		return (1);
	return (0);
}

void		flush_flags(t_flags *flags)
{
	flags->on = 0;
	flags->field_w = 0;
	flags->prec = 0;
	flags->color = 0;
}
