# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 10:24:13 by alidy             #+#    #+#              #
#    Updated: 2021/01/11 10:44:09 by alidy            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

HEADER			=		include/libft.h

SRC_PATH		=		src

SRCS_NAME		=		ft_atoi.c				\
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
						ft_printf.c	  	 		\
						ft_itoa_base.c   		\
						ft_get_str_format.c 	\
						ft_int_format.c     	\
						ft_parsing_flags.c  	\
						ft_str_format.c     	\
						ft_un_format.c      	\
						ft_hexa_format.c    	\
						get_next_line_utils.c	\
						get_next_line.c			\

OBJS			=		${SRCS:.c=.o}

NAME			=		libft.a

RM				=		rm -f

CC				=		gcc

FLAGS			=		-Wall -Wextra -Werror

SRCS			=		$(addprefix $(SRC_PATH)/,$(SRCS_NAME))

all:                    $(NAME)

%.o: %.c                $(HEADER)
	@echo "\033[0;32m[OK] \033[0m \033[0;33m Compiling:\033[0m" $<
	@gcc $(FLAGS) -I $(HEADER) -c $< -o $@

$(NAME):                $(OBJS) $(HEADER)
	@echo "\x1b[36m\n[OK] \033[0m \x1b[35m Compiling Libft\033[0m\n"
	@ar rcs $(NAME) $(OBJS)

clean:
	@echo "\x1b[36m[OK] \033[0m \x1b[31m Removing File object\033[0m"
	@$(RM) $(OBJS)

fclean:                            clean
	@echo "\x1b[36m[OK] \033[0m \x1b[31m Removing All\033[0m"
	@$(RM) $(NAME)

re:                                fclean all

LIBFT:
	@echo ".----------------.  .----------------.  .----------------.  .----------------.  .----------------.  " 
	@echo "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |"  
	@echo "| |   _____      | || |     _____    | || |   ______     | || |  _________   | || |  _________   | |"  
	@echo "| |  |_   _|     | || |    |_   _|   | || |  |_   _ \    | || | |_   ___  |  | || | |  _   _  |  | |"  
	@echo "| |    | |       | || |      | |     | || |    | |_) |   | || |   | |_  \_|  | || | |_/ | | \_|  | |"  
	@echo "| |    | |   _   | || |      | |     | || |    |  __'.   | || |   |  _|      | || |     | |      | |"  
	@echo "| |   _| |__/ |  | || |     _| |_    | || |   _| |__) |  | || |  _| |_       | || |    _| |_     | |"  
	@echo "| |  |________|  | || |    |_____|   | || |  |_______/   | || | |_____|      | || |   |_____|    | |"  
	@echo "| |              | || |              | || |              | || |              | || |              | |"  
	@echo "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |"  
	@echo "'----------------'  '----------------'  '----------------'  '----------------'  '----------------'  " 


.PHONY:                         clean fclean