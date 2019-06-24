# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afonck <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/24 12:48:10 by afonck            #+#    #+#              #
#    Updated: 2019/06/24 12:58:06 by afonck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CFLAGS	= -Wall -Werror -Wextra

FILES		=	float.c \
				percent.c \
				char.c \
				string.c \
				int.c \
				uint.c \
				bin.c \
				octal.c \
				hex.c \
				pointer.c \
				utils.c 

OBJ			= $(FILES:%.c=%.o)

LIB			= libft/libft.a

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(OBJ): $(FILES)
	@make -C ./libft
	@gcc -c $(CFLAGS) $(FILES)

clean:
	@make clean -C ./libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all
