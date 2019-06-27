/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:24 by afonck            #+#    #+#             */
/*   Updated: 2019/06/27 16:03:49 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

//FLAG FUNCTION
int	is_activated(t_flags *flags)
{
	if ((HASH_FLAG) || (MIN_FLAG) || (PLUS_FLAG)
			|| (SPACE_FLAG) || (ZERO_FLAG) || flags->field_width || flags->precision)
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

//FLAG FUNCTION
t_flags *init_flags()
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
//FLAG FUNCTION
int		is_flag(char c)
{
	if (c == '#' || c == '-' || c == '+' || c == ' ' || c == '0')
		return (1);
	else
		return (0);
}
//FLAG FUNCTION
void	activate_flags(t_flags *flags, char c)
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
//FLAG FUNCTION
void	check_flags(const char **fmt, t_flags *flags)
{
	while (is_flag(**fmt))
	{
		activate_flags(flags, **fmt);
		//printf("[DEBUG] fmt is at %p and is %c\n", (*fmt), (**fmt));
		(*fmt)++;
	}
	//printf("[DEBUG] flag loop activated, flag working? hash= %d\n, minus= %d, plus= %d, space= %d, zero= %d\n\n", flags->hashtag, flags->minus, flags->plus, flags->space, flags->zero);
}

void	store_field_width(const char **fmt, t_flags *flags)
{
	char	field_width[10];
	int		i;

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

void	check_field_width(const char **fmt, t_flags *flags)
{
	if (!ft_isdigit(**fmt))
		return;
	store_field_width(fmt, flags);
}

void	store_precision(const char **fmt, t_flags *flags)
{
	char	precision[10];
	int		i;

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

void	check_precision(const char **fmt, t_flags *flags)
{
	if (**fmt == '.')
	{
		flags->state |= PREC;
		(*fmt)++;
		//if (!ft_isdigit(**fmt))
		//	return ;
		store_precision(fmt, flags);
	}
}
//FILE FLAGS
void	activate_biglmod(const char **fmt, t_flags *flags)
{
	(*fmt)++;
	flags->state |= BIGL;
}
// FILE FLAGS
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

//BONUS FILE
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

// BONUS FILE
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

// CAN GO IN LIBFT AND NEEDS TO REMOVE ONE LINE
float	ft_atof(const char *s)
{
	float	res;
	float	fact;
	int		d;
	int		point_seen;

	res = 0;
	fact = 1;
	d = 0;
	point_seen = 0;
	if (*s == '-')
	{
		s++;
		fact = -1;
	}
	while (*s)
	{
		if (*s == '.')
			point_seen = 1;
		d = *s - '0';
		if (d >= 0 && d <= 9)
		{
			if (point_seen)
				fact /= 10.0f;
			res = res * 10.0f + (float)d;
		}
		s++;
	}
	return (res * fact);
}
