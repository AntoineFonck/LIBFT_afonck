/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afonck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 14:50:06 by afonck            #+#    #+#             */
/*   Updated: 2019/05/07 18:31:03 by afonck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft.h"

void	ft_uitoaprint_base(unsigned int value, int base, int fd)
{
	char	buf[50];
    char    *ptr;
    int     num;
    int	    ascii_offset;

    ptr = &buf[50];
    *ptr = '\0';
    num = value;
    //if (value < 0 && base == 10)
      //  value *= -1;
    if (value == 0)
        *--ptr = '0' + (value % base);
    while (value != 0)
    {
	ascii_offset = 0;
	if (value % base > 9)
		ascii_offset = 39;
        *--ptr = '0' + ((value % base) + ascii_offset);
        value /= base;
    }
    //if (num < 0 && base == 10)
      //  *--ptr = '-';
    //return (ptr);
    write(fd, ptr, ft_strlen(ptr));
}

/*
int main(int argc, char **argv)
{
	int test;

	test = 0x12ef;
	if (argc == 3)
	{
		//printf("%s\n", itoa_base(atoi(argv[1]), atoi(argv[2])));
		ft_uitoaprint_base(test, ft_atoi(argv[2]));
		printf("\n\nreal printf hex = %x\n", test);//ft_atoi(argv[1]));
		printf("\nreal printf octal = %o\n", ft_atoi(argv[1]));
		printf("\nreal printf unsigned = %u\n", ft_atoi(argv[1]));
		printf("\nreal printf signed = %d\n", ft_atoi(argv[1]));
	}
	return (0);
}
*/
