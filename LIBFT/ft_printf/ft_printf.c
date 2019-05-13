/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:24 by afonck            #+#    #+#             */
/*   Updated: 2019/05/13 16:02:01 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>
#include <stdio.h>
#include "ft_printf.h"

int	convert_percent(va_list args, int *fd)
{
	ft_putchar_fd('%', *fd);
	return (1);
}

int	convert_char(va_list args, int *fd)
{
	ft_putchar_fd(va_arg(args, int), *fd);
	return (1);
}

int	convert_string(va_list args, int *fd)
{
	char *s;
	int len;

	s = va_arg(args, char *);
	len = ft_strlen(s);
	write(*fd, s, len);
	return (len);
}

void pad_this(int number, t_flags *flags, int *fd)
{
	int nbpad;

	nbpad = flags->field_width - ft_nbrlen(number);
	if (flags->zero)
	{
		while (nbpad > 0)
		{
			ft_putchar('0');
			nbpad--;
		}
		return ;
	}
	while (nbpad > 0)
	{
		ft_putchar(' ');
		nbpad--;
	}
	return ;
}

int	convert_int(va_list args, int *fd, t_flags *flags)
{
	int number;
	//int numlen;

	number = va_arg(args, int);
	if (flags->minus)
	{
	//numlen = ft_nbrlen(number);
		ft_putnbr_fd(number, *fd);
		pad_this(number, flags, fd);
	}
	else
	{
		pad_this(number, flags, fd);
		ft_putnbr_fd(number, *fd);
	}
	return (ft_nbrlen(number));
}

int	convert_hex(va_list args, int *fd)
{
	unsigned int hex;
	int len;

	hex = va_arg(args, unsigned int);
	ft_uitoaprint_base(hex, 16, *fd);
	return (ft_nbrlen(hex));
}

static const t_converter	g_converters[] =
{
	{'%', FALSE, convert_percent},
	{'c', TRUE, convert_char},
	{'s', TRUE, convert_string},
	{'d', TRUE, convert_int},
	{'x', TRUE, convert_hex}
};

int	do_function(char c, int *fd, va_list args, t_flags *flags)
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
	printf("[DEBUG] i is at %p and field_width is at %p\n", &i, &field_width);
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
	printf("[DEBUG] i is at %p and tab precision is at %p\n", &i, &precision);
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

void check_precision(const char **fmt, t_flags *flags)
{
	if (**fmt == '.')
	{
		(*fmt)++;
		if (!ft_isdigit(**fmt))
			return ;
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
			total_len += do_function(*fmt, &fd, args, flags);
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
		ft_printf(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
		ft_putchar('\n');
		printf(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
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
