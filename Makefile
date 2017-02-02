# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bngo <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/05 11:40:59 by bngo              #+#    #+#              #
#    Updated: 2017/02/02 13:11:10 by bngo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
CFLAGS = -Wall -Werror -Wextra
CPATH = src/
OPATH = obj/
HPATH = include/ libft/
INC = $(addprefix -I , $(HPATH))
CFILES = main.c \

OFILES = $(CFILES:.c=.o)
HFILES = include/minishell.h libft/libft.h
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

debug: $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) -g $(INC) $< -c -o $@


clean:
	make -C libft clean
	rm -rf $(OBJ) $(OPATH)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
