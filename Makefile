# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/23 12:57:35 by vhacman           #+#    #+#              #
#    Updated: 2025/03/23 17:46:31 by vhacman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                VARIABLES                                     #
# **************************************************************************** #

NAME		= pipex                                # Executable name
CC			= gcc                                  # Compiler
CFLAGS		= -Wall -Wextra -Werror -gdwarf-4      # Compilation flags with debug info
RM			= rm -f                                # Remove command
MAKEFLAGS	+= -s                                  # Silence recursive make output

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a                # Compiled libft

# Sources and objects
SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/pipex.c \
			  $(SRC_DIR)/exec_utils.c \
			  $(SRC_DIR)/path_utils.c
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

# Compile everything
all: $(NAME)

# Compile pipex with libft
$(NAME): $(LIBFT_A) $(OBJS)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^ $(LIBFT_A)
	@$(MAKE) echo

# Compile individual .c to .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Build libft silently
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) $(notdir $@)

# Clean .o files and libft objects silently
clean:
	@make -s -C $(LIBFT_DIR) fclean
	@$(RM) -r $(OBJ_DIR)
	@$(RM) valgrind.log $(NAME)
	@echo "(╯°□°）╯︵ ┻━┻  Pipex obliterated. Objects, logs, binary, and libft.a wiped. ✨"

# Full clean: pipex + libft.a
fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "(⌐■_■)🔥 Pipex & libft.a obliterated. fclean complete. 💣"

# Rebuild everything
re: fclean all
	@echo "(☞ﾟヮﾟ)☞ Recompiled from scratch. Pipex rises again!"

# **************************************************************************** #
#                             EXTRA TARGETS                                    #
# **************************************************************************** #

# Run pipex with Valgrind
valgrind:
	@echo "🧠 Initializing neural scan..."
	@echo "🔍 Launching pipex under memory surveillance..."
	@valgrind --leak-check=full --track-fds=yes ./$(NAME) infile \"ls\" \"wc -l\" outfile > valgrind.log 2>&1
	@echo "✅ Memory scan complete. No survivors... hopefully. ☠️"

# Stylish ASCII message
echo:
	@echo "(ﾟ◥益◤ﾟ) P̣̱̣͉̃̋̅ͦ̀ȉ̯͙͍̹̙͊p͍̭̰̎̃e̪̞̦̬̬̐̐x͚͙͕̠̋͌́ͦ ͓͗̃̅͊ͯC̬̥͎o̮̥̓ṁ̠̤̩ͤpͯ̆̽î̦̬͉ͅl̹ͅe͛ͬd̮  (ʘ言ʘ)"

# Targets that are not files
.PHONY: all clean fclean re valgrind echo