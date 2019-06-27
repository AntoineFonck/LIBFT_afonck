# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afonck <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 18:55:30 by afonck            #+#    #+#              #
#    Updated: 2018/12/20 19:38:35 by afonck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CFLAGS	= -Wall -Werror -Wextra -Iincludes -c
FILES		= $(shell ls | grep -E "ft_.+\.c") \
			  get_next_line.c
OBJ			= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ): $(FILES)
	@gcc $(CFLAGS) $(FILES)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
