# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 10:24:13 by alidy             #+#    #+#              #
#    Updated: 2020/09/06 21:51:58 by alidy            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


HEADER			=		includes/ft_printf.h

LIB				=		libft.a

LIBS			=		libft/libft.a

SRC_PATH		=		src

SRCS_NAME		=		ft_printf.c	  	 		\
						ft_itoa_base.c   		\
						ft_get_str_format.c 	\
						ft_int_format.c     	\
						ft_parsing_flags.c  	\
						ft_str_format.c     	\
						ft_un_format.c      	\
						ft_hexa_format.c    	\

OBJS			=		${SRCS:.c=.o}

NAME			=		libftprintf.a

RM				=		rm -f

CC				=		clang

FLAGS			=		-Wall -Wextra -Werror

SRCS			=		$(addprefix $(SRC_PATH)/,$(SRCS_NAME))

all:					$(LIB) $(NAME)

%.o: %.c 				$(HEADER) $(LIBS)
	@$(CC) $(FLAGS) -I $(HEADER) -c $< -o $@

$(NAME):				$(OBJS) $(HEADER)
	@cp libft/libft.a ./$(NAME)
	@ar rcs $(NAME) $(OBJS)

$(LIB):
	@$(MAKE) -C libft all

clean:
	@$(MAKE) -C libft clean
	@$(RM) $(OBJS)

fclean:                            clean
	@$(MAKE) -C libft fclean
	@$(RM) $(NAME)

re:                                fclean all
