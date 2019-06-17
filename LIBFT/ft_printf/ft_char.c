#include "../libft.h"
#include "ft_printf.h"

int special_convert_char(char c, int fd, t_flags *flags)
{
        int full_len;

        full_len = 0;
        if (flags->state & MINUS)
        {
                ft_putchar_fd(c, fd);
                full_len += pad_str(1, flags, fd);
                return (full_len + 1);
        }
        if (flags->state & PLUS)
        {
                full_len += pad_str(1, flags, fd);
                ft_putchar_fd(c, fd);
                return (full_len + 1);
        }
        full_len += pad_str(1, flags, fd);
        ft_putchar_fd(c, fd);
        return (full_len + 1);
}

int convert_char(va_list args, int fd, t_flags *flags)
{
        char c;

        c = va_arg(args, int);
        if (is_activated(flags))
                return (special_convert_char(c, fd, flags));
        ft_putchar_fd(c, fd);
        return (1);
}
