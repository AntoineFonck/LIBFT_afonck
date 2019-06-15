/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:00:21 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/14 13:11:23 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int pad_oct_prec_min(int octlen, t_flags *flags, int fd, unsigned int oct)
{
    int nbpad;
    int nbzero;
    int padlen;

    nbpad = flags->field_width - (flags->precision >= octlen ? flags->precision : octlen) - (flags->precision <= octlen ? flags->hashtag : 0);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= octlen ? flags->precision : octlen) - octlen;
    padlen = nbpad + nbzero + (flags->hashtag && flags->precision <= octlen ? 1 : 0);
    if (flags->hashtag && flags->precision <= octlen)
        write(fd, "0", 1);
    pad_zero(nbzero, fd);
    /* while (nbzero > 0)
    {
        ft_putchar_fd('0', fd);
        nbzero--;
    }*/
    ft_uitoaprint_base(oct, 8, fd);
    if (flags->precision < flags->field_width)
    {
        pad_space(nbpad, fd);
        /* while (nbpad)
        {
            ft_putchar_fd(' ', fd);
            nbpad--;
        }*/
    }
    return (padlen);
}

int pad_oct_prec(int octlen, t_flags *flags, int fd)
{
    int nbpad;
    int nbzero;
    int padlen;

    nbpad = flags->field_width - (flags->precision >= octlen ? flags->precision : octlen) - (flags->precision <= octlen ? flags->hashtag : 0);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= octlen ? flags->precision : octlen) - octlen;
    padlen = nbpad + nbzero + (flags->hashtag && flags->precision <= octlen ? 1 : 0);
    if (flags->precision < flags->field_width)
    {
        pad_space(nbpad, fd);
        /* while (nbpad)
        {
            ft_putchar_fd(' ', fd);
            nbpad--;
        }*/
        if (flags->hashtag && flags->precision <= octlen)
            write(fd, "0", 1);
        pad_zero(nbzero, fd);
        /* while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }*/ 
    }
    else
    {
        if (flags->hashtag && flags->precision <= octlen)
            write(fd, "0", 1);
        pad_zero(nbzero, fd);
        /* while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }*/
    }
    return (padlen);
}

int pad_oct(int octlen, t_flags *flags, int fd)
{
    int nbpad;
    int padlen;

    if (flags->precision)
        return (pad_oct_prec(octlen, flags, fd));
    nbpad = flags->field_width - octlen - (flags->hashtag ? 1 : 0);
    padlen = 0;
    padlen += (nbpad > 0 ? nbpad : 0) + (flags->hashtag ? 1 : 0);
    if (nbpad < 0)
        nbpad = 0;
    if (flags->hashtag && flags->zero)
	    write(fd, "0", 1);
    while (nbpad > 0)
    {
        if (flags->zero)
            ft_putchar_fd('0', fd);
        else
            ft_putchar_fd(' ', fd);
        nbpad--;
    }
    if (flags->hashtag && !flags->zero)
     	write(fd, "0", 1);
    return (padlen);
}

int special_convert_oct(unsigned int oct, int fd, t_flags *flags)
{
    int full_len;
    int octlen;

    full_len = 0;
    octlen = ft_uitoalen_base(oct, 8);
    if (flags->minus)
    {
        full_len += pad_oct_prec_min(octlen, flags, fd, oct);
        return (full_len + octlen);
    }
    full_len += pad_oct(octlen, flags, fd);
    ft_uitoaprint_base(oct, 8, fd);
    return (full_len + octlen);
}

int convert_oct(va_list args, int fd, t_flags *flags)
{
    unsigned int oct;
    int octlen;
    oct = va_arg(args, unsigned int);
    if (is_activated(flags))
        return (special_convert_oct(oct, fd, flags));
    octlen = ft_uitoaprint_base(oct, 8, fd);
    return (octlen);
}
