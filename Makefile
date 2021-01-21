# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/02 17:12:28 by alidy             #+#    #+#              #
#    Updated: 2021/01/21 13:18:10 by alidy            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


HEADER			=		include/minishell.h

LIBS			=		libft/libft.a

SRC_PATH		=		srcs

SRCS_NAME		=		minishell.c 	\
						ms_parsing.c 	\
						ms_env.c 		\
						ms_utils.c		\
						ms_exec.c 		\
						ms_echo.c		\
						ms_pwd.c 		\
						ms_free.c 		\
						ms_env_utils.c 	\
						ms_export.c 	\
						ms_unset.c 		\

						
OBJS			=		${SRCS:.c=.o}

NAME			=		minishell

RM				=		rm -f

CC				=		clang

FLAGS			=		-Wall -Wextra -Werror

SRCS			=		$(addprefix $(SRC_PATH)/,$(SRCS_NAME))

all:					NAME

%.o: %.c				$(HEADER)
	@echo "\033[0;32m[OK] \033[0m \033[0;33m Compiling:\033[0m" $<
	@$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@

NAME:				$(OBJS) $(HEADER) 
	@echo "\x1b[36m\n[OK] \033[0m \x1b[35m Compiling Minishell\033[0m\n"
	@$(MAKE) -C ./libft
	@$(CC) $(FLAGS) -I $(HEADER) -o $(NAME) ${LIBS} $(SRCS)
	@echo "        .__       .__       .__           .__  .__"
	@echo "  _____ |__| ____ |__| _____|  |__   ____ |  | |  |"
	@echo " /     \|  |/    \|  |/  ___/  |  \_/ __ \|  | |  |"
	@echo "|  Y Y  \  |   |  \  |\___ \|   Y  \  ___/|  |_|  |__"
	@echo "|__|_|  /__|___|  /__/____  >___|  /\___  >____/____/"
	@echo "      \/        \/        \/     \/     \/"
	
clean:
	@$(MAKE) clean -C ./libft
	@echo "\x1b[36m[OK] \033[0m \x1b[31m Removing File object\033[0m"
	@$(RM) $(OBJS)

fclean:					clean
	@$(MAKE) fclean -C ./libft
	@echo "\x1b[36m[OK] \033[0m \x1b[31m Removing All\033[0m"
	@$(RM) $(NAME)

re:                                fclean all		