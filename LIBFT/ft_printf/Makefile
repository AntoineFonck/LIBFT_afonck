# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afonck <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/24 12:48:10 by afonck            #+#    #+#              #
#    Updated: 2019/07/06 15:21:51 by sluetzen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

CFLAGS	= -Wall -Werror -Wextra

LIBRARIES	= -lft -L$(LIBFT_DIR)

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

HEADER_LIST = ft_printf.h

SRC_DIR  = ./src/
INC_DIR  = ./includes/
OBJ_DIR  = ./obj/
LIBFT_DIR	= ./libft/
LIBFT	= $(LIBFT_DIR)libft.a

SRC_LIST	=	ft_printf.c \
				float.c \
				percent.c \
				char.c \
				string.c \
				int.c \
				uint.c \
				bin.c \
				octal.c \
				hex.c \
				hexcap.c \
				pointer.c \
				checklen.c \
				flags.c \
				pad.c \
				float_spec.c \
				utils.c 

OBJ_LIST = $(SRC_LIST:.c=.o)

SRC		=	$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ		=	$(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INC_DIR)ft_printf.h
	@gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all
