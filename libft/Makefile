CC = cc

CFLAGS = -Wall -Wextra -Werror -I./include
# -I : find the header in include.

SRCS = $(shell cat files.txt)

OBJ_DIR = objs
# directory for objects file.

OBJS = $(SRCS:srcs/%.c=$(OBJ_DIR)/%.o)
# convert .c files to .o files to the path OBJ_DIR.

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: srcs/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
# mkdir -p $(OBJ_DIR) : make the OBJ_DIR if it not existing.
# $(CC) $(CFLAGS) -c $< -o $@ : ($<) for .c files, ($@) for .o files. 
# -c : translating the code into code (.o) without linking it.
# -o : the result will be a file named laike .c file just .o file.

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
