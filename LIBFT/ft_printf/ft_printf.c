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

static const t_converter	g_converters[] =
{
	{'%', FALSE, convert_percent},
	{'c', TRUE, convert_char},
	{'s', TRUE, convert_string},
	{'d', TRUE, convert_int}
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

		i = 15643;
		test = 'O';
		ft_printf("i = %d and you wrote '%s'\ntest char = %c\nand a percent alone should print a percent = %%\nhallo %d\n", i, argv[1], test, (unsigned int)&i);
		printf("real printf = %d\n", (unsigned int)&i);
	}
	return (0);
}
