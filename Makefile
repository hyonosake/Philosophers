NAME =		phil
SRCS =		philo/atoi.c \
			philo/main.c

OBJS =		${SRCS:.c=.o}
DOBJS =		${SRCS:.c=.d}
WWW =		-Wall -Wextra -Werror
FLAGS =		$(WWW) -g -pthread #-O3 -msse3
RM =		rm -rf
CC =		gcc

all:		$(NAME)

%.o: %.c
			$(CC) $(FLAGS) -c $< -o $@

$(NAME):	${OBJS} 
			$(CC) -g $(OBJS)  -o $(NAME)

clean:		
			$(RM) $(OBJS)
			$(RM) $(DOBJS)
fclean:		clean
			$(RM) $(NAME)
re:			fclean all
norm:		fclean
			norminette phlo/*.c  
run:		
			make
			./phil 1 2 3 4 5
bonus:		all

.PHONY: all clean fclean re run bonus 
.SILENT:
-include $(DOBJS)