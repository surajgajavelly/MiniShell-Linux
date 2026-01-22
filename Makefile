OBJ := $(patsubst %.c,%.o, $(wildcard *.c))

minishell : $(OBJ)
	gcc $(OBJ) -o minishell

clean :
	rm -f *.o minishell