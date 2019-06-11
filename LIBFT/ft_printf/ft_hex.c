/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 11:04:22 by sluetzen          #+#    #+#             */
/*   Updated: 2019/06/11 15:13:02 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int pad_hex_prec_min(int hexlen, t_flags *flags, int fd, unsigned int hex)
{
    int nbpad;
    int nbzero;
    int padlen;

    nbpad = flags->field_width - (flags->precision >= hexlen ? flags->precision : hexlen) - (flags->hashtag ? 2 : 0);
    printf("nbpad negative? %d", nbpad);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
    // DOESN'T WORK YET FOR %#-09.02x 432333
    printf("nbzero negative? %d\n", nbzero); // COUNTING WRONG WHEN "hi %-6.1x %c hi" "1333335" "l" | cat -e
    padlen = nbpad + nbzero + /*(flags->field_width < flags->precision ? 2 : 0)*//* + (flags->plus)*/ + (flags->hashtag ? 2 : 0) + (flags->precision < hexlen ? 0 : 0);
    printf("nbpad=%d\n", nbpad);
    if (flags->hashtag)
        write(fd, "0x", 2);
    while (nbzero > 0)
    {
        ft_putchar_fd('0', fd);
        nbzero--;
    }
    ft_uitoaprint_base(hex, 16, fd, 'x');
    if (flags->precision < flags->field_width)
    {
        while (nbpad)
        {
            ft_putchar_fd(' ', fd);
            nbpad--;
        }
    }
    return (padlen);
}

int pad_hex_min(int hexlen, t_flags *flags, int fd, unsigned int hex)
{
    int nbpad;
    int padlen;
    int test;

    if (flags->precision)
        return (pad_hex_prec_min(hexlen, flags, fd, hex));
    nbpad = flags->field_width - hexlen;
    padlen = 0;
    test = hexlen + 1;
    padlen += nbpad > 0 ? nbpad : 0;
    if (nbpad < 0)
        nbpad = 0;
    if (flags->hashtag)
    {
        if (flags->zero)
        {
            write(fd, "0x", 2);
        }
        nbpad -= 2;
        if (hexlen >= flags->field_width)
            padlen += 2;
        // WORKS NOW BUT EW :D better solution? (problem: if hexlen + 1 is equal to field_width, length is being counted wrong)
        if (test == flags->field_width)
            padlen++;
    }
    //padlen = nbpad + 2;
    if (flags->hashtag && !flags->zero)
    {
        write(fd, "0x", 2);
        ft_uitoaprint_base(hex, 16, fd, 'x');
    }
    while (nbpad > 0)
    {
        ft_putchar_fd(' ', fd);
        nbpad--;
    }
    //printf("PADLEN = %d and HEXLEN = %d\n", padlen, hexlen);
    return (padlen);
}

int pad_hex_prec(int hexlen, t_flags *flags, int fd)
{
    int nbpad;
    int nbzero;
    int padlen;

    //nbpad = flags->field_width - (flags->precision >= hexlen ? flags->precision : hexlen) - (flags->hashtag ? 2 : 0);
    //printf("nbpad negative? %d", nbpad);
   // if (nbpad < 0)
    //    nbpad = 0;
   // nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
    //printf("nbzero negative? %d", nbzero);
   // padlen = nbpad + nbzero /* + (flags->plus)*/ + (flags->hashtag ? 2 : 0);
    nbpad = flags->field_width - (flags->precision >= hexlen ? flags->precision : hexlen) - (flags->hashtag ? 2 : 0);
    printf("nbpad negative? **************%d", nbpad);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
    // DOESN'T WORK YET FOR %#-09.02x 432333
    printf("nbzero negative? %d\n", nbzero); // COUNTING WRONG WHEN "hi %-6.1x %c hi" "1333335" "l" | cat -e
    padlen = nbpad + nbzero + /*(flags->field_width < flags->precision ? 2 : 0)*//* + (flags->plus)*/ + (flags->hashtag ? 2 : 0) + (flags->precision < hexlen ? 0 : 0);
    printf("nbpad=%d\n", nbpad);
    if (flags->precision < flags->field_width)
    {
        while (nbpad)
        {
            ft_putchar_fd(' ', fd);
            nbpad--;
        }
        if (flags->hashtag)
            write(fd, "0x", 2);
        while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }
    }
    else
    {
        if (flags->hashtag)
            write(fd, "0x", 2);
        while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }
    }
    return (padlen);
}

int pad_hex(int hexlen, t_flags *flags, int fd)
{
    int nbpad;
    int padlen;
    int test;

    if (flags->precision)
        return (pad_hex_prec(hexlen, flags, fd));
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
        while (nbpad > 0)
        {
            ft_putchar_fd(' ', fd);
            nbpad--;
        }
    }
    if (flags->hashtag)
    {
        if (flags->zero)
            write(fd, "0x", 2);
        nbpad -= 2;
        if (hexlen >= flags->field_width)
            padlen += 2;
        // WORKS NOW BUT EW :D better solution? (problem: if hexlen + 1 is equal to field_width, length is being counted wrong)
        if (test == flags->field_width)
            padlen++;
    }
    //padlen = nbpad + 2;
    
    if (flags->zero)
    {
        //printf("are we here %d", nbpad);
        if (flags->hashtag)
        {
            while (nbpad > 0)
            {
                ft_putchar_fd('0', fd);
                nbpad--;
            }
        }
        return (padlen);
    }
    while (nbpad > 0)
    {
        ft_putchar_fd(' ', fd);
        nbpad--;
    }
    if (flags->hashtag && !flags->zero)
        write(fd, "0x", 2);
    //printf("PADLEN = %d and HEXLEN = %d\n", padlen, hexlen);
    return (padlen);
}

int special_convert_hex(unsigned int hex, int fd, t_flags *flags)
{
    int full_len;
    int hexlen;

    full_len = 0;
    hexlen = ft_uitoalen_base(hex, 16, fd);
    if (flags->minus /*&& !flags->precision*/)
    {
        if (!flags->precision && !flags->hashtag)
            ft_uitoaprint_base(hex, 16, fd, 'x');
        full_len += pad_hex_min(hexlen, flags, fd, hex);
        return (full_len + hexlen);
    }
    full_len += pad_hex(hexlen, flags, fd);
    ft_uitoaprint_base(hex, 16, fd, 'x');
    return (full_len + hexlen);
}

int convert_hex(va_list args, int fd, t_flags *flags)
{
    unsigned int hex;
    int len;
    int hexlen;
    hex = va_arg(args, unsigned int);
    if (is_activated(flags))
        return (special_convert_hex(hex, fd, flags));
    hexlen = ft_uitoaprint_base(hex, 16, fd, 'x');
    return (hexlen);
}

int pad_cap_hex_prec(int hexlen, t_flags *flags, int fd)
{
    int nbpad;
    int nbzero;
    int padlen;

    nbpad = flags->field_width - flags->precision - (flags->hashtag ? 2 : 0);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = flags->precision - hexlen;
    padlen = nbpad + nbzero /* + (flags->plus)*/ + (flags->hashtag ? 2 : 0);
    if (flags->precision < flags->field_width)
    {
        while (nbpad)
        {
            ft_putchar_fd(' ', fd);
            nbpad--;
        }
        if (flags->hashtag)
            write(fd, "0X", 2);
        while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }
    }
    else
    {
        if (flags->hashtag)
            write(fd, "0X", 2);
        while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }
    }
    return (padlen);
}

int pad_cap_hex(int hexlen, t_flags *flags, int fd)
{
    int nbpad;
    int padlen;

    if (flags->precision && flags->precision > hexlen)
        return (pad_cap_hex_prec(hexlen, flags, fd));
    nbpad = flags->field_width - hexlen;
    padlen = 0;
    padlen += nbpad > 0 ? nbpad : 0;
    if (nbpad < 0)
        nbpad = 0;
    if (flags->hashtag)
    {
        if (flags->zero)
            write(fd, "0X", 2);
        nbpad -= 2;
        if (hexlen >= flags->field_width)
            padlen += 2;
        // DOESNT WORK WITH %#4x 452
        /*if (hexlen++ == flags->field_width)
			padlen++;*/
    }
    //padlen = nbpad + 2;
    if (flags->zero && !flags->minus)
    {
        while (nbpad > 0)
        {
            ft_putchar_fd('0', fd);
            nbpad--;
        }
        return (padlen);
    }
    while (nbpad > 0)
    {
        ft_putchar_fd(' ', fd);
        nbpad--;
    }
    if (flags->hashtag && !flags->zero)
        write(fd, "0X", 2);
    //printf("PADLEN = %d and HEXLEN = %d\n", padlen, hexlen);
    return (padlen);
}

int special_convert_cap_hex(unsigned int hex, int fd, t_flags *flags)
{
    int full_len;
    int hexlen;

    full_len = 0;
    hexlen = ft_uitoalen_base(hex, 16, fd);
    if (flags->minus && !flags->precision)
    {
        ft_uitoaprint_base(hex, 16, fd, 'X');
        full_len += pad_cap_hex(hexlen, flags, fd);
        return (full_len + hexlen);
    }
    full_len += pad_cap_hex(hexlen, flags, fd);
    ft_uitoaprint_base(hex, 16, fd, 'X');
    return (full_len + hexlen);
}

int convert_cap_hex(va_list args, int fd, t_flags *flags)
{
    unsigned int    hex;
    int             len;
    int             hexlen;

    hex = va_arg(args, unsigned int);
    if (is_activated(flags))
        return (special_convert_cap_hex(hex, fd, flags));
    hexlen = ft_uitoaprint_base(hex, 16, fd, 'X');
    return (hexlen);
}