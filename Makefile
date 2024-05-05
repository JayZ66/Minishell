# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romlambe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 18:59:35 by jeza              #+#    #+#              #
#    Updated: 2024/05/05 17:13:33 by romlambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME = minishell

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -Werror -Iheaders/ -g

#Liste des fichiers source.
SRCS = main.c clean_nodes.c copy_list.c extract_cmd.c init_clean_nodes.c\
		init_nodes.c redirection.c tokenize.c utils_list.c

LIBFT = Libft/libft.a
# PRINTF = printf/libftprintf.a

OBJS = $(SRCS:.c=.o)

# Regle par defaut pour l'executable
all: author project $(NAME)

# Regles pour afficher l'auteur et le projet.
author:
	@echo "Authors : romlambe & jeguerin\n"
project:
	@echo "Project : Minishell\n"

$(LIBFT):
	make -C Libft

# $(PRINTF):
# 	make -C printf

# Regle pour creer l'executable en liant les objets.
# $(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ) -o $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

# Regle pour nettoyer les fichiers objets.
clean:
	$(RM) $(OBJS)
	make clean -C Libft

# Regle pour nettoyer les fichiers objets et l'executable.
fclean: clean
	$(RM) $(NAME)
	make fclean -C Libft

# Regle pour reconstruire le projet (clean, puis all)
re: author fclean all

# Declarer les regles comme des cibles .phony pour eviter des conflits avec
# des fichiers du meme nom.
.PHONY: all clean fclean re
