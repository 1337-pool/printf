CFLAGS=-Wall -Wextra -Werror -I includes
RM=rm -f
AR=ar -rcs
NAME=libftprintf.a
SRCS=srcs/ft_print_memory.c  srcs/ft_putchar.c  srcs/ft_putnbr_base.c \
		 srcs/ft_putstr.c	srcs/ft_strlen.c ft_printf.c
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
