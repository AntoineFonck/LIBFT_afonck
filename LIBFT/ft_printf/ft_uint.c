#include "../libft.h"
#include "ft_printf.h"

int pad_uint_prec(unsigned int number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - (flags->precision >= ft_unbrlen(number) ? flags->precision : ft_unbrlen(number)) - (number < 0 ? 1 : 0);
	if (((flags->state & PLUS) || (flags->state & SPACE)) && number >= 0)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = (flags->precision >= ft_unbrlen(number) ? flags->precision : ft_unbrlen(number)) - ft_unbrlen(number) + (number < 0 ? 1 : 0);
	padlen = nbpad + nbzero + (number >= 0 ? (flags->state & PLUS) || (flags->state & SPACE) : 0);
	printf("nbpad=%d, nbzero=%d, padlen=%d\n", nbpad, nbzero, padlen);
	if (!(flags->state & MINUS))
		pad_space(nbpad, fd);
	pad_zero(nbzero, fd);
	ft_uitoaprint_base(number, 10, fd);
	if ((flags->state & MINUS))
		pad_space(nbpad, fd);
	return (padlen);
}

int uint_precision(unsigned int number, int fd, t_flags *flags)
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

int uint_no_precision(unsigned int number, int fd, t_flags *flags)
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

int pad_uint(unsigned int number, t_flags *flags, int fd)
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

int special_convert_uint(unsigned int number, int fd, t_flags *flags)
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
	int number;

	number = va_arg(args, unsigned int);
	if (is_activated(flags))
		return (special_convert_uint(number, fd, flags));
	ft_uitoaprint_base(number, 10, fd);
	return (ft_unbrlen(number));
}
