/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:51:35 by afonck            #+#    #+#             */
/*   Updated: 2019/05/07 18:31:16 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF
# define FALSE 0
# define TRUE 1

void	ft_uitoaprint_base(unsigned int value, int base, int fd);

typedef struct s_converter 
{
	char format;
	int boolean;
	int (*fun_ptr)(va_list, int*);
}	t_converter;

#endif
