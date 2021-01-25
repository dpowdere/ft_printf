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
CONTENTS = \
    ft_printf.c \
\
    conv_c.c \
    conv_e.c \
    conv_f.c \
    conv_g.c \
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
    ryu_dtoa_e.c \
    ryu_dtoa_f.c \
    ryu_digits.c \
    ryu_math.c \
    ryu_utils.c \
\
    ft_memcpy.c \
    ft_memset.c \
    ft_strchr.c \
    ft_strdup.c \
    ft_strlen.c \
    ft_strpfx.c \
    ft_wcstombs_len.c \
    ft_write.c

NAME := $(LIBNAME).a
SRCDIR := src
INCDIR := include
OBJDIR := obj
DEPDIR := .dep

SRCS := $(addprefix $(SRCDIR)/, $(CONTENTS))
OBJS := $(addprefix $(OBJDIR)/, $(CONTENTS:.c=.o))
DEPS := $(addprefix $(DEPDIR)/, $(CONTENTS:.c=.d))
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

clean:
	$(RM) -R $(OBJDIR)/ $(DEPDIR)/ $(INCDIR)/*.gch

fclean: clean
	$(RM) -R *.dSYM core core.*
	$(RM) $(NAME) *.out

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $(DEPFLAGS) -o $@ $<

$(SRCDIR)/%.c: $(DEPDIR)

$(DEPDIR) $(OBJDIR):
	mkdir -p $@

test:
	@if [ -f test.c ] ; \
	then \
		test -f $(NAME) || $(MAKE) $(NAME) ; \
		$(CC) $(CFLAGS) -Wformat=0 $(INCLUDE) test.c $(NAME) -o test.out ; \
		./test.out ; \
	else \
		echo "No test found" ; \
	fi

-include $(DEPS)
