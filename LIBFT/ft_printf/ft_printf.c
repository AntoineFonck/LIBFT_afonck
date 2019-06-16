/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:24 by afonck            #+#    #+#             */
/*   Updated: 2019/06/14 13:24:30 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int is_activated(t_flags *flags)
{
	if ((flags->state & HASHTAG) || (flags->state & MINUS) || (flags->state & PLUS)
	|| (flags->state & SPACE) || (flags->state & ZERO) || flags->field_width || flags->precision)
		return (1);
	return (0);
}

int special_convert_percent(int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->state & MINUS)
	{
		if (flags->state & PLUS)
			ft_putchar_fd('+', fd);
		ft_putchar_fd('%', fd);
		full_len += pad(1, flags, fd);
		return (full_len + 1);
	}
	if (flags->state & PLUS)
	{
		if (flags->state & ZERO)
			ft_putchar_fd('+', fd);
		full_len += pad(1, flags, fd);
		if (!(flags->state & ZERO))
			ft_putchar_fd('+', fd);
		ft_putchar_fd('%', fd);
		return (full_len + 1);
	}
	full_len += pad(1, flags, fd);
	ft_putchar_fd('%', fd);
	return (full_len + 1);
}

int convert_percent(va_list args, int fd, t_flags *flags)
{
	(void)args;
	if (is_activated(flags))
		return (special_convert_percent(fd, flags));
	ft_putchar_fd('%', fd);
	return (1);
}

int special_convert_char(char c, int fd, t_flags *flags)
{
	int full_len;

	full_len = 0;
	if (flags->state & MINUS)
	{
		ft_putchar_fd(c, fd);
		full_len += pad_str(1, flags, fd);
		return (full_len + 1);
	}
	if (flags->state & PLUS)
	{
		full_len += pad_str(1, flags, fd);
		ft_putchar_fd(c, fd);
		return (full_len + 1);
	}
	full_len += pad_str(1, flags, fd);
	ft_putchar_fd(c, fd);
	return (full_len + 1);
}

int convert_char(va_list args, int fd, t_flags *flags)
{
	char c;

	c = va_arg(args, int);
	if (is_activated(flags))
		return (special_convert_char(c, fd, flags));
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
	if (flags->state & MINUS)
	{
		write(fd, s, len);
		full_len += pad_str(len, flags, fd);
		return (full_len + len);
	}
	if (flags->state & PLUS)
	{
		full_len += pad_str(len, flags, fd);
		write(fd, s, len);
		return (full_len + len);
	}
	full_len += pad_str(len, flags, fd);
	write(fd, s, len);
	return (full_len + len);
}

int convert_string(va_list args, int fd, t_flags *flags)
{
	char *s;
	int len;

	s = va_arg(args, char *);
	len = ft_strlen(s);
	if (is_activated(flags))
		return (special_convert_string(s, len, fd, flags));
	write(fd, s, len);
	return (len);
}

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
		/* while (nbpad > 0)
		{
			ft_putchar_fd('0', fd);
			nbpad--;
		}*/
		return (padlen);
	}
	pad_space(nbpad, fd);
	/* while (nbpad > 0)
	{
		ft_putchar_fd(' ', fd);
		nbpad--;
	}*/
	printf("PADLEN = %d\n", padlen);
	return (padlen);
}

int pad(int number, t_flags *flags, int fd)
{
	int nbpad;
	int padlen;

	nbpad = flags->field_width - ft_nbrlen(number);
	if ((flags->state & PLUS) || (flags->state & SPACE))
		nbpad--;
	if (nbpad < 0)
		nbpad = 0;
	padlen = nbpad + (flags->state & PLUS);
	if ((flags->state & ZERO) && !(flags->state & MINUS))
	{
		pad_zero(nbpad, fd);
		/*while (nbpad > 0)
		{
			ft_putchar_fd('0', fd);
			nbpad--;
		}*/
		return (padlen);
	}
	pad_space(nbpad, fd);
	/* while (nbpad > 0)
	{
		ft_putchar_fd(' ', fd);
		nbpad--;
	}*/
	//printf("PADLEN = %d\n", padlen);
	return (padlen);
}

static const t_converter g_converters[] =
	{
		{'%', convert_percent},
		{'c', convert_char},
		{'s', convert_string},
		{'d', convert_int},
		{'i', convert_int},
		{'o', convert_oct},
		{'u', convert_uint},
		{'x', convert_hex},
		{'X', convert_cap_hex},
		{'p', convert_pointer}
	};

int do_function(char c, int fd, va_list args, t_flags *flags)
{
	int i;

	i = 0;
	while (g_converters[i].format && g_converters[i].format != c)
		i++;
	if (g_converters[i].format == c)
		return (g_converters[i].fun_ptr(args, fd, flags));
	return (0);
}

t_flags *init_flags()
{
	t_flags *flags;

	if ((flags = (t_flags *)malloc(sizeof(t_flags))) == NULL)
		return (NULL);
	flags->state = 0;
	flags->field_width = 0;
	flags->precision = 0;
	return (flags);
}

int is_flag(char c)
{
	if (c == '#' || c == '-' || c == '+' || c == ' ' || c == '0')
		return (1);
	else
		return (0);
}

void activate_flags(t_flags *flags, char c)
{
	/* activate them in nearly the equivalent of doing += for each flag (HASHTAG + MINUS for example if both are activated), using | (OR) instead for a very gud reason: if a flag is repeated twice (%##x for instance), the += logic would give this result: flags->state += HASHTAG so flags->state is now equal 1 (0000 0001) BUT if you repeat this operation (second hashtag in format %##d) you get this: flags->state += HASHTAG is equal to 2 which is WRONG (would randomly activate flags MINUS because MINUS = 2 (0000 0010)).
	   SO the solution is to use OR (|) instead of + because 1 (0000 0001) | 1 (0000 0001) is still equal to 1 (0000 0001) ;D
	   */
	if (c == '#')
		flags->state |= HASHTAG;
	else if (c == '-')
		flags->state |= MINUS;
	else if (c == '+')
		flags->state |= PLUS;
	else if (c == ' ')
		flags->state |= SPACE;
	else if (c == '0')
		flags->state |= ZERO;
	else
		return;
}

void check_flags(const char **fmt, t_flags *flags)
{
	while (is_flag(**fmt))
	{
		activate_flags(flags, **fmt);
		//printf("[DEBUG] fmt is at %p and is %c\n", (*fmt), (**fmt));
		(*fmt)++;
	}
	//printf("[DEBUG] flag loop activated, flag working? hash= %d\n, minus= %d, plus= %d, space= %d, zero= %d\n\n", flags->hashtag, flags->minus, flags->plus, flags->space, flags->zero);
}

void store_field_width(const char **fmt, t_flags *flags)
{
	char field_width[10];
	int i;

	i = 0;
	ft_bzero((void *)field_width, 10);
	//printf("[DEBUG] i is at %p and field_width is at %p\n", &i, &field_width);
	while (ft_isdigit(**fmt) && i < 10)
	{
		field_width[i] = **fmt;
		//printf("[DEBUG] current field_width[%d] == %c at %p for **fmt == %c\n", i, field_width[i], &field_width[i], **fmt);
		i++;
		(*fmt)++;
	}
	while (ft_isdigit(**fmt))
		(*fmt)++;
	//printf("[HEEEEERE] %d\n", ft_atoi(field_width));
	//flags->field_width = ft_atoi(field_width);
	flags->field_width = (ft_atoi(field_width) > 0 ? ft_atoi(field_width) : 0);
	ft_bzero((void *)field_width, 10);
	//printf("[DEBUG] total field width == %d and is at %p\n", flags->field_width, &(flags->field_width));
}

void check_field_width(const char **fmt, t_flags *flags)
{
	if (!ft_isdigit(**fmt))
		return;
	store_field_width(fmt, flags);
}

void store_precision(const char **fmt, t_flags *flags)
{
	char precision[10];
	int i;

	i = 0;
	ft_bzero((void *)precision, 10);
	//printf("[DEBUG] i is at %p and tab precision is at %p\n", &i, &precision);
	while ((ft_isdigit(**fmt) || is_flag(**fmt)) && i < 10)
	{
		precision[i] = **fmt;
		//printf("[DEBUG] current precision[%d] == %c at %p for **fmt == %c\n", i, precision[i], &precision[i], **fmt);
		i++;
		(*fmt)++;
	}
	while (ft_isdigit(**fmt))
		(*fmt)++;
	//flags->precision = ft_atoi(precision);
	flags->precision = (ft_atoi(precision) > 0 ? ft_atoi(precision) : 0);
	ft_bzero((void *)precision, 10);
	//printf("[DEBUG] total precision == %d and is at %p\n", flags->precision, &(flags->precision));
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
}

void check_lmod(const char **fmt, t_flags *flags)
{
	if (**fmt == 'h')
	{
		(*fmt)++;
		if (**fmt == 'h')
		{
			flags->state |= HH;
			(*fmt)++;
		}
		else
			flags->state |= H;
	}
	else if (**fmt == 'l')
	{
		(*fmt)++;
		if (**fmt == 'l')
		{
			flags->state |= LL;
			(*fmt)++;
		}
		else
			flags->state = L;
	}
}

void flush_flags(t_flags *flags)
{
	flags->state = 0;
	flags->field_width = 0;
	flags->precision = 0;
}

void check_all(const char **fmt, t_flags *flags)
{
	check_flags(fmt, flags);
	check_field_width(fmt, flags);
	check_precision(fmt, flags);
	check_lmod(fmt, flags);
}

int ft_vprintf(int fd, const char *fmt, va_list args, t_flags *flags)
{
	int total_len;

	total_len = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			//check_flags(&fmt, flags);
			//check_field_width(&fmt, flags);
			//check_precision(&fmt, flags);
			check_all(&fmt, flags);
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
		char *test;
		int myone;
		char hi = 'h';
		test = &hi;
		int realone;
		//myone = ft_printf(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
		myone = ft_printf(argv[1], ft_atol(argv[2]), argv[3][0], test);
		ft_putchar('\n');
		//realone = printf(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]));
		realone = printf(argv[1], ft_atol(argv[2]), argv[3][0], test);
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
