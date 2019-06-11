/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:35 by afonck            #+#    #+#             */
/*   Updated: 2019/06/11 11:32:35 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

int	ft_uitoaprint_base(unsigned int value, int base, int fd, char letter);

int	ft_uitoalen_base(unsigned int value, int base, int fd);

void pad_zero(int nbzero, int fd);

void pad_space(int nbpad, int fd);

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

int		pad(int number, t_flags *flags, int fd);

int		pad_int(int number, t_flags *flags, int fd);

int		pad_str(int number, t_flags *flags, int fd);

#endif
