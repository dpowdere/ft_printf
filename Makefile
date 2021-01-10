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
    specs/ft_spec_c.c \
    specs/ft_spec_e.c \
    specs/ft_spec_f.c \
    specs/ft_spec_g.c \
    specs/ft_spec_hex.c \
    specs/ft_spec_int.c \
    specs/ft_spec_n.c \
    specs/ft_spec_o.c \
    specs/ft_spec_p.c \
    specs/ft_spec_percent.c \
    specs/ft_spec_s.c \
\
    parsing/ft_parse_flags.c \
    parsing/ft_parse_width.c \
    parsing/ft_parse_precision.c \
    parsing/ft_parse_size.c \
    parsing/ft_parse_specifier.c \
    parsing/ft_normalize_spec.c \
    parsing/ft_get_typing_width.c \
\
    utils/ft_ll_base.c \
    utils/ft_format_ll.c \
    utils/ft_print_field.c \
\
    utils/ft_memset.c \
    utils/ft_strchr.c \
    utils/ft_strdup.c \
    utils/ft_strlen.c \
    utils/ft_strpfx.c \
    utils/ft_write.c

NAME := $(LIBNAME).a
OBJS := $(CONTENTS:.c=.o)
DEPS := $(CONTENTS:.c=.d)
SYSTEM := $(shell uname)

CC := gcc
CFLAGS = -Wall -Wextra -Werror -g3 -DDARWIN=$(DARWIN)
DEPFLAGS = -MMD -MP

AR := ar
ARFLAGS := rcusv
DARWIN := 1
ifneq ($(SYSTEM), Darwin)
  DARWIN := 0
  ifeq ($(SYSTEM), Linux)
    ARFLAGS := rcuUsv
  else
    ARFLAGS := rcsv
  endif
endif

.PHONY: all bonus clean fclean re

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

all: $(NAME)

bonus: $(NAME)

clean:
	$(RM) *.o */*.o *.d */*.d *.gch */*.gch *.out

fclean: clean
	$(RM) $(NAME) *.dSYM

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $(DEPFLAGS) -o $@ $<

-include $(DEPS)
