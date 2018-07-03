# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/04 21:30:41 by afarapon          #+#    #+#              #
#    Updated: 2018/02/04 22:51:31 by afarapon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_contrast

CC = gcc -Wall -Wextra -Werror 

IDIR = ./includes

CFLAGS = -I$(IDIR)

LIBDIR = ./libft

LIBFT = $(LIBDIR)/libft.a

SRCDIR = src

SRC = main.c \
	extra_functions.c \
	calc_array.c

_OBJ = $(SRC:%.c=%.o)

_DEPS = ft_thpool.h

OBJ = $(SRC:.c=.o)

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

.PHONY: all clean fclean re
.NOTPARALLEL: all clean fclean re

all: $(NAME)

%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(LIBFT) $(OBJ)
	@cp libft/libft.a ./$(NAME)
	@$(CC) -o $(NAME) $(OBJ) libft/libft.a -lpthread

$(LIBFT):
	@make -C $(LIBDIR)

clean:
	@/bin/rm -rf *.o
	@/bin/rm -rf libft/*.o

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -rf libft/libft.a

re : fclean all