# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/25 10:25:41 by dpowdere          #+#    #+#              #
#    Updated: 2021/01/27 00:19:40 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBNAME := libftprintf
CONTENTS = \
    ft_printf.c \
\
    conv_c.c \
    conv_hex.c \
    conv_int.c \
    conv_n.c \
    conv_o.c \
    conv_p.c \
    conv_percent.c \
    conv_s.c \
\
    get_va_arg.c \
    get_typing_width.c \
    normalize_spec.c \
    print_field.c \
\
    parse_conversion.c \
    parse_flags.c \
    parse_precision.c \
    parse_size.c \
    parse_width.c \
\
    jtoa.c \
    j_base.c \
\
    ft_memset.c \
    ft_strchr.c \
    ft_strdup.c \
    ft_strlen.c \
    ft_strpfx.c \
    ft_wcstombs.c \
    ft_wcstombs_len.c \
    ft_wctomb.c \
    ft_wctomb_len.c \
    ft_write.c

NAME := $(LIBNAME).a
SRCDIR := src
INCDIR := include
OBJDIR := obj
$(shell mkdir -p $(OBJDIR))

SRCS := $(addprefix $(SRCDIR)/, $(CONTENTS))
OBJS := $(addprefix $(OBJDIR)/, $(CONTENTS:.c=.o))
DEPS := $(addprefix $(OBJDIR)/, $(CONTENTS:.c=.d))
INCLUDE := -I$(INCDIR)
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

.PHONY: all bonus clean fclean re test

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

all: $(NAME)

bonus: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@ $(INCLUDE) $<

clean:
	$(RM) $(OBJDIR)/*.o $(OBJDIR)/*.d $(INCDIR)/*.gch

fclean: clean
	$(RM) -R *.dSYM core core.*
	$(RM) $(NAME) *.out

re: fclean all

test:
	@if [ -f test.c ] ; \
	then \
		test -f $(NAME) || $(MAKE) $(NAME) ; \
		$(CC) $(CFLAGS) -Wformat=0 -o test.out $(INCLUDE) test.c $(NAME) ; \
		./test.out ; \
	else \
		echo "No test found" ; \
	fi

-include $(DEPS)
