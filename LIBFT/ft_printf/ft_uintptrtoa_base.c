/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintptrtoa_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:32:29 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/24 15:33:27 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int	ft_uintptrtoaprint_base(uintptr_t value, int base, int fd)
{
	char	buf[(sizeof(uintptr_t) * 2) + 1];
	char	*ptr;
	int		num;
	int		ascii_offset;

	ptr = &buf[(sizeof(uintptr_t) * 2)];
	*ptr = '\0';
	num = value;
	if (value == 0)
		*--ptr = '0' + (value % base);
	while (value != 0)
	{
		ascii_offset = 0;
		if (value % base > 9)
			ascii_offset = 39;
		*--ptr = '0' + ((value % base) + ascii_offset);
		value /= base;
	}
	write(fd, ptr, ft_strlen(ptr));
	return (ft_strlen(ptr));
}

int	ft_uintptrtoalen_base(uintptr_t value, int base)
{
	char	buf[(sizeof(uintptr_t) * 2) + 1]; // 8 bytes * 2 (2 char per byte ex a7)
	char	*ptr;
	int		num;
	int		ascii_offset;

	ptr = &buf[(sizeof(uintptr_t) * 2)];
	*ptr = '\0';
	num = value;
	if (value == 0)
		*--ptr = '0' + (value % base);
	while (value != 0)
	{
		ascii_offset = 0;
		if (value % base > 9)
			ascii_offset = 39;
		*--ptr = '0' + ((value % base) + ascii_offset);
		value /= base;
	}
	return (ft_strlen(ptr));
}
