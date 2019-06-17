#include "../libft.h"
#include "ft_printf.h"

/*
**int special_convert_percent(int fd, t_flags *flags)
**{
**        int full_len;
**
**        full_len = 0;
**        if (flags->state & MINUS)
**        {
**                if (flags->state & PLUS)
**                        ft_putchar_fd('+', fd);
**                ft_putchar_fd('%', fd);
**                full_len += pad_percent(1, flags, fd);
**                return (full_len + 1);
**        }
**        if (flags->state & PLUS)
**        {
**                if (flags->state & ZERO)
**                        ft_putchar_fd('+', fd);
**                full_len += pad_percent(1, flags, fd);
**                if (!(flags->state & ZERO))
**                        ft_putchar_fd('+', fd);
**                ft_putchar_fd('%', fd);
**                return (full_len + 1);
**        }
**        full_len += pad_percent(1, flags, fd);
**        ft_putchar_fd('%', fd);
**        return (full_len + 1);
**}
*/
int convert_percent(va_list args, int fd, t_flags *flags)
{
        (void)args;
	(void)flags;
	/*
        **if (is_activated(flags))
        **        return (special_convert_percent(fd, flags));
	*/
        ft_putchar_fd('%', fd);
        return (1);
}
/*
**int pad_percent(int number, t_flags *flags, int fd)
**{
**        int nbpad;
**        int padlen;
**
**        nbpad = flags->field_width - ft_nbrlen(number);
**        if ((flags->state & PLUS) || (flags->state & SPACE))
**                nbpad--;
**        if (nbpad < 0)
**                nbpad = 0;
**        padlen = nbpad + (flags->state & PLUS);
**        if ((flags->state & ZERO) && !(flags->state & MINUS))
**        {
**                pad_zero(nbpad, fd);
**                return (padlen);
**        }
**        pad_space(nbpad, fd);
**        return (padlen);
**}
*/
