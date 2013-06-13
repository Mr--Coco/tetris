SRC	=	main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	tetris

CC	=	gcc

RM	=	rm -f

LIB	=	-lm -lSDL -lSDL_mixer -lSDL_ttf ##-lSDLmain

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

all:	$(NAME)

clean:	
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
