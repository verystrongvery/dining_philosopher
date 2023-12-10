SRC		= 	main.c\
			philo_act.c\
			util.c
OBJ		= $(SRC:.c=.o)

NAME	= philo_two
RM		= rm -rf
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all 	: $(NAME)

clean	:
		$(RM) $(OBJ) *.gch *.out

fclean	: clean
		$(RM) $(NAME)

re		: fclean all

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)