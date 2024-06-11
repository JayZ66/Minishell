# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 18:59:35 by jeza              #+#    #+#              #
#    Updated: 2024/06/11 16:54:24 by romlambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'executable
NAME = minishell

# Compilateur
CC := gcc

# Options de compilation
CFLAGS := -Wall -Wextra -Werror -Iheaders/ -g

#Liste des fichiers source.
SRCS = 	Sources/main.c Sources/utils.c \
		Sources/modify_env.c Sources/built_in.c \
		Sources/builtin_export.c Sources/execution.c \
		Sources/signals.c Sources/builtin_cd.c Sources/utils1.c \
		Sources/utils2.c Sources/path_to_exec.c Sources/manage_pipes.c \
		Sources/manage_here_doc.c Sources/cd_utils.c \
		Sources/export_utils.c Sources/execute_cmd_only.c Sources/export_utils2.c \
		Sources/builtin_echo.c Sources/expanser.c \
		Sources/expanser2.c Sources/utils3.c Sources/new_exec.c \
		Sources/exec_builtin.c Sources/manage_input.c Sources/manage_output.c \
		Sources/get_var_env.c \
		Parsing/clean_nodes.c Parsing/copy_list.c Parsing/extract_cmd.c \
		Parsing/init_clean_nodes.c Parsing/clean_nodes2.c Parsing/init_nodes.c \
		Parsing/redirection.c Parsing/tokenize.c Parsing/utils_list.c \
		Sources/echo_utils.c  Parsing/realloc_env.c Parsing/tokenize2.c \
		Parsing/handle_redirection.c Parsing/redirection_utils.c Parsing/copy_final_list.c\
		Parsing/init_final_nodes.c Parsing/manage_final_nodes.c\
		Sources/var_env.c Sources/var_env_utils.c Sources/quotes.c \
		Sources/exec_multiple_cmd.c Sources/exec_process_by_process.c Sources/cd_utils2.c \
		Sources/export_utils3.c Sources/builtin_exit.c Sources/builtin_unset.c \
		Sources/var_env2.c Sources/main_utils.c Sources/free_lst.c\

LIBFT = Libft/libft.a
GETNEXTLINE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
PRINTF = ft_printf/libftprintf.a

OBJS = $(SRCS:.c=.o)
GETNEXTLINE_OBJ := $(GETNEXTLINE:.c=.o)

# Regle par defaut pour l'executable
all: author project $(NAME)

# Regles pour afficher l'auteur et le projet.
author:
	@echo "Authors : romlambe & jeguerin\n"
project:
	@echo "Project : Minishell\n"

$(LIBFT):
	make -C Libft

$(PRINTF):
	make -C ft_printf

# Regle pour creer l'executable en liant les objets.
# $(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ) -o $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(GETNEXTLINE_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(GETNEXTLINE_OBJ) $(LIBFT) $(PRINTF) -o $(NAME) -lreadline

# Regle pour nettoyer les fichiers objets.
clean:
	$(RM) $(OBJS)
	$(RM) $(GETNEXTLINE_OBJ)
	make clean -C Libft
	make clean -C ft_printf

# Regle pour nettoyer les fichiers objets et l'executable.
fclean: clean
	$(RM) $(NAME)
	make fclean -C Libft
	make fclean -C ft_printf

# Regle pour reconstruire le projet (clean, puis all)
re: author fclean all

# Declarer les regles comme des cibles .phony pour eviter des conflits avec
# des fichiers du meme nom.
.PHONY: all clean fclean re
