# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/25 10:25:41 by dpowdere          #+#    #+#              #
#    Updated: 2020/12/25 10:33:05 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBNAME = libftprintf
CONTENTS = \
    ft_printf.c

NAME = $(LIBNAME).a
HEADER = $(LIBNAME).h
OBJS = $(CONTENTS:.c=.o)
SYSTEM = $(shell uname)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = rcusv
ifneq ($(SYSTEM), Darwin)
  ifeq ($(SYSTEM), Linux)
    ARFLAGS = rcuUsv
  else
    ARFLAGS = rcsv
  endif
endif

.PHONY: all clean fclean re

all: $(NAME)

clean:
	-$(MAKE) clean -C libft
	$(RM) *.gch
	$(RM) *.o

fclean: clean
	-$(MAKE) fclean -C libft
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
