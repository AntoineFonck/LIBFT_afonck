#include "../libft.h"
#include "ft_printf.h"

int pad_uint_prec(uintmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - (flags->precision >= ft_unbrlen(number)
			? flags->precision : ft_unbrlen(number));
	if (((flags->state & PLUS) || (flags->state & SPACE)))
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= ft_unbrlen(number) ? flags->precision : ft_unbrlen(number))
		- ft_unbrlen(number);
	padlen = nbpad + nbzero + ((flags->state & PLUS) || (flags->state & SPACE));
	if (!(flags->state & MINUS))
		pad_space(nbpad, fd);
	pad_zero(nbzero, fd);
	ft_uitoaprint_base(number, 10, fd);
	if (flags->state & MINUS)
		pad_space(nbpad, fd);
	return (padlen);
}

int uint_precision(uintmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->state & MINUS))
	{
		len += pad_uint_prec(number, flags, fd);
		//if ((flags->state & PLUS) && flags->field_width > flags->precision && number >= 0)
		//	ft_putchar_fd('+', fd);
	}
	else
	{
		//if ((flags->state & PLUS) && number > 0)
		//	ft_putchar_fd('+', fd);
		len += pad_uint_prec(number, flags, fd);
	}
	return (len);
}

int uint_no_precision(uintmax_t number, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->state & MINUS))
	{
		len += pad_uint(number, flags, fd);
		ft_uitoaprint_base(number, 10, fd);
	}
	else
	{
		ft_uitoaprint_base(number, 10, fd);
		len += pad_uint(number, flags, fd);
	}
	return (len);
}

int pad_uint(uintmax_t number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_unbrlen(number);
	printf("nbrlen is %d\n", ft_unbrlen(number));
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad;
	if ((flags->state & ZERO) && !(flags->state & MINUS))
	{
		if ((flags->state & SPACE) && !(flags->state & PLUS))
		{
			ft_putchar_fd(' ', fd);
			nbpad--;
		}
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
	printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int special_convert_uint(uintmax_t number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision)
		full_len += uint_precision(number, fd, flags);
	else
		full_len += uint_no_precision(number, fd, flags);
	return (full_len + ft_unbrlen(number));
}

int convert_uint(va_list args, int fd, t_flags *flags)
{
	uintmax_t number;

	if (flags->state & HH)
            number = (unsigned char)va_arg(args, unsigned int);
    	else if (flags->state & H)
            number = (unsigned short)va_arg(args, unsigned int);
    	else if (flags->state & L)
            number = (unsigned long)va_arg(args, unsigned long);
    	else if (flags->state & LL)
            number = (unsigned long long)va_arg(args, unsigned long long);
    	else
	    number = va_arg(args, unsigned int);
	if (is_activated(flags))
		return (special_convert_uint(number, fd, flags));
	ft_uitoaprint_base(number, 10, fd);
	return (ft_unbrlen(number));
}
