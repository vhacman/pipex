# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 10:15:55 by vhacman           #+#    #+#              #
#    Updated: 2025/03/24 10:15:56 by vhacman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                VARIABLES                                     #
# **************************************************************************** #

NAME		= pipex			# The name of the final executable
CC			= gcc			# The compiler to use

# Compiler flags:
# -Wall     : enable all warnings
# -Wextra   : enable extra warnings
# -Werror   : treat warnings as errors
# -gdwarf-4 : include debug symbols in DWARF v4 format
CFLAGS		= -Wall -Wextra -Werror -gdwarf-4

# Command to delete files
RM			= rm -f

# Silence output from recursive make calls
MAKEFLAGS	+= -s

# Directory paths
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
LIBFT_DIR	= libft
MAIN_DIR	= main
UTILS_DIR	= utils

# Path to the compiled libft static library
LIBFT_A		= $(LIBFT_DIR)/libft.a

# List of source files (.c files with full paths)
SRCS = $(MAIN_DIR)/main.c \
	   $(SRC_DIR)/pipex.c \
	   $(UTILS_DIR)/exec_utils.c \
	   $(UTILS_DIR)/path_utils.c

# List of object files corresponding to source files
# Example: main/main.c → obj/main/main.o
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

# Default target: build the program
all: $(NAME)

# Link the object files and libft to create the final executable
$(NAME): $(LIBFT_A) $(OBJS)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^ $(LIBFT_A)
	@$(MAKE) echo

# Rule to compile each .c file into a .o file in obj/
# $< = source file, $@ = object file
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)					# create directory if it doesn't exist
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@	# compile .c into .o

# Build libft.a by running libft's Makefile
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) $(notdir $@)

# Remove object files, log, binary, and libft
clean:
	@make -s -C $(LIBFT_DIR) fclean
	@$(RM) -r $(OBJ_DIR)
	@$(RM) valgrind.log $(NAME)
	@echo "(╯°□°）╯︵ ┻━┻  Pipex obliterated. Objects, logs, binary, and libft.a wiped. ✨"

# Remove everything, including final binary
fclean: clean
	@$(RM) $(NAME)
	@echo "(⌐■_■)🔥 Pipex & libft.a obliterated. fclean complete. 💣"

# Rebuild from scratch
re: fclean all
	@echo "(☞ﾟヮﾟ)☞ Recompiled from scratch. Pipex rises again!"

# **************************************************************************** #
#                             EXTRA TARGETS                                    #
# **************************************************************************** #

# Run the program under Valgrind for memory leak detection
valgrind:
	@echo "🧠 Initializing neural scan..."
	@echo "🔍 Launching pipex under memory surveillance..."
	@valgrind --leak-check=full --track-fds=yes ./$(NAME) infile \"ls\" \"wc -l\" outfile > valgrind.log 2>&1
	@echo "✅ Memory scan complete. No survivors... hopefully. ☠️"

# Fun success message
echo:
	@echo "(ﾟ◥益◤ﾟ) P̣̱̣͉̃̋̅ͦ̀ȉ̯͙͍̹̙͊p͍̭̰̎̃e̪̞̦̬̬̐̐x͚͙͕̠̋͌́ͦ ͓͗̃̅͊ͯC̬̥͎o̮̥̓ṁ̠̤̩ͤpͯ̆̽î̦̬͉ͅl̹ͅe͛ͬd̮  (ʘ言ʘ)"

# Declare targets that aren't actual files
.PHONY: all clean fclean re valgrind echo
