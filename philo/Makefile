# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfernand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 12:52:28 by gfernand          #+#    #+#              #
#    Updated: 2023/09/13 12:52:31 by gfernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c src/pthreads.c src/check.c src/initialize.c src/utils.c

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
BLUE	= '\033[1;34m'
WHITE	= '\033[1;37m'

CC = gcc
FLAGS = -Wall -Werror -Wextra

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GREEN)"Generating enforcible..."$(WHITE)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo $(GREEN)"$(NAME) Generated!"$(WHITE)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo $(RED)"OBJS were deleted"$(WHITE)

fclean: clean
	rm -f $(NAME)
	@echo $(RED)"$(NAME) deleted"$(WHITE)

re: fclean all

n:
	"norminette"

.PHONY: all clean fclean re n
