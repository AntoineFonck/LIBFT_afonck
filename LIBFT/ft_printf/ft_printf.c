/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:24 by afonck            #+#    #+#             */
/*   Updated: 2019/06/07 16:25:51 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>
#include <stdio.h>
#include "ft_printf.h"

int is_activated(t_flags *flags)
{
	if (flags->hashtag || flags->minus || flags->plus || flags->space ||
			flags->zero || flags->field_width || flags->precision)
		return (1);
	return (0);
}

int special_convert_percent(int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->minus)
	{
		if (flags->plus)
			ft_putchar_fd('+', fd);
		ft_putchar_fd('%', fd);
		full_len += pad_this(1, flags, fd);
		return (full_len + 1);
	}
	if (flags->plus)
	{
		if (flags->zero)
			ft_putchar_fd('+', fd);
		full_len += pad_this(1, flags, fd);
		if (!flags->zero)
			ft_putchar_fd('+', fd);
		ft_putchar_fd('%', fd);
		return (full_len + 1);
	}
	full_len += pad_this(1, flags, fd);
	ft_putchar_fd('%', fd);
	return (full_len + 1);
}

int	convert_percent(va_list args, int fd, t_flags *flags)
{
	if (is_activated(flags))
		return(special_convert_percent(fd, flags));
	ft_putchar_fd('%', fd);
	return (1);
}

int special_convert_char(char c, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->minus)
	{
		ft_putchar_fd(c, fd);
		full_len += pad_this_str(1, flags, fd);
		return (full_len + 1);
	}
	if (flags->plus)
	{
		full_len += pad_this_str(1, flags, fd);
		ft_putchar_fd(c, fd);
		return (full_len + 1);
	}
	full_len += pad_this_str(1, flags, fd);
	ft_putchar_fd(c, fd);
	return (full_len + 1);
}

int	convert_char(va_list args, int fd, t_flags *flags)
{
	char c;

	c = va_arg(args, int);
	if (is_activated(flags))
		return(special_convert_char(c, fd, flags));
	ft_putchar_fd(c, fd);
	return (1);
}

int special_convert_string(char *s, int len, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->precision < len && flags->precision)
		len = flags->precision;
	if (flags->precision < 0)
		len = ft_absolute(flags->precision);
	if (flags->minus)
	{
		write(fd, s, len);
		full_len += pad_this_str(len, flags, fd);
		return (full_len + len);
	}
	if (flags->plus)
	{
		full_len += pad_this_str(len, flags, fd);
		write(fd, s, len);
		return (full_len + len);
	}
	full_len += pad_this_str(len, flags, fd);
	write(fd, s, len);
	return (full_len + len);
}

int	convert_string(va_list args, int fd, t_flags *flags)
{
	char *s;
	int len;

	s = va_arg(args, char *);
	len = ft_strlen(s);
	if (is_activated(flags))
		return(special_convert_string(s, len, fd, flags));
	write(fd, s, len);
	return (len);
}

int pad_this_str(int number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - number;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad;
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
	printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int pad_this(int number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_nbrlen(number);
	if (flags->plus || flags->space)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (flags->plus);
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
	printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int pad_this_int_prec(int number, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - flags->precision;
	if (nbpad < 0)
		nbpad = 0;
	nbzero = flags->precision - ft_nbrlen(number);
	padlen = nbpad + nbzero + (flags->plus);
	if (flags->precision < flags->field_width)
	{
		while (nbpad)
		{
			ft_putchar_fd(' ', fd);
			nbpad--;
		}
		while (nbzero)
		{
			ft_putchar_fd('0', fd);
			nbzero--;
		}
	}
	else
	{
		while (nbzero)
		{
			ft_putchar_fd('0', fd);
			nbzero--;
		}
	}
	return (padlen);
}

int pad_this_int(int number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	if (flags->precision && flags->precision > ft_nbrlen(number))
		return (pad_this_int_prec(number, flags, fd));
	nbpad = flags->field_width - ft_nbrlen(number);
	if (flags->plus)
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (flags->plus);
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
	printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int special_convert_int(int number, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->minus && !flags->precision)
	{
		if (flags->plus)
			ft_putchar_fd('+', fd);
		ft_putnbr_fd(number, fd);
		full_len += pad_this_int(number, flags, fd);
		return (full_len + ft_nbrlen(number));
	}
	if (flags->plus)
	{
		if (flags->zero || flags->precision)
			ft_putchar_fd('+', fd);
		full_len += pad_this_int(number, flags, fd);
		if (!flags->zero && !flags->precision)
			ft_putchar_fd('+', fd);
		ft_putnbr_fd(number, fd);
		return (full_len + ft_nbrlen(number));
	}
	full_len += pad_this_int(number, flags, fd);
	ft_putnbr_fd(number, fd);
	return (full_len + ft_nbrlen(number));
}

int	convert_int(va_list args, int fd, t_flags *flags)
{
	int number;

	number = va_arg(args, int);
	if (is_activated(flags))
		return(special_convert_int(number, fd, flags));
	ft_putnbr_fd(number, fd);
	return (ft_nbrlen(number));
	/*
	   if (flags->minus)
	   {
	   ft_putnbr_fd(number, fd);
	   pad_this(number, flags, fd);
	   }
	   else
	   {
	   pad_this(number, flags, fd);
	   ft_putnbr_fd(number, fd);
	   }
	   return (ft_nbrlen(number));
	   */
}

int pad_this_hex_prec(int hexlen, t_flags *flags, int fd)
{
	int nbpad;
	int nbzero;
	int padlen;

	nbpad = flags->field_width - flags->precision - (flags->hashtag ? 2 : 0);
	if (nbpad < 0)
		nbpad = 0;
	nbzero = flags->precision - hexlen;
	padlen = nbpad + nbzero + (flags->plus) + (flags->hashtag ? 2 : 0);
	if (flags->precision < flags->field_width)
	{
		while (nbpad)
		{
			ft_putchar_fd(' ', fd);
			nbpad--;
		}
		write(fd, "0x", 2);
		while (nbzero)
		{
			ft_putchar_fd('0', fd);
			nbzero--;
		}
	}
	else
	{
		write(fd, "0x", 2);
		while (nbzero)
		{
			ft_putchar_fd('0', fd);
			nbzero--;
		}
	}
	return (padlen);
}

int pad_this_hex(int hexlen, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	if (flags->precision && flags->precision > hexlen)
		return (pad_this_hex_prec(hexlen, flags, fd));
	nbpad = flags->field_width - hexlen;
	if (nbpad < 0)
		nbpad = 0;
	if (flags->hashtag)
	{
		if (flags->zero)
			write(fd, "0x", 2);
		//nbpad -= 2;
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
		write(fd, "0x", 2);
	printf("PADLEN = %d and HEXLEN = %d\n", padlen, hexlen);
	return (padlen);
}

int	special_convert_hex(unsigned int hex, int fd, t_flags *flags)
{
	int full_len;
	int hexlen;

	full_len = 0;
	hexlen = ft_uitoalen_base(hex, 16, fd);
	if (flags->minus && !flags->precision)
	{
		ft_uitoaprint_base(hex, 16, fd);
		full_len += pad_this_hex(hexlen, flags, fd);
		return (full_len + hexlen);
	}
	full_len += pad_this_hex(hexlen, flags, fd);
	ft_uitoaprint_base(hex, 16, fd);
	return (full_len + hexlen);
}

int	convert_hex(va_list args, int fd, t_flags *flags)
{
	unsigned int hex;
	int len;
	int hexlen;

	hex = va_arg(args, unsigned int);
	if (is_activated(flags))
		return(special_convert_hex(hex, fd, flags));
	hexlen = ft_uitoaprint_base(hex, 16, fd);
	return (hexlen);
}

static const t_converter	g_converters[] =
{
	{'%', convert_percent},
	{'c', convert_char},
	{'s', convert_string},
	{'d', convert_int},
	{'x', convert_hex}
};

int	do_function(char c, int fd, va_list args, t_flags *flags)
{
	int i;

	i = 0;
	while (g_converters[i].format && g_converters[i].format != c)
		i++;
	if (g_converters[i].format == c)
		return(g_converters[i].fun_ptr(args, fd, flags));
	return (0);
}

t_flags *init_flags()
{
	t_flags *flags;

	if ((flags = (t_flags *)malloc(sizeof(t_flags))) == NULL)
		return (NULL);
	flags->hashtag = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->zero = 0;
	flags->field_width = 0;
	flags->precision = 0;
	return (flags);
}

int  is_flag(char c)
{
	if (c == '#' || c == '-' || c == '+' || c == ' ' || c == '0')
		return (1);
	else
		return (0);
}

void activate_flags(t_flags *flags, char c)
{
	if (c == '#')
		flags->hashtag = 1;
	else if (c == '-')
		flags->minus = 1;
	else if (c == '+')
		flags->plus = 1;
	else if (c == ' ')
		flags->space = 1;
	else if (c == '0')
		flags->zero = 1;
	else
		return ;
}

void check_flags(const char **fmt, t_flags *flags)
{
	while (is_flag(**fmt))
	{
		activate_flags(flags, **fmt);
		printf("[DEBUG] fmt is at %p and is %c\n", (*fmt), (**fmt));
		(*fmt)++;
	}
	printf("[DEBUG] flag loop activated, flag working? hash= %d\n, minus= %d, plus= %d, space= %d, zero= %d\n\n", flags->hashtag, flags->minus, flags->plus, flags->space, flags->zero);
}

void store_field_width(const char **fmt, t_flags *flags)
{
	char field_width[10];
	int i;

	i = 0;
	ft_bzero((void *)field_width, 10);
	printf("[DEBUG] i is at %p and field_width is at %p\n", &i, &field_width);
	while (ft_isdigit(**fmt))
	{
		field_width[i] = **fmt;
		printf("[DEBUG] current field_width[%d] == %c at %p for **fmt == %c\n", i, field_width[i], &field_width[i], **fmt);
		i++;
		(*fmt)++;
	}
	printf("[HEEEEERE] %d\n", ft_atoi(field_width));
	flags->field_width = ft_atoi(field_width);
	ft_bzero((void *)field_width, 10);
	printf("[DEBUG] total field width == %d and is at %p\n", flags->field_width, &(flags->field_width));
}

void check_field_width(const char **fmt, t_flags *flags)
{
	if (!ft_isdigit(**fmt))
		return ;
	store_field_width(fmt, flags);
	/*
	   char field_width[10];
	   int i;

	   i = 0;
	   printf("[DEBUG] i is at %p and field_width is at %p\n", &i, &field_width);
	   if (!ft_isdigit(**fmt))
	   return ;
	   while (ft_isdigit(**fmt))
	   {
	   field_width[i] = **fmt;
	   printf("[DEBUG] current field_width[%d] == %c at %p for **fmt == %c\n", i, field_width[i], &field_width[i], **fmt);
	   i++;
	   (*fmt)++;
	   }
	   flags->field_width = ft_atoi(field_width);
	   ft_bzero((void *)field_width, 10);
	   printf("[DEBUG] total field width == %d and is at %p\n", flags->field_width, &(flags->field_width));
	   */
}

void store_precision(const char **fmt, t_flags *flags)
{
	char precision[10];
	int i;

	i = 0;
	ft_bzero((void *)precision, 10);
	printf("[DEBUG] i is at %p and tab precision is at %p\n", &i, &precision);
	while (ft_isdigit(**fmt) || is_flag(**fmt))
	{
		if (is_flag(**fmt))
			activate_flags(flags, **fmt);
		else
		{
			precision[i] = **fmt;
			printf("[DEBUG] current precision[%d] == %c at %p for **fmt == %c\n", i, precision[i], &precision[i], **fmt);
			i++;
		}
		(*fmt)++;
	}
	flags->precision = ft_atoi(precision);
	ft_bzero((void *)precision, 10);
	printf("[DEBUG] total precision == %d and is at %p\n", flags->precision, &(flags->precision));
}

void check_precision(const char **fmt, t_flags *flags)
{
	if (**fmt == '.')
	{
		(*fmt)++;
		//if (!ft_isdigit(**fmt))
		//	return ;
		store_precision(fmt, flags);
	}
	/*
	   char precision[10];
	   int i;

	   i = 0;
	   printf("[DEBUG] i is at %p and tab precision is at %p\n", &i, &precision);
	   if (**fmt == '.')
	   {
	   (*fmt)++;
	   if (!ft_isdigit(**fmt))
	   return ;
	   while (ft_isdigit(**fmt))
	   {
	   precision[i] = **fmt;
	   printf("[DEBUG] current precision[%d] == %c at %p for **fmt == %c\n", i, precision[i], &precision[i], **fmt);
	   i++;
	   (*fmt)++;
	   }
	   flags->precision = ft_atoi(precision);
	   printf("[DEBUG] total precision == %d and is at %p\n", flags->precision, &(flags->precision));
	   }
	   */
}

void flush_flags(t_flags *flags)
{
	flags->hashtag = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->zero = 0;
	flags->field_width = 0;
	flags->precision = 0;
}

int ft_vprintf(int fd, const char *fmt, va_list args, t_flags *flags)
{
	int tmp_int;
	char tmp_char;
	char *tmp_str;
	int total_len;

	total_len = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			check_flags(&fmt, flags);
			check_field_width(&fmt, flags);
			check_precision(&fmt, flags);
			total_len += do_function(*fmt, fd, args, flags);
			flush_flags(flags);
			fmt++;
		}
		else
		{
			ft_putchar_fd(*fmt, fd);
			total_len++;
			fmt++;
		}
	}
	return (total_len);
}

int ft_printf(const char *fmt, ...)
{
	int done;
	va_list args;
	t_flags *flags;

	if ((flags = init_flags()) == NULL)
		return (-1);
	va_start(args, fmt);
	done = ft_vprintf(1, fmt, args, flags);
	va_end(args);
	ft_memdel((void **)&flags);
	return (done);
}

int main(int argc, char *argv[])
{
	if (argc == 4)
	{
		int myone;
		int realone;
		//myone = ft_printf(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
		myone = ft_printf(argv[1], ft_atoi(argv[2]), argv[3]);
		ft_putchar('\n');
		//realone = printf(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
		realone = printf(argv[1], ft_atoi(argv[2]), argv[3]);
		printf("\nmy printf len = %d and real printf len = %d\n", myone, realone);
	}
	return (0);
}

/*
   int main(int argc, char *argv[])
   {
   if (argc == 2)
   {
   int i;
   char test;
   int len1;
   int len2;

   i = 15643;
   test = 'O';
   len1 = ft_printf("i = %d and you wrote '%s'\ntest char = %c\nand a percent alone should print a percent = %%\nhallo %d\n0x55 = 0x%x\n", i, argv[1], test, (unsigned int)&i, 0x55);
   len2 = printf("i = %d and you wrote '%s'\ntest char = %c\nand a percent alone should print a percent = %%\nhallo %d\n0x55 = 0x%x\n", i, argv[1], test, (unsigned int)&i, 0x55);
   printf("ft_printf len == %d and printf len == %d", len1, len2);
   }
   return (0);
   }
   */
