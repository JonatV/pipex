# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jveirman <jveirman@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 13:31:02 by jveirman          #+#    #+#              #
#    Updated: 2024/04/24 15:06:36 by jveirman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = gcc

LIBFT		=	./libft/libft.a

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SUCCESS	=	\033[30;42;1m
END		=	\033[0m

SRCS = 	src/pipex.c\
		src/utils.c
		
SRCS_BONUS = 	src_bonus/pipex_bonus.c\
				src_bonus/utils_bonus.c\
				src_bonus/get_delimiter_bonus.c
				
OBJS 	= 	${SRCS:.c=.o}

OBJS_BONUS 	= 	${SRCS_BONUS:.c=.o}
all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	make all -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@
	@make art

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJS_BONUS)
	make all -C libft
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $@
	@make art_bonus


clean :
	$(RM) $(OBJS) $(OBJS_BONUS)
	make clean -C libft

fclean : clean
	$(RM) $(NAME) $(NAME_BONUS)
	$(RM) $(LIBFT)

re : fclean all

art :
	@clear
	@echo " "
	@echo "              ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄"
	@echo "             █▓▓█      ▄▄▄▄▄▄▄ ▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄   █"
	@echo "            █▓▒▒▓█    █       █   █       █       █  █▄█  █   █"
	@echo "           █▓░░▒▒▓█   █    ▄  █   █    ▄  █    ▄▄▄█       █    █"
	@echo "           █ ░░░▒▓█   █   █▄█ █   █   █▄█ █   █▄▄▄█       █    █"
	@echo "           █   ░▒▓█   █    ▄▄▄█   █    ▄▄▄█    ▄▄▄██     █     █"
	@echo "           █  ░░▒▓█   █   █   █   █   █   █   █▄▄▄█   ▄   █    █"
	@echo "            █ ░▒▒█    █▄▄▄█   █▄▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄█ █▄▄█   █"
	@echo "             █▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀"
	@echo " "

art_bonus :
	@clear
	@echo " "
	@echo "              ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄"
	@echo "             █▓▓█      ▄▄▄▄▄▄▄ ▄▄▄ ▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄ ▄▄   ▄▄   █"
	@echo "            █▓▒▒▓█    █       █   █       █       █  █▄█  █   █"
	@echo "           █▓░░▒▒▓█   █    ▄  █   █    ▄  █    ▄▄▄█       █    █"
	@echo "           █ ░░░▒▓█   █   █▄█ █   █   █▄█ █   █▄▄▄█       █    █"
	@echo "           █   ░▒▓█   █    ▄▄▄█   █    ▄▄▄█    ▄▄▄██     █     █"
	@echo "           █  ░░▒▓█   █   █   █   █   █   █   █▄▄▄█   ▄   █    █"
	@echo "            █ ░▒▒█    █▄▄▄█   █▄▄▄█▄▄▄█   █▄▄▄▄▄▄▄█▄▄█ █▄▄█   █"
	@echo "             █▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀"
	@echo "                        ▀▀██ ▄▄▀█▀▄▄▀█ ▄▄▀█ ██ █ ▄▄█▀▀"
	@echo "                          ██ ▄▄▀█ ██ █ ██ █ ██ █▄▄▀█"
	@echo "                          ██ ▀▀ ██▄▄██▄██▄██▄▄▄█▄▄▄█"
	@echo "                           ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"
	@echo " "

.PHONY: all clean fclean re art art_bonus
