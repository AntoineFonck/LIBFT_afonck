/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:24 by afonck            #+#    #+#             */
/*   Updated: 2019/07/05 13:54:27 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		is_activated(t_flags *flags)
{
	if ((HASH_FLAG) || (MIN_FLAG) || (PLUS_FLAG)
			|| (SPACE_FLAG) || (ZERO_FLAG)
			|| flags->field_width || flags->precision)
		return (1);
	return (0);
}

static const	t_converter g_converters[] =
{
	{'%', convert_percent},
	{'c', convert_char},
	{'C', convert_wchar},
	{'s', convert_string},
	{'S', convert_wstring},
	{'d', convert_int},
	{'i', convert_int},
	{'o', convert_oct},
	{'u', convert_uint},
	{'x', convert_hex},
	{'X', convert_cap_hex},
	{'p', convert_pointer},
	{'b', convert_bin},
	{'f', convert_float}
};

int		do_function(char c, int fd, va_list args, t_flags *flags)
{
	int i;

	i = 0;
	while (i < (NBFORMATS - 1) && g_converters[i].format != c)
		i++;
	if (g_converters[i].format == c)
		return (g_converters[i].fun_ptr(args, fd, flags));
	return (0);
}

t_flags	*init_flags(void)
{
	t_flags *flags;

	if ((flags = (t_flags *)malloc(sizeof(t_flags))) == NULL)
		return (NULL);
	flags->state = 0;
	flags->field_width = 0;
	flags->precision = 0;
	flags->color = 0;
	return (flags);
}

int		is_flag(char c)
{
	if (c == '#' || c == '-' || c == '+' || c == ' ' || c == '0')
		return (1);
	else
		return (0);
}

void	activate_flags(t_flags *flags, char c)
{
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
		return ;
}

void	check_flags(const char **fmt, t_flags *flags)
{
	while (is_flag(**fmt))
	{
		activate_flags(flags, **fmt);
		(*fmt)++;
	}
}

void	activate_biglmod(const char **fmt, t_flags *flags)
{
	(*fmt)++;
	flags->state |= BIGL;
}

void	check_lmod(const char **fmt, t_flags *flags)
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
			flags->state |= L;
	}
	else if (**fmt == 'L')
		activate_biglmod(fmt, flags);
}

void	check_color(const char **fmt, t_flags *flags)
{
	if (**fmt == '{')
	{
		(*fmt)++;
		if (**fmt == 'r')
			flags->color = 1;
		else if (**fmt == 'g')
			flags->color = 2;
		else if (**fmt == 'y')
			flags->color = 3;
		else if (**fmt == 'b')
			flags->color = 4;
		else if (**fmt == 'm')
			flags->color = 5;
		else if (**fmt == 'c')
			flags->color = 6;
		(*fmt)++;
		if (**fmt == '}')
			(*fmt)++;
		else
			flags->color = 0;
	}
}

void	flush_flags(t_flags *flags)
{
	flags->state = 0;
	flags->field_width = 0;
	flags->precision = 0;
	flags->color = 0;
}

void	check_all(const char **fmt, t_flags *flags)
{
	check_flags(fmt, flags);
	check_field_width(fmt, flags);
	check_precision(fmt, flags);
	check_lmod(fmt, flags);
	check_color(fmt, flags);
}

void	choose_color(int fd, int color)
{
	if (color == 1)
		write(fd, RED, COLORLEN);
	else if (color == 2)
		write(fd, GREEN, COLORLEN);
	else if (color == 3)
		write(fd, YELLOW, COLORLEN);
	else if (color == 4)
		write(fd, BLUE, COLORLEN);
	else if (color == 5)
		write(fd, MAGENTA, COLORLEN);
	else if (color == 6)
		write(fd, CYAN, COLORLEN);
}

int		ft_vprintf(int fd, const char *fmt, va_list args, t_flags *flags)
{
	int total_len;

	total_len = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			check_all(&fmt, flags);
			choose_color(fd, flags->color);
			total_len += do_function(*fmt, fd, args, flags);
			if (flags->color)
				write(fd, RESET, 4);
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

int		ft_printf(const char *fmt, ...)
{
	int		done;
	va_list	args;
	t_flags	*flags;

	if ((flags = init_flags()) == NULL)
		return (-1);
	va_start(args, fmt);
	done = ft_vprintf(1, fmt, args, flags);
	va_end(args);
	ft_memdel((void **)&flags);
	return (done);
}
