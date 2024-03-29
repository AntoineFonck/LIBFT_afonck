/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:17:05 by sluetzen          #+#    #+#             */
/*   Updated: 2019/07/05 13:53:50 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
**int special_convert_percent(int fd, t_flags *flags)
**{
**        int full_len;
**
**        full_len = 0;
**        if (flags->on & MIN)
**        {
**                if (flags->on & PLUS)
**                        ft_putchar_fd('+', fd);
**                ft_putchar_fd('%', fd);
**                full_len += pad_percent(1, flags, fd);
**                return (full_len + 1);
**        }
**        if (flags->on & PLUS)
**        {
**                if (flags->on & ZERO)
**                        ft_putchar_fd('+', fd);
**                full_len += pad_percent(1, flags, fd);
**                if (!(flags->on & ZERO))
**                        ft_putchar_fd('+', fd);
**                ft_putchar_fd('%', fd);
**                return (full_len + 1);
**        }
**        full_len += pad_percent(1, flags, fd);
**        ft_putchar_fd('%', fd);
**        return (full_len + 1);
**}
*/

/*
**int	convert_percent(va_list args, int fd, t_flags *flags)
**{
**	(void)args;
**	(void)flags;
**	if (is_activated(flags))
**	return (special_convert_percent(fd, flags));
**	ft_putchar_fd('%', fd);
**	return (1);
**}
*/

int	convert_percent(va_list args, int fd, t_flags *flags)
{
	(void)args;
	(void)flags;
	ft_putchar_fd('%', fd);
	return (1);
}

/*
**int pad_percent(int number, t_flags *flags, int fd)
**{
**        int nbpad;
**        int padlen;
**
**        nbpad = flags->field_w - ft_nbrlen(number);
**        if ((flags->on & PLUS) || (flags->on & SPACE))
**                nbpad--;
**        if (nbpad < 0)
**                nbpad = 0;
**        padlen = nbpad + (flags->on & PLUS);
**        if ((flags->on & ZERO) && !(flags->on & MIN))
**        {
**                pad_zero(nbpad, fd);
**                return (padlen);
**        }
**        pad_space(nbpad, fd);
**        return (padlen);
**}
*/
