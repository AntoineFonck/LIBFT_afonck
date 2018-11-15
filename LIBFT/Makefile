# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afonck <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 18:55:30 by afonck            #+#    #+#              #
#    Updated: 2018/11/08 15:43:53 by afonck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC    =    gcc
CFLAGS    =    -Wall -Wextra -Werror -I ./libft.h

NAME    =    libft.a
SRC        =    *.c

OBJ        =    *.o

all:    $(NAME)

$(NAME):
	$(CC) -c $(CFLAGS) $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean:    clean
	/bin/rm -f $(NAME)

re:    fclean all
