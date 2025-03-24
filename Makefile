# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/23 12:57:35 by vhacman           #+#    #+#              #
#    Updated: 2025/03/24 09:48:28 by vhacman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


 
# *****************************************************************************#
#                                VARIABLES                                     #
# **************************************************************************** #

# The name of the final executable
NAME		= pipex

# The compiler to use
CC			= gcc

# Compiler flags:
# -Wall     : enable all warnings
# -Wextra   : enable extra warnings
# -Werror   : treat warnings as errors
# -gdwarf-4 : include debugging information using DWARF v4
# -g -->tells the compiler to generate debug symbols
# dwarf-4 --> specifies the format and version of the debug
#				info. 
CFLAGS		= -Wall -Wextra -Werror -gdwarf-4

# Command to delete files  (-f -->force)
RM			= rm -f

# This silences output from recursive make calls (like libft) (-s -->silence)
MAKEFLAGS	+= -s

# Source directories
SRC_DIR		= src        # where pipex.c is
OBJ_DIR		= obj        # where .o files will be stored
INC_DIR		= includes   # where .h files are
LIBFT_DIR	= libft      # where the libft project is
MAIN_DIR	= main       # where main.c is

# Path to the compiled libft static library
LIBFT_A		= $(LIBFT_DIR)/libft.a

# List of source files
SRCS = $(MAIN_DIR)/main.c \
	   $(SRC_DIR)/pipex.c \
	   utils/exec_utils.c \
	   utils/path_utils.c

# "Take every .c file listed in $(SRCS)
# and turn it into the corresponding .o file path inside the obj/ directory."
# patsubst = short for pattern substitution --> general -$(patsubst <pattern>,<replacement>,<text>)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

# 'make' or 'make all' will build the executable
all: $(NAME)

# To build pipex (which is what $(NAME) equals), first need:
#$(LIBFT_A) → the compiled libft.a library
#$(OBJS) → all the .o files compiled from your .c files
#This command quietly tells the compiler (gcc) to compile all object files 
#and the libft library, using the specified flags and headers from includes/,
#and to output the final executable named pipex.
$(NAME): $(LIBFT_A) $(OBJS)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^ $(LIBFT_A)
	@$(MAKE) echo

# Rule to compile any .c file into a .o file inside obj/
# $< = the source file
# $@ = the target object file
# mkdir -p creates the obj/ subdirectories as needed
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Build libft statically (it runs libft/Makefile)
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) $(notdir $@)

# Clean object files, binary, valgrind log, and libft artifacts
clean:
	@make -s -C $(LIBFT_DIR) fclean
	@$(RM) -r $(OBJ_DIR)
	@$(RM) valgrind.log $(NAME)
	@echo "(╯°□°）╯︵ ┻━┻  Pipex obliterated. Objects, logs, binary, and libft.a wiped. ✨"

# Clean everything: same as clean, but also removes the final binary again (just in case)
fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "(⌐■_■)🔥 Pipex & libft.a obliterated. fclean complete. 💣"

# Rebuild everything from scratch
re: fclean all
	@echo "(☞ﾟヮﾟ)☞ Recompiled from scratch. Pipex rises again!"

# **************************************************************************** #
#                             EXTRA TARGETS                                    #
# **************************************************************************** #

# Run pipex under Valgrind to check for memory leaks
valgrind:
	@echo "🧠 Initializing neural scan..."
	@echo "🔍 Launching pipex under memory surveillance..."
	@valgrind --leak-check=full --track-fds=yes ./$(NAME) infile \"ls\" \"wc -l\" outfile > valgrind.log 2>&1
	@echo "✅ Memory scan complete. No survivors... hopefully. ☠️"

# Print a funny ASCII message when compilation succeeds
echo:
	@echo "(ﾟ◥益◤ﾟ) P̣̱̣͉̃̋̅ͦ̀ȉ̯͙͍̹̙͊p͍̭̰̎̃e̪̞̦̬̬̐̐x͚͙͕̠̋͌́ͦ ͓͗̃̅͊ͯC̬̥͎o̮̥̓ṁ̠̤̩ͤpͯ̆̽î̦̬͉ͅl̹ͅe͛ͬd̮  (ʘ言ʘ)"

# Declare targets that are not actual files (avoids confusion with files of the same name)
.PHONY: all clean fclean re valgrind echo