# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -I libft/include

# Utilities
RM = rm -f
AR = ar rcs

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft

# Library
LIBFT = $(LIBFT_DIR)/libft.a

# Executable
BIN = minishell
NAME = $(BIN)

# Source Files
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

# Object Files
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Color Definitions for Better Readability
COL_RESET = \033[0m
COL_GREEN = \033[32m
COL_CYAN = \033[36m
COL_YELLOW = \033[33m
COL_RED = \033[31m

# Default Rule
all: $(NAME)

# Link the Executable
$(NAME): $(LIBFT) $(OBJ)
	@echo "$(COL_GREEN)Linking the executable...$(COL_RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@
	@echo "$(COL_GREEN)Linking done!$(COL_RESET)"

# Compile the Object Files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(COL_CYAN)Compiling: $<$(COL_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(COL_GREEN)Compilation of $< done!$(COL_RESET)"

# Make Libft
$(LIBFT): | $(LIBFT_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR)

# Clean the Build
clean:
	@echo "$(COL_RED)Cleaning build...$(COL_RESET)"
	@make clean -C $(LIBFT_DIR)
	@$(RM) -r $(OBJ_DIR)
	@echo "$(COL_RED)Build cleaned!$(COL_RESET)"

# Fully Clean the Build (including executable)
fclean: clean
	@echo "$(COL_RED)Removing executable...$(COL_RESET)"
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "$(COL_RED)Executable removed!$(COL_RESET)"

# Create Object Directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rebuild Everything
re: fclean all

.PHONY: all clean fclean re

