# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 11:23:23 by romlambe          #+#    #+#              #
#    Updated: 2024/05/16 19:33:40 by jeguerin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strcmp.c\
	ft_strjoin.c ft_strmapi.c ft_striteri.c ft_itoa.c ft_split.c ft_strtrim.c \
	ft_string_cpy.c ft_strndup.c ft_isspace.c

SRCBONUS 	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

NAME		=	libft.a

OBJ			=	$(SRC:.c=.o)

OBJBONUS	=	$(SRCBONUS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra

RM= rm -f

ifdef MAKEBONUS
			OBJ = $(OBJBONUS)
endif

all:	$(NAME)

$(NAME): $(OBJ)
			ar rcs $(NAME) $(OBJ)

%.o: %.c
		$(CC) $(CFLAGS) -o $@ -c $<
bonus: all
			make MAKEBONUS=1
clean:
			$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re
