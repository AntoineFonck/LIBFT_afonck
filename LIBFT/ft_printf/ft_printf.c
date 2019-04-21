#include "../libft.h"
#include <stdarg.h>

int do_function(int fd, char c, va_list args)
{
	if (c == '%')
	{
		ft_putchar_fd('%', fd);
		return (1);
	}
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), fd);
		return (1);
	}
	if (c == 's')
	{
		ft_putstr_fd(va_arg(args, char *), fd);
		//return (ft_strlen(tmp_str));
		return (1);
	}
	if (c == 'd')
	{
		ft_putnbr_fd(va_arg(args, int), fd);
		return (1);
	}
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
			total_len += do_function(fd, *fmt, args);
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
		ft_printf("i = %d and you wrote '%s'\ntest char = %c\nand a percent alone should print a percent = %%\n", i, argv[1], test);
	}
	return (0);
}
