CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM	= rm -f

NAME = philo_bonus

SRCS = main.c init.c utils.c activities.c

DEPS	=	philo.h

OBJS = ${SRCS:.c=.o}

all:		${NAME}

.c.o: ${SRCS}

			@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):	$(OBJS) $(DEPS)
			@$(CC) $(OBJS) -o $(NAME)
		
clean:		
			@${RM} $(OBJS)
	
fclean:		clean
			@$(RM) $(NAME)
re:			fclean all

.PHONY:		all clean fclean re