
NAME = LogicSimButInC
LIB = `pkg-config gtk+-3.0 --libs` #Remplace par l'ensemble des librairies de GTK à link pour compiler
PATH_SRC = ./sources/
HEADER = ./includes/
FLAG = -O3 -Wall -Wextra -Werror -std=c99 `pkg-config gtk+-3.0 --cflags` #Remplace par l'ensemble des flags nécessaire à GTK
SRC = $(PATH_SRC)main.c $(PATH_SRC)interface.c $(PATH_SRC)gtkLoader.c $(PATH_SRC)logicSimFunctions.c $(PATH_SRC)component.c $(PATH_SRC)logiSimFileFunction.c
OBJ = main.o interface.o gtkLoader.o logicSimFunctions.o component.o logiSimFileFunction.o


all: $(NAME)

$(NAME):
	gcc-8 $(FLAG) -I $(HEADER) $(SRC) -o $(NAME) $(LIB)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

flcean: fclean

exec:
	./LogicSimButInC

re: fclean all
