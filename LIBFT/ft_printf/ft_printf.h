/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:35 by afonck            #+#    #+#             */
/*   Updated: 2019/06/07 16:01:13 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

int	ft_uitoaprint_base(unsigned int value, int base, int fd);

int	ft_uitoalen_base(unsigned int value, int base, int fd);

typedef	struct s_flags
{
	int hashtag;
	int minus;
	int plus;
	int space;
	int zero;
	int field_width;
	int precision;
}				t_flags;

typedef struct s_converter 
{
	char format;
	int (*fun_ptr)(va_list, int, t_flags*);
}	t_converter;

int		pad_this(int number, t_flags *flags, int fd);

int		pad_this_int(int number, t_flags *flags, int fd);

int		pad_this_str(int number, t_flags *flags, int fd);

#endif
