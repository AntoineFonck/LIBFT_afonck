/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:35 by afonck            #+#    #+#             */
/*   Updated: 2019/06/14 13:14:56 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

#define HASHTAG  1   /* 0000 0001 */
#define MINUS  2   /* 0000 0010 */
#define PLUS  4   /* 0000 0100 */
#define SPACE  8   /* 0000 1000 */
#define ZERO  16  /* 0001 0000 */
#define HH  32  /* 0010 0000 */
#define H  64  /* 0100 0000 */
#define L  128 /* 1000 0000 */
#define LL  256 /* 1 0000 0000 */

#include <stdarg.h>
#include <stdio.h>

int	ft_uitoaprint_base(uintmax_t value, int base, int fd);

int	ft_uitocapaprint_base(uintmax_t value, int base, int fd);

int	ft_uitoalen_base(uintmax_t value, int base);

int     ft_uintptrtoaprint_base(uintptr_t value, int base, int fd);

int     ft_uintptrtoalen_base(uintptr_t value, int base);

void pad_zero(int nbzero, int fd);

void pad_space(int nbpad, int fd);

typedef	struct s_flags
{
	int state;
	int field_width;
	int precision;
}				t_flags;

typedef struct s_converter 
{
	char format;
	int (*fun_ptr)(va_list, int, t_flags*);
}	t_converter;

int		pad(int number, t_flags *flags, int fd);

int		pad_int(intmax_t number, t_flags *flags, int fd);

int		pad_str(int number, t_flags *flags, int fd);

int is_activated(t_flags *flags);

int convert_cap_hex(va_list args, int fd, t_flags *flags);

int convert_hex(va_list args, int fd, t_flags *flags);

int convert_pointer(va_list args, int fd, t_flags *flags);

int convert_int(va_list args, int fd, t_flags *flags);

int convert_uint(va_list args, int fd, t_flags *flags);

//int convert_float(va_list args, int fd, t_flags *flags);

int convert_oct(va_list args, int fd, t_flags *flags);

int convert_bin(va_list args, int fd, t_flags *flags);

int pad_uint(uintmax_t number, t_flags *flags, int fd);

int ft_unbrlen(uintmax_t n);
#endif
