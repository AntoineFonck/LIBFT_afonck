/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 11:04:22 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/13 16:01:44 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int pad_hex_prec_min(int hexlen, t_flags *flags, int fd, unsigned int hex, char letter)
{
    int nbpad;
    int nbzero;
    int padlen;

    nbpad = flags->field_width - (flags->precision >= hexlen ? flags->precision : hexlen) - (flags->hashtag ? 2 : 0);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
    padlen = nbpad + nbzero + (flags->hashtag ? 2 : 0) + (flags->precision < hexlen ? 0 : 0);
    if (flags->hashtag)
        letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
    pad_zero(nbzero, fd);
    /* while (nbzero > 0)
    {
        ft_putchar_fd('0', fd);
        nbzero--;
    }*/
    if (letter == 'x')
    	ft_uitoaprint_base(hex, 16, fd);
    else if (letter == 'X')
	ft_uitocapaprint_base(hex, 16, fd);
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

int pad_hex_prec(int hexlen, t_flags *flags, int fd, char letter)
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
        if (flags->hashtag)
            letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
        pad_zero(nbzero, fd);
        /* while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }*/ 
    }
    else
    {
        if (flags->hashtag)
            letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
        pad_zero(nbzero, fd);
        /* while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }*/
    }
    return (padlen);
}

int pad_hex(int hexlen, t_flags *flags, int fd, char letter)
{
    int nbpad;
    int padlen;

    if (flags->precision)
        return (pad_hex_prec(hexlen, flags, fd, letter));
    nbpad = flags->field_width - hexlen - (flags->hashtag ? 2 : 0);
    padlen = 0;
    padlen += (nbpad > 0 ? nbpad : 0) + (flags->hashtag ? 2 : 0);
    if (nbpad < 0)
        nbpad = 0;
    if (flags->hashtag && flags->zero)
             letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
    while (nbpad > 0)
    {
        if (flags->zero)
            ft_putchar_fd('0', fd);
        else
            ft_putchar_fd(' ', fd);
        nbpad--;
    }
    if (flags->hashtag && !flags->zero)
        letter == 'x' ? write(fd, "0x", 2) : write(fd, "0X", 2);
    return (padlen);
}

int special_convert_hex(unsigned int hex, int fd, t_flags *flags, char letter)
{
    int full_len;
    int hexlen;

    full_len = 0;
    hexlen = ft_uitoalen_base(hex, 16, fd);
    if (flags->minus)
    {
        full_len += pad_hex_prec_min(hexlen, flags, fd, hex, letter);
        return (full_len + hexlen);
    }
    full_len += pad_hex(hexlen, flags, fd, letter);
    if (letter == 'x')
    	ft_uitoaprint_base(hex, 16, fd);
    else if (letter == 'X')
	    ft_uitocapaprint_base(hex, 16, fd);
    return (full_len + hexlen);
}

int convert_hex(va_list args, int fd, t_flags *flags)
{
    unsigned int hex;
    int len;
    int hexlen;
    hex = va_arg(args, unsigned int);
    if (is_activated(flags))
        return (special_convert_hex(hex, fd, flags, 'x'));
    hexlen = ft_uitoaprint_base(hex, 16, fd);
    return (hexlen);
}

int convert_cap_hex(va_list args, int fd, t_flags *flags)
{
    unsigned int    hex;
    int             len;
    int             hexlen;

    hex = va_arg(args, unsigned int);
    if (is_activated(flags))
        return (special_convert_hex(hex, fd, flags, 'X'));
    hexlen = ft_uitocapaprint_base(hex, 16, fd);
    return (hexlen);
}
