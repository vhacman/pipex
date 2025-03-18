# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:48:43 by vhacman           #+#    #+#              #
#    Updated: 2025/03/18 12:49:18 by vhacman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome dell'eseguibile finale
NAME = pipex

# Il compilatore da utilizzare
CC = gcc

# Flag di compilazione: -Wall (tutti i warning), -Wextra (warning extra), 
# -Werror (tratta i warning come errori)
CFLAGS = -Wall -Wextra -Werror 

# File sorgenti del progetto
SRC = pipex.c utils.c

# Converte i nomi dei file .c in nomi di file .o
OBJ = $(SRC:.c=.o)

# Target di default: se digitiamo 'make' verrà eseguito 'all'
all: $(NAME)


# Target per costruire l'eseguibile:
# 1) Stampa un messaggio.
# 2) Esegue il Makefile della cartella libft 
#    (make -C libft) per compilare la libreria.
# 3) Compila e linka il progetto principale con la libft, usando -I e -L 
#    per includere e linkare.
$(NAME): $(OBJ)
	@echo "Compiling libft..."
	@make -C libft
	$(CC) $(CFLAGS) -Ilibft -o $(NAME) $(OBJ) -Llibft -lft


# Regola generica per compilare i .c in .o
# $< è il nome del file sorgente, $@ è il nome del target (.o)
%.o: %.c
	$(CC) $(CFLAGS) -Ilibft -c $< -o $@



# Pulisce i file oggetto .o del progetto principale
clean:
	rm -f $(OBJ)
	@make clean -C libft 
#@make clean -C libft -> il Makefile esegue il comando make clean all'interno 
# della directory libft


# Pulisce gli oggetti e l'eseguibile finale, e fa lo stesso per la libft
fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

# Ricostruisce il progetto da zero (equivale a fclean + all)
re: fclean all
