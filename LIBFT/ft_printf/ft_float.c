#include "../libft.h"
#include "ft_printf.h"

int pad_float_prec(double number, int preclen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;
	int nbrlen;

	nbrlen = ft_floatlen(number) - (number < 0 ? 1 : 0);
	nbpad = flags->field_width - (flags->precision >= nbrlen ? flags->precision : nbrlen) \
		- (number < 0 ? 1 : 0) - (((flags->state & PLUS) || (flags->state & SPACE)) && number >= 0 ? 1 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= nbrlen ? flags->precision : nbrlen) - nbrlen;
	padlen = nbpad + nbzero + (number >= 0 ? (flags->state & PLUS) || (flags->state & SPACE) : 0);
	if (!(flags->state & MINUS))
		pad_space(nbpad, fd);
	if ((flags->state & PLUS) && number >= 0)
		ft_putchar_fd('+', fd);
	if ((flags->state & SPACE) && number >= 0 && !(flags->state & PLUS))
		ft_putchar_fd(' ', fd);
	if (number < 0)
		ft_putchar_fd('-', fd);
	pad_zero(nbzero, fd);
	ft_ftoa(number, preclen, fd);
	if ((flags->state & MINUS))
		pad_space(nbpad, fd);
	return (padlen);
}

int float_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->state & MINUS))
	{
		len += pad_float_prec(number, preclen, flags, fd);
		//if ((flags->state & PLUS) && flags->field_width > flags->precision && number >= 0)
		//	ft_putchar_fd('+', fd);
	}
	else
	{
		//if ((flags->state & PLUS) && number > 0)
		//	ft_putchar_fd('+', fd);
		if (number < 0 && (flags->state & ZERO))
			ft_putchar_fd('-', fd);
		len += pad_float_prec(number, preclen, flags, fd);
	}
	return (len);
}

int float_no_precision(double number, int preclen, int fd, t_flags *flags)
{
	int len;

	len = 0;
	if (!(flags->state & MINUS))
	{
		if ((flags->state & PLUS) && (flags->state & ZERO) && number >= 0)
			ft_putchar_fd('+', fd);
		if (number < 0 && (flags->state & ZERO))
			ft_putchar_fd('-', fd);
		len += pad_float(number, flags, fd);
		if ((flags->state & PLUS) && !(flags->state & ZERO) && number >= 0)
			ft_putchar_fd('+', fd);
		ft_ftoa(number, preclen, fd);
	}
	else if ((flags->state & MINUS))
	{
		if ((flags->state & PLUS) && number >= 0)
			ft_putchar_fd('+', fd);
		else if ((flags->state & SPACE) && number >= 0)
			ft_putchar_fd(' ', fd);
		ft_ftoa(number, preclen, fd);
		len += pad_float(number, flags, fd);
	}
	return (len);
}

int pad_float(double number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_floatlen(number);
	if (((flags->state & PLUS) || (flags->state & SPACE)) && number >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (number >= 0 ? (flags->state & PLUS) || (flags->state & SPACE) : 0);
	if ((flags->state & ZERO) && !(flags->state & MINUS))
	{
		if ((flags->state & SPACE) && !(flags->state & PLUS) && number >= 0)
			ft_putchar_fd(' ', fd);
		pad_zero(nbpad, fd);
		printf("PADLEN = %d\n", padlen);
		return (padlen);
	}
	if ((flags->state & SPACE) && !(flags->state & PLUS) && number >= 0)
		ft_putchar_fd(' ', fd);
	pad_space(nbpad, fd);
	if (number < 0 && !(flags->state & MINUS))
		ft_putchar_fd('-', fd);
	printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int special_convert_float(double number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision)
		full_len += float_precision(number, flags->precision, fd, flags);
	else if (!flags->precision && (flags->state & PREC))
		full_len += float_precision(number, 0, fd, flags);
	else
		full_len += float_no_precision(number, 6, fd, flags);
	return (full_len + ft_floatlen(number));
}

int convert_float(va_list args, int fd, t_flags *flags)
{
	double number;
	int nblen;

	nblen = 0;
	number = va_arg(args, double);
	if (is_activated(flags) || (flags->state & PREC))
		return (special_convert_float(number, fd, flags));
	nblen += ft_ftoa(number, 6, fd);
	return (nblen);
}
