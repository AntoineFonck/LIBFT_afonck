/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <afonck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:15:51 by afonck          #+#    #+#             */
/*   Updated: 2019/06/12 18:15:56 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int pad_pointer_prec_min(int hexlen, t_flags *flags, int fd, uintptr_t hex)
{
    int nbpad;
    int nbzero;
    int padlen;

    nbpad = flags->field_width - (flags->precision >= hexlen ? flags->precision : hexlen) - (flags->hashtag ? 2 : 0);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
    padlen = nbpad + nbzero + (flags->hashtag ? 2 : 0) + (flags->precision < hexlen ? 0 : 0);
    write(fd, "0x", 2);
    pad_zero(nbzero, fd);
    /*while (nbzero > 0)
    {
        ft_putchar_fd('0', fd);
        nbzero--;
    }*/
    ft_uintptrtoaprint_base(hex, 16, fd);
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

int pad_pointer_prec(int hexlen, t_flags *flags, int fd)
{
    int nbpad;
    int nbzero;
    int padlen;
    nbpad = flags->field_width - (flags->precision >= hexlen ? flags->precision : hexlen) - (flags->hashtag ? 2 : 0);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
    padlen = nbpad + nbzero + (flags->hashtag ? 2 : 0) + (flags->precision < hexlen ? 0 : 0);
    if (flags->precision < flags->field_width)
    {
        pad_space(nbpad, fd);
        /* while (nbpad)
        {
            ft_putchar_fd(' ', fd);
            nbpad--;
        }*/
        write(fd, "0x", 2);
        pad_zero(nbzero, fd);
        /* while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }*/
    }
    else
    {
        write(fd, "0x", 2);
        pad_zero(nbzero, fd);
        /* while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }*/
    }
    return (padlen);
}

int pad_pointer(int hexlen, t_flags *flags, int fd)
{
    int nbpad;
    int padlen;
    int test;

    if (flags->precision)
        return (pad_pointer_prec(hexlen, flags, fd));
    nbpad = flags->field_width - hexlen;
    padlen = 0;
    test = hexlen + 1;
    padlen += nbpad > 0 ? nbpad : 0;
    if (nbpad < 0)
        nbpad = 0;
    if (flags->hashtag && !flags->zero)
    {
        if (flags->hashtag)
            nbpad -= 2;
        pad_space(nbpad, fd);
        /* while (nbpad > 0)
        {
            ft_putchar_fd(' ', fd);
            nbpad--;
        }*/
    }
    if (flags->hashtag)
    {
        if (flags->zero)
             write(fd, "0x", 2);
        nbpad -= 2;
        if (hexlen >= flags->field_width)
            padlen += 2;
        if (test == flags->field_width)
            padlen++;
    }
    //padlen = nbpad + 2;
    
    if (flags->zero)
    {
        if (flags->hashtag)
        {
            pad_space(nbpad, fd);
            /* while (nbpad > 0)
            {
                ft_putchar_fd('0', fd);
                nbpad--;
            }*/
        }
        return (padlen);
    }
    pad_space(nbpad, fd);
    /* while (nbpad > 0)
    {
        ft_putchar_fd(' ', fd);
        nbpad--;
    }*/
    if (flags->hashtag && !flags->zero)
        write(fd, "0x", 2);
    return (padlen);
}

int special_convert_pointer(uintptr_t hex, int fd, t_flags *flags)
{
    int full_len;
    int hexlen;

    full_len = 0;
    hexlen = ft_uintptrtoalen_base(hex, 16, fd);
    if (flags->minus)
    {
        if (!flags->precision && !flags->hashtag)
            ft_uintptrtoaprint_base(hex, 16, fd);
        full_len += pad_pointer_prec_min(hexlen, flags, fd, hex);
        return (full_len + hexlen);
    }
    full_len += pad_pointer(hexlen, flags, fd);
    ft_uintptrtoaprint_base(hex, 16, fd);
    return (full_len + hexlen);
}

int convert_pointer(va_list args, int fd, t_flags *flags)
{
    uintptr_t hex;
    int len;
    int hexlen;

    hex = va_arg(args, uintptr_t);
    if (is_activated(flags))
        return (special_convert_pointer(hex, fd, flags));
    write(fd, "0x", 2);
    hexlen = ft_uintptrtoaprint_base(hex, 16, fd);
    return (hexlen + 2);
}
