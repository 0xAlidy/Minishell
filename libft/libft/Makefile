# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 09:32:01 by alidy             #+#    #+#              #
#    Updated: 2020/09/06 21:52:09 by alidy            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


NAME 	= 	libft.a

HEADERS	=	libft.h

CC		=	clang

FLAG 	= 	-Wall -Wextra -Werror

OPTION	= 	-c

SRCS	= 	ft_atoi.c				\
			ft_bzero.c				\
			ft_isalnum.c			\
			ft_isalpha.c			\
			ft_isascii.c			\
			ft_isdigit.c			\
			ft_isprint.c			\
			ft_memccpy.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_memcpy.c				\
			ft_memmove.c 			\
			ft_memset.c				\
			ft_strchr.c				\
			ft_strdup.c				\
			ft_strjoin.c			\
			ft_strlcat.c			\
			ft_strlcpy.c			\
			ft_strlen.c				\
			ft_strncmp.c			\
			ft_strnstr.c			\
			ft_strrchr.c			\
			ft_strtrim.c			\
			ft_substr.c 			\
			ft_tolower.c			\
			ft_toupper.c			\
			ft_calloc.c 			\
			ft_itoa.c 				\
			ft_putchar_fd.c 		\
			ft_putendl_fd.c 		\
			ft_putnbr_fd.c  		\
			ft_putstr_fd.c  		\
			ft_split.c				\
			ft_strmapi.c			\
			ft_intlen.c				\
			ft_strjoin_free.c 		\
			get_next_line_utils.c   \
			get_next_line.c 		\


SRCSB	=	ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c		\
			ft_lstdelone_bonus.c 	\
			ft_lstiter_bonus.c		\
			ft_lstlast_bonus.c		\
			ft_lstmap_bonus.c		\
			ft_lstnew_bonus.c		\
			ft_lstsize_bonus.c		\
			ft_lstadd_back_bonus.c	\
			
OBJS	= 	$(SRCS:.c=.o)

OBJSB	= 	$(SRCSB:.c=.o)

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
		ar rcs $(NAME) $(OBJS)

bonus   :	$(OBJS) $(OBJSB) 
		ar rcs $(NAME) $(OBJS) $(OBJSB)

%.o: %.c $(HEADERS)
		$(CC) $(FLAG) -c $< -o $@ -I $(HEADERS)

clean	:
		/bin/rm -f $(OBJS) $(OBJSB)
			
fclean	:	clean	
		/bin/rm -f $(NAME)

re		: 	fclean all
