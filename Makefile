CFLAGS=-Wall -Wextra -Werror -I includes
RM=rm -f
AR=ar -rcs
NAME=libftprintf.a
SRCS=srcs/ft_print_memory.c  srcs/ft_putchar.c  srcs/ft_putnbr_base.c \
		 srcs/ft_putstr.c	srcs/ft_strlen.c ft_printf.c
OBJS=$(SRCS:.c=.o)
BONUS_SRCS = ft_printf_bonus.c parse_bonus.c format_bonus.c convert_bonus.c utils_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
