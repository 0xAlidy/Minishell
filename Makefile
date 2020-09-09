# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/02 17:12:28 by alidy             #+#    #+#              #
#    Updated: 2020/09/06 23:46:17 by alidy            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


HEADER			=		include/minishell.h

LIBS			=		libft/libftprintf.a

SRC_PATH		=		srcs

SRCS_NAME		=		minishell.c \
						pwd.c 		\
						
OBJS			=		${SRCS:.c=.o}

NAME			=		minishell

RM				=		rm -f

CC				=		clang

FLAGS			=		-Wall -Wextra -Werror

SRCS			=		$(addprefix $(SRC_PATH)/,$(SRCS_NAME))

all:					$(NAME)

%.o: %.c				$(HEADER) $(LIBS)
	@$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@
	
$(NAME):				$(OBJS) $(HEADER)
	@$(MAKE) -C ./libft all
	@$(CC) $(FLAGS) -I $(HEADER) -o $(NAME) ${LIBS} $(SRCS) libft/libftprintf.a

clean:
	@$(MAKE) clean -C ./libft
	@echo "\x1b[36m[OK] \033[0m \x1b[31m Removing File object\033[0m"
	@$(RM) $(OBJS)

fclean:					clean
	@$(MAKE) fclean -C ./libft
	@echo "\x1b[36m[OK] \033[0m \x1b[31m Removing All\033[0m"
	@$(RM) $(NAME)

re:                                fclean all		
	
