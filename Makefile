# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 10:15:55 by vhacman           #+#    #+#              #
#    Updated: 2025/03/24 12:40:50 by vhacman          ###   ########.fr        #
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
	   $(UTILS_DIR)/path_utils.c \
	   $(UTILS_DIR)/errors.c

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
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@	

# Build libft.a by running libft's Makefile
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) $(notdir $@)

# Remove object files, log, binary, and libft
clean:
	@make -s -C $(LIBFT_DIR) fclean --silent > /dev/null
	@$(RM) -r $(OBJ_DIR)
	@$(RM) valgrind.log $(NAME)
	@echo "✨ ᴘɪᴘᴇx ᴏʙʟɪᴛᴇʀᴀᴛᴇᴅ ᴏʙᴊᴇᴄᴛꜱ ʟᴏɢꜱ ʙɪɴᴀʀʏ ᴀɴᴅ ʟɪʙꜰᴛᴀ ᴡɪᴘᴇᴅ. ✨"

# Remove everything, including final binary
fclean: clean
	@$(RM) $(NAME)
	@echo "(⌐■_■)🔥 ᴘɪᴘᴇx ᴏʙʟɪᴛᴇʀᴀᴛᴇᴅ ꜰᴄʟᴇᴀɴ ᴄᴏᴍᴘʟᴇᴛᴇ. 💣"

# Rebuild from scratch
re: fclean all
	@echo "(☞ﾟヮﾟ)☞ ʀᴇᴄᴏᴍᴘɪʟᴇᴅ ꜰʀᴏᴍ ꜱᴄʀᴀᴛᴄʜ ᴘɪᴘᴇx ʀɪꜱᴇꜱ ᴀɢᴀɪɴ!"

# **************************************************************************** #
#                             EXTRA TARGETS                                    #
# **************************************************************************** #

# Run the program under Valgrind for memory leak detection
valgrind:
	@echo "🧠 ɪɴɪᴛɪᴀʟɪᴢɪɴɢ ɴᴇᴜʀᴀʟ ꜱᴄᴀɴ..."
	@echo "🔍 ʟᴀᴜɴᴄʜɪɴɢ ᴘɪᴘᴇx ᴜɴᴅᴇʀ ᴍᴇᴍᴏʀʏ ꜱᴜʀᴠᴇɪʟʟᴀɴᴄᴇ..."
	@valgrind --leak-check=full --track-fds=yes ./$(NAME) infile \"ls\" \"wc -l\" outfile > valgrind.log 2>&1
	@echo "✅ ᴍᴇᴍᴏʀʏ ꜱᴄᴀɴ ᴄᴏᴍᴘʟᴇᴛᴇ ɴᴏ ꜱᴜʀᴠɪᴠᴏʀꜱ ʜᴏᴘᴇꜰᴜʟʟʏ ☠️"

# Fun success message
echo:
	@echo "ᑭIᑭE᙭ ᑕOᗰᑭIᒪEᗪ"

# Declare targets that aren't actual files
.PHONY: all clean fclean re valgrind echo
