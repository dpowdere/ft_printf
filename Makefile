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
    ft_printf.c \
\
    utils/ft_write.c

NAME := $(LIBNAME).a
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

.PHONY: all clean fclean re

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

all: $(NAME)

clean:
	$(RM) *.o */*.o *.d */*.d *.gch */*.gch *.out

fclean: clean
	$(RM) $(NAME) *.dSYM

re: fclean all

%.o: %.c %.d
	$(CC) $(CFLAGS) -c -o $@ $<

%.d: %.c
	$(CPP) $(DEPFLAGS) $< -o /dev/null

-include $(DEPS)
