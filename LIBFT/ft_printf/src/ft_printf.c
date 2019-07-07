/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:24 by afonck            #+#    #+#             */
/*   Updated: 2019/07/06 15:27:50 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

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
	//PUT CHOOSE_COLOR HERE?? and remove in vprintf -> then move to bonus.c
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

void	check_all(const char **fmt, t_flags *flags)
{
	check_flags(fmt, flags);
	check_field_width(fmt, flags);
	check_precision(fmt, flags);
	check_lmod(fmt, flags);
	check_color(fmt, flags);
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
			choose_color(fd, flags->color); //put call into check_color?
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
