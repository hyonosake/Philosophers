NAME =		phil
SRCS =		./parse_check.c \
			./routines.c \
			./thread_management.c \
			./utils.c \
			./main.c

OBJS =		${SRCS:.c=.o}
DOBJS =		${SRCS:.c=.d}
WWW =		
FLAGS =		$(WWW) -g -MMD -pthread -fsanitize=address
RM =		rm -rf
CC =		gcc

%.o: %.c
			$(CC) -I philosophers.h $(FLAGS) -c $< -o $@

$(NAME):	${OBJS} 
			$(CC) $(OBJS)  -o $(NAME)

all:		$(NAME)

clean:		
			$(RM) $(OBJS)
			$(RM) $(DOBJS)
fclean:		clean
			$(RM) $(NAME)
re:			fclean all
norm:		fclean
			norminette ./*.c  
run:		
			make re
			./phil 5 800 200 200
bonus:		all

.PHONY: all clean fclean re run bonus 
#.SILENT:
-include $(DOBJS)