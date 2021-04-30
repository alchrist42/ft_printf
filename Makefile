NAME		=	libftprintf.a

SRCS		= 	ft_printf.c			ft_printf_utils1.c		ft_printf_utils2.c

HEADER		=	ft_printf.h

OBJS		=	$(patsubst %.c,%.o,$(SRCS))
# OBJS_B		=	$(patsubst %.c,%.o,$(SRCS_B))


CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

LIBC		=	ar rcs

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
			@cd libft && MAKE
			@cp libft/libft.a $(NAME)
			$(LIBC) $(NAME) $(OBJS) $?

bonus:		$(NAME)

libft.a:   

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus

