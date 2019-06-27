# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afonck <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/24 12:48:10 by afonck            #+#    #+#              #
#    Updated: 2019/06/27 16:33:09 by afonck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CFLAGS	= -Wall -Werror -Wextra

LIBRARIES	= -lft -L$(LIBFT_DIR)

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

SRC_DIR  = ./src/
INC_DIR  = ./includes/
OBJ_DIR  = ./obj/
LIBFT_DIR	= ./libft/
LIBFT	= $(LIBFT_DIR)libft.a

SRC_LIST	=	float.c \
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
SRC		=	$(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_LIST	= $(patsubst %.c, %.o, $(SRC_LIST))

OBJ		= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ): $(FILES) $(HEADERS)
	@gcc $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all
