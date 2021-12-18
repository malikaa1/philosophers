NAME = philo

SRCS = main.c utils.c

CC = gcc

INCLUDE	= include

CFLAGS = -Wall -Wextra -Werror -pthread

OBJS = ${SRCS:.c=.o}

$(NAME) : $(OBJS) 
		$(CC) $(CFLAGS) -g -I $(INCLUDE) $(OBJS) -o $(NAME) 

RM = rm -f
%.o : %.c 
		$(CC) -g $(FLAGS) -c -I $(INCLUDE) $< -o ${<:.c=.o}

all : $(NAME)


clean :	
		${RM} ${OBJS}
		

fclean :	 clean
		${RM} ${NAME}

re:	fclean all
.PHONY:		all clean fclean re

