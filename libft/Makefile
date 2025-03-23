# **************************************************************************** #
#                                VARIABLES                                     #
# **************************************************************************** #

NAME        = libft.a
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs
RM          = rm -f
MAKEFLAGS	+= -s

SRC_DIR     = src
OBJ_DIR     = obj

SRCS        = $(wildcard $(SRC_DIR)/*.c)
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)
	@echo "\n(╯°□°）╯︵ ┻━┻  𝓛𝓲𝓫𝓯𝓽 compiled and summoned. Prepare for reuse. ⚔️)\n"

$(NAME): $(OBJS)
	@$(AR) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "🧽 Object files vanished. The forge is clean."

fclean: clean
	@$(RM) $(NAME)
	@echo "💀 $(NAME) sacrificed to the binary gods. fclean complete."

re: fclean all
	@echo "🔁 Libft reborn. Recompiled from ashes."


.PHONY: all clean fclean re
