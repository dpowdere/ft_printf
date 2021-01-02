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

LIBNAME := libftprintf
CONTENTS := \
    ft_printf.c

NAME := $(LIBNAME).a
HEADER := $(LIBNAME).h
OBJS := $(CONTENTS:.c=.o)
DEPS := $(CONTENTS:.c=.d)
SYSTEM := $(shell uname)

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g3
DEPFLAGS = -MM -MP -MT "$(@:.d=.o) $@" -MF $@

AR := ar
ARFLAGS := rcusv
ifneq ($(SYSTEM), Darwin)
  ifeq ($(SYSTEM), Linux)
    ARFLAGS := rcuUsv
  else
    ARFLAGS := rcsv
  endif
endif

.PHONY: all clean clean_ fclean FORCE re

$(NAME): $(OBJS) libft/libft.a
	$(AR) $(ARFLAGS) $@ $^

all: $(NAME)

clean_:
	$(RM) *.o *.d *.gch *.out

clean: clean_
	@$(MAKE) -C libft clean

fclean: clean_
	$(RM) $(NAME) *.dSYM
	@$(MAKE) -C libft fclean

re: fclean all

%.o: %.c %.d
	$(CC) $(CFLAGS) -c -o $@ $<

%.d: %.c
	$(CPP) $(DEPFLAGS) $< -o /dev/null

libft/libft.a: FORCE
	$(MAKE) -C libft

FORCE:

-include $(DEPS)
