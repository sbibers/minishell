CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I libft/include

RM = rm -f
AR = ar rcs

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a


BIN = minishell
NAME = $(BIN)

SRC = handle_built_in.c \
	env.c \
	handle_errors.c \
	execute.c \
	execute_2.c \
	expand_path.c \
	expand_var.c \
	creat_node_3.c \
	split_separator.c \
	delete_quotes.c \
	grep_path_of_cmd.c \
	get_fd.c \
	handle_quote.c \
	heredoc.c \
	main.c \
	matrix_things.c \
	parsing.c \
	signal.c \
	utilities.c \
	creat_node.c \
	creat_node_2.c \
	handle_echo_pwd.c \
	utils_2.c \
	handle_unset.c \
	handle_export.c \
	utils_3.c \
	handle_cd.c \
	ft_replace.c \
	print_error.c \
	get_path.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): | $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
