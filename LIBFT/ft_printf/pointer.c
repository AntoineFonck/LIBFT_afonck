#include "../libft.h"
#include "ft_printf.h"

int pad_pointer_prec_min(int hexlen, t_flags *flags, int fd, uintptr_t hex)
{
    int nbpad;
    int nbzero;
    int padlen;

    nbpad = flags->field_width - (flags->precision >= hexlen ? flags->precision : hexlen) - (flags->hashtag ? 2 : 0);
    //printf("nbpad negative? %d", nbpad);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
    padlen = nbpad + nbzero + (flags->hashtag ? 2 : 0) + (flags->precision < hexlen ? 0 : 0);
    //printf("nbpad=%d\n", nbpad);
    write(fd, "0x", 2);
    while (nbzero > 0)
    {
        ft_putchar_fd('0', fd);
        nbzero--;
    }
    ft_uintptrtoaprint_base(hex, 16, fd);
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

int pad_pointer_prec(int hexlen, t_flags *flags, int fd)
{
    int nbpad;
    int nbzero;
    int padlen;
    nbpad = flags->field_width - (flags->precision >= hexlen ? flags->precision : hexlen) - (flags->hashtag ? 2 : 0);
    if (nbpad < 0)
        nbpad = 0;
    nbzero = (flags->precision >= hexlen ? flags->precision : hexlen) - hexlen;
    // DOESN'T WORK YET FOR %#-09.02x 432333
    //printf("nbzero negative? %d\n", nbzero); // COUNTING WRONG WHEN "hi %-6.1x %c hi" "1333335" "l" | cat -e
    padlen = nbpad + nbzero + /*(flags->field_width < flags->precision ? 2 : 0)*//* + (flags->plus)*/ + (flags->hashtag ? 2 : 0) + (flags->precision < hexlen ? 0 : 0);
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
        write(fd, "0x", 2);
        while (nbzero > 0)
        {
            ft_putchar_fd('0', fd);
            nbzero--;
        }
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

    //flags->hashtag = 1;
    hex = va_arg(args, uintptr_t);
    if (is_activated(flags))
        return (special_convert_pointer(hex, fd, flags));
    printf("uintptr_t = %lu\n", sizeof(uintptr_t));
    write(fd, "0x", 2);
    hexlen = ft_uintptrtoaprint_base(hex, 16, fd);
    return (hexlen + 2);
}
