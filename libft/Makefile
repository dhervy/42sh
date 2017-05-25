# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/07/30 22:35:18 by vde-la-s          #+#    #+#              #
#    Updated: 2017/03/08 12:33:23 by vde-la-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC  			= 	get_next_line.c	\
					ft_memset.c		\
					ft_bzero.c		\
					ft_memcpy.c		\
					ft_memccpy.c	\
					ft_memmove.c	\
					ft_memchr.c		\
					ft_memcmp.c		\
					ft_strlen.c		\
					ft_strdup.c		\
					ft_strndup.c	\
					ft_strcpy.c		\
					ft_strncpy.c	\
					ft_strcat.c		\
					ft_strncat.c	\
					ft_strlcat.c	\
					ft_strchr.c		\
					ft_strrchr.c	\
					ft_strstr.c		\
					ft_strnstr.c	\
					ft_strcmp.c		\
					ft_strncmp.c	\
					ft_atoi.c		\
					ft_isalpha.c	\
					ft_isdigit.c	\
					ft_isalnum.c	\
					ft_isascii.c	\
					ft_isprint.c	\
					ft_toupper.c	\
					ft_tolower.c	\
					ft_memalloc.c	\
					ft_memdel.c		\
					ft_strnew.c		\
					ft_strdel.c		\
					ft_strclr.c		\
					ft_striter.c	\
					ft_striteri.c	\
					ft_strmap.c		\
					ft_strmapi.c	\
					ft_strequ.c		\
					ft_strnequ.c	\
					ft_strsub.c		\
					ft_strjoin.c	\
					ft_strtrim.c	\
					ft_strsplit.c	\
					ft_itoa.c		\
					ft_putchar.c	\
					ft_putstr.c		\
					ft_putendl.c	\
					ft_putnbr.c		\
					ft_putchar_fd.c	\
					ft_putstr_fd.c	\
					ft_putendl_fd.c	\
					ft_putnbr_fd.c	\
					ft_lstnew.c		\
					ft_lstdelone.c	\
					ft_lstdel.c		\
					ft_lstadd.c		\
					ft_lstiter.c	\
					ft_lstmap.c		\
					ft_split_out.c	\
					ft_isspace.c


OBJ = $(SRC:.c=.o)
FLAGS =  -Wall -Wextra -Werror
INCLUDE = -I includes

all: $(NAME)

$(NAME):
		@gcc $(FLAGS) $(INCLUDE) -c $(SRC)
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)
clean:
		@rm -rf $(OBJ)
fclean: clean
		@rm -rf $(NAME)
re: fclean all
