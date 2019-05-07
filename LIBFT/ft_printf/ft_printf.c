/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:24 by afonck            #+#    #+#             */
/*   Updated: 2019/05/07 18:52:08 by afonck           ###   ########.fr       */
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

int	convert_int(va_list args, int *fd)
{
	int number;
	int numlen;

	number = va_arg(args, int);
	numlen = ft_nbrlen(number);
	ft_putnbr_fd(number, *fd);
	return (numlen);
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

int	do_function(char c, int *fd, va_list args)
{
	int i;

	i = 0;
	while (g_converters[i].format && g_converters[i].format != c)
		i++;
	if (g_converters[i].format == c)
		return(g_converters[i].fun_ptr(args, fd));
	return (0);
}

int ft_vprintf(int fd, const char *fmt, va_list args)
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
			total_len += do_function(*fmt, &fd, args);
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

	va_start(args, fmt);
	done = ft_vprintf(1, fmt, args);
	va_end(args);
	return (done);
}

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
