##
## EPITECH PROJECT, 2019
## name
## File description:
## Makefile
##

all:
	make -C nm/
	make -C objdump/

nm: 
	make -C nm/

objdump: 
	make -C objdump/

$(NAME):
	rm -f $(shell find $(SOURCEDIR) -name '*.o')

clean:
	rm -f $(shell find $(SOURCEDIR) -name '*.o')
	rm -f $(shell find $(SOURCEDIR) -name '*~')
	rm -f $(shell find $(SOURCEDIR) -name '*.gc*')

fclean: clean
	rm -f ./my_nm
	rm -f ./my_objdump

re:	fclean all

.PHONY: all clean fclean re nm objdump


