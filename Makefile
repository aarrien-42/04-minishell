# Normbre del ejecutable
NAME = minishell

# Directorios
SRC_DIR = srcs/
OBJ_DIR = objs/
OBJF = objs
INC = incs

# Ficheros
SRC_FILES = main fill_input built input_split clean_block env_list \
	check change_caracter signals add_spaces ft_pipex ft_pipex_utils
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# Comandos
CC = gcc
LREADLINE_FLAGS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib/
READLINE = -I/Users/$(USER)/.brew/opt/readline/include/
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
RM = rm -f
AR = ar rcs

# REGLAS #
all: $(NAME)

# Compilar conjuntamente
$(NAME): $(OBJ)
	@$(MAKE) -C ./libft
	@echo "libft compiled!"
	@$(CC) $(CFLAGS) $(LREADLINE_FLAGS) $(READLINE) -lncurses ./libft/libft.a $(OBJ) -o $(NAME)
	@echo "minishell compiled!"

# Compilar objetos individualmente
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(READLINE) -I $(INC) -c $< -o $@

# Crear directorio temporal para los obj
$(OBJF):
	@mkdir -p $(OBJ_DIR)

# Eliminar temporales
clean:
	@$(MAKE) -C ./libft clean
	@$(RM) -r $(OBJ_DIR)
	@echo "Objects and directory cleaned!"

# Eliminar temporales y ejecutable
fclean: clean
	@$(MAKE) -C ./libft fclean
	@$(RM) $(NAME) libft.a
	@echo "Executable cleaned!"

re: fclean all

norm:
	@norminette

.PHONY: all clean fclean re
