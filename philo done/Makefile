NAME		= philo

SRCS		= srcs/philo.c srcs/philo_utils.c srcs/init.c srcs/handle_threads.c srcs/handle_actions.c

OBJS		= $(SRCS:.c=.o)

RM		= rm -f

CC		= cc -Wall -Wextra -Werror -pthread -g

.c.o:
			@$(CC) -c $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean re fclean