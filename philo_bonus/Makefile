NAME =		phil_bonus
SRCS =		./init_structs.c \
			./routines.c \
			./forks.c \
			./utils.c \
			./utils_2.c \
			./main.c

OBJS =		${SRCS:.c=.o}
DOBJS =		${SRCS:.c=.d}
WWW =		
FLAGS =		$(WWW) -g -MMD -pthread #-fsanitize=address
RM =		rm -rf
CC =		gcc

%.o: %.c
			$(CC) $(FLAGS) -c $< -o $@

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
			make clean
			./$(NAME) 5 800 200 200

bonus:		all

a:			all clean

.PHONY: all clean fclean re run bonus 
#.SILENT:
-include $(DOBJS)