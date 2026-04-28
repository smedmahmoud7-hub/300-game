# Compiler
CC = gcc

# fichiers sources
SRC = main.c source.c
OBJ = $(SRC:.c=.o)

# executable
NAME = game

# flags
CFLAGS = -Wall -Wextra -std=c99
SDLFLAGS = -lSDL2 -lSDL2_image -lm

# rule principale
all: $(NAME)

# link final
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(SDLFLAGS)

# compilation .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
