#include "../libft.h"
#include "ft_printf.h"

int pad_str(int number, t_flags *flags, int fd)
{
        int nbpad;
        int padlen;

        nbpad = flags->field_width - number;
        if (nbpad < 0)
                nbpad = 0;
        padlen = nbpad;
        if ((flags->state & ZERO) && !(flags->state & MINUS))
        {
                pad_zero(nbpad, fd);
                return (padlen);
        }
        pad_space(nbpad, fd);
        return (padlen);
}

int special_convert_string(char *s, int len, int fd, t_flags *flags)
{
        int full_len;

        full_len = 0;
        if (flags->precision < len && flags->precision)
                len = flags->precision;
	else if (!flags->precision && (flags->state & PREC))
		len = 0;
        if (flags->state & MINUS)
        {
		if (len > 0)
                	write(fd, s, len);
                full_len += pad_str(len, flags, fd);
                return (full_len + len);
        }
        if (flags->state & PLUS)
        {
                full_len += pad_str(len, flags, fd);
		if (len > 0)
                	write(fd, s, len);
                return (full_len + len);
        }
        full_len += pad_str(len, flags, fd);
	if (len > 0)
        	write(fd, s, len);
        return (full_len + len);
}

int convert_string(va_list args, int fd, t_flags *flags)
{
        char *s;
        int len;

        s = va_arg(args, char *);
        len = ft_strlen(s);
        if (is_activated(flags) || (flags->state & PREC))
                return (special_convert_string(s, len, fd, flags));
        write(fd, s, len);
        return (len);
}
