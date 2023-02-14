# Normbre del ejecutable
NAME = libft.a

# Directorios
SRC_DIR = srcs/
OBJ_DIR = objs/
OBJF = objs
INC = ../incs

# Ficheros
SRC_FILES = ft_putchar_fd ft_putstr_fd ft_strlen ft_split ft_strjoin \
			ft_substr ft_strncmp ft_strchr ft_strtrim ft_strdup ft_itoa
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# Comandos
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
AR = ar rcs

# REGLAS #
all: $(NAME)

# Compilar conjuntamente
$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

# Compilar objetos individualmente y meterlos al directorio correspodiente mediante una pipe
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

# Crear directorio temporal para los obj
$(OBJF):
	@mkdir -p $(OBJ_DIR)

# Eliminar temporales
clean:
	@$(RM) -r $(OBJ_DIR)

# Eliminar temporales y ejecutable
fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
