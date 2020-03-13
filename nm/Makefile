##
## EPITECH PROJECT, 2019
## name
## File description:
## Makefile
##

SRC     =	$(shell find . -name '*.c')

OBJ     =	$(SRC:.c=.o)

CC	=	gcc

CPPFLAGS	=	-I ../include

NAME    =	my_nm

# FLAG	=	-W -Wall -Werror -Wextra  -g3 -O3

all:    $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)
	mv $(NAME) ../

clean:
	rm -f $(shell find $(SOURCEDIR) -name '*.o')
	rm -f $(shell find $(SOURCEDIR) -name '*~')
	rm -f $(shell find $(SOURCEDIR) -name '*.gc*')

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re


