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
	@echo "ʟɪʙꜰᴛ ᴄᴏᴍᴘɪʟᴇᴅ ᴀɴᴅ ꜱᴜᴍᴍᴏɴᴇᴅ ᴘʀᴇᴘᴀʀᴇ ꜰᴏʀ ʀᴇᴜꜱᴇ \n"

$(NAME): $(OBJS)
	@$(AR) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "🧽  ᴏʙᴊᴇᴄᴛ ꜰɪʟᴇꜱ ᴠᴀɴɪꜱʜᴇᴅ. ᴛʜᴇ ꜰᴏʀɢᴇ ɪꜱ ᴄʟᴇᴀɴ."

fclean: clean
	@$(RM) $(NAME)
	@echo "💀 $(NAME) ꜱᴀᴄʀɪꜰɪᴄᴇᴅ ᴛᴏ ᴛʜᴇ ʙɪɴᴀʀʏ ɢᴏᴅꜱ ꜰᴄʟᴇᴀɴ ᴄᴏᴍᴘʟᴇᴛᴇ."

re: fclean all
	@echo "🔁 ʟɪʙꜰᴛ ʀᴇʙᴏʀɴ ʀᴇᴄᴏᴍᴘɪʟᴇᴅ ꜰʀᴏᴍ ᴀꜱʜᴇꜱ."


.PHONY: all clean fclean re
