# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/10 03:40:58 by onahiz            #+#    #+#              #
#    Updated: 2019/04/24 05:19:11 by onahiz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = src/main.c src/options.c src/args.c src/dir_content.c src/files.c src/getters.c src/ft_ls.c src/max.c

OBJ = src/main.o src/options.o src/args.o src/dir_content.o src/files.o src/getters.o src/ft_ls.o src/max.o

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C libft/
	@gcc $(SRC) $(CFLAGS) -L libft/ -lft -o $(NAME)

clean:
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all
