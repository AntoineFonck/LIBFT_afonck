/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluetzen <sluetzen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:35 by afonck            #+#    #+#             */
/*   Updated: 2019/06/24 14:44:47 by sluetzen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

# define HASHTAG  1   /* 0000 0001 */
# define MINUS  2   /* 0000 0010 */
# define PLUS  4   /* 0000 0100 */
# define SPACE  8   /* 0000 1000 */
# define ZERO  16  /* 0001 0000 */
# define HH  32  /* 0010 0000 */
# define H  64  /* 0100 0000 */
# define L  128 /* 1000 0000 */
# define LL  256 /* 1 0000 0000 */
# define PREC  512 /* 10 0000 0000 */
# define BIGL  1024 /* 100 0000 0000 */

# define HASH_FLAG flags->state & HASHTAG
# define MIN_FLAG flags->state & MINUS
# define PLUS_FLAG flags->state & PLUS
# define SPACE_FLAG flags->state & SPACE
# define ZERO_FLAG flags->state & ZERO
# define HH_FLAG flags->state & HH
# define H_FLAG flags->state & H
# define L_FLAG flags->state & L
# define LL_FLAG flags->state & LL
# define PREC_FLAG flags->state & PREC
# define BIGL_FLAG flags->state & BIGL


# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define COLORLEN 7
# define RESET "\e[0m"

# define NBFORMATS 14

#include <stdarg.h>

#include <stdint.h>
#include <wchar.h>

int ft_printf(const char *fmt, ...); /*__attribute__((format(printf,1,2)));*/
/////////////////////////////
int ft_ftoa(double n, int afterpoint, int fd);
int ft_floatlen(double n, int afterpoint);
float ft_atof(const char* s);
int ft_putwchar_fd(wchar_t wchar, int fd);
int get_wchar_size(int nbbits);
int nbits(unsigned int nbr);
/////////////////////////////

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
	int color;
}				t_flags;

typedef struct s_converter 
{
	char format;
	int (*fun_ptr)(va_list, int, t_flags*);
}	t_converter;

/*
**int		pad_percent(int number, t_flags *flags, int fd);
*/

/////////////////
int pad_float(double number, t_flags *flags, int fd);
//////////////////


int		pad_int(intmax_t number, t_flags *flags, int fd);

int		pad_str(int number, t_flags *flags, int fd);

int is_activated(t_flags *flags);
//////////////////////////////
int convert_float(va_list args, int fd, t_flags *flags);
//////////////////////////////
int convert_percent(va_list args, int fd, t_flags *flags);

int convert_string(va_list args, int fd, t_flags *flags);

int convert_wstring(va_list args, int fd, t_flags *flags);

int convert_char(va_list args, int fd, t_flags *flags);

int convert_wchar(va_list args, int fd, t_flags *flags);

int convert_cap_hex(va_list args, int fd, t_flags *flags);

int convert_hex(va_list args, int fd, t_flags *flags);

int convert_pointer(va_list args, int fd, t_flags *flags);

int convert_int(va_list args, int fd, t_flags *flags);

int convert_uint(va_list args, int fd, t_flags *flags);

//int convert_float(va_list args, int fd, t_flags *flags);

int convert_oct(va_list args, int fd, t_flags *flags);

int convert_bin(va_list args, int fd, t_flags *flags);

int pad_uint(uintmax_t number, t_flags *flags, int fd);

void	flags_spec(t_flags *flags, int nbpad, int fd, intmax_t number);

int ft_unbrlen(uintmax_t n);
#endif
