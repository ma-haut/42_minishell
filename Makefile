NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = include

SRC = main.c\
		parsing/parsing.c\
		parsing/parsing_utils.c\
		parsing/node_init.c\
		parsing/tokenize.c\
		parsing/tokenize2.c\
		parsing/tokenize_utils.c\
		parsing/tokenize_utils2.c\
		parsing/tokenize_utils3.c\
		parsing/parse.c\
		parsing/parse2.c\
		parsing/parse_tokens.c\
		parsing/free_struct.c\
		parsing/parse_pipe.c\
		builtins/ft_cd.c\
		builtins/ft_echo.c\
		builtins/ft_env.c\
		builtins/ft_exit.c\
		builtins/ft_export.c\
		builtins/ft_pwd.c\
		builtins/ft_unset.c\
		builtins/env_utils.c\
		builtins/env_utils2.c\
		exec/exec.c\
		exec/exec_builtins.c\
		exec/exec_commands.c\
		exec/exec_pipes.c\
		exec/handle_redir.c\
		exec/get_path.c\
		exec/files_utils.c\
		exec/files_utils2.c\
		utils/free_stuff.c\
		utils/handle_errors.c\
		utils/expand.c\
		utils/expand2.c\
		utils/expand3.c\
		utils/init_shell.c\
		utils/handle_signals.c

OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)

LDFLAGS =  -L$(LIBFT_DIR)
LIBS =  $(LIBFT) -lreadline

AR = ar
ARFLAGS = rcs

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3 -I$(LIBFT_INCLUDE)

# Colors
RED     := "\033[1;31m"
GREEN   := "\033[1;32m"
RESET   := "\033[0m"

# Default Rule
all: $(OBJDIR) $(LIBFT) $(NAME)

# Object Directory Rule
$(OBJDIR):
	@mkdir -p $(OBJDIR) || true

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Libft
$(LIBFT):
	@$(MAKE) --silent -C $(LIBFT_DIR)
	@echo '[$(NAME)] Libft successfully built'

# Linking Rule
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(BONUS_OBJ) $(LIBS) $(MLXFLAGS) -o $(NAME)
	@echo $(GREEN)"[$(NAME)] Executable created ✅"$(RESET)

# Clean Rules
clean:
	@echo $(RED)'[$(NAME)] Cleaning objects'$(RESET)
	@rm -rf $(OBJDIR)

fclean: clean
	@echo $(RED)'[$(NAME)] Cleaning all files'$(RESET)
	@rm -f $(NAME)
	@$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus