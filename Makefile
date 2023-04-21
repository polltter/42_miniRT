# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 18:45:23 by touteiro          #+#    #+#              #
#    Updated: 2023/04/19 11:44:38 by touteiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
CC		= cc
CFLAGS	= -I incs -Imlx -Wall -Werror -Wextra -g3 -O3 -fsanitize=address

LIST_SRCS_FILES		= list_utils list_utils_2 list_utils_3 list_utils_4
STRS_SRCS_FILES		= ft_split  strings  strings_utils1  strings_utils2
GNL_SRCS_FILES		= get_next_line  get_next_line_utils
UTILS_FILES			= mlx_utils draw_utils utils parse_utils
HANDLES_FILES		= keys mouse
BODYS_FILES			= build build_bodys build_utils build_lights
GENERAL_SRC_FILES	= main

LIST_SRCS		= ${addsuffix .c, ${addprefix srcs/utils/list/, ${LIST_SRCS_FILES}}}
STRS_SRCS		= ${addsuffix .c, ${addprefix srcs/utils/strs/, ${STRS_SRCS_FILES}}}
GNL_SRCS		= ${addsuffix .c, ${addprefix srcs/utils/gnl/, ${GNL_SRCS_FILES}}}
UTILS_SRCS		= ${addsuffix .c, ${addprefix srcs/utils/, ${UTILS_FILES}}}
HANDLES_SRCS	= ${addsuffix .c, ${addprefix srcs/handles/, ${HANDLES_FILES}}}
BODYS_SRCS		= ${addsuffix .c, ${addprefix srcs/bodys/, ${BODYS_FILES}}}
GENERAL_SRC		= ${addsuffix .c, ${addprefix srcs/, ${GENERAL_SRC_FILES}}}

SRCS	=  ${GENERAL_SRC} ${LIST_SRCS} ${UTILS_SRCS} ${HANDLES_SRCS} ${STRS_SRCS} ${GNL_SRCS} ${BODYS_SRCS}

INCS_FILES	= miniRT.h structs.h list_utils.h get_next_line.h
INCS	= ${addprefix incs/, ${INCS_FILES}}

OBJ		= ${addprefix objs/, ${SRCS:.c=.o}}
OBJ	= ${addprefix obj/, ${SRCS:.c=.o}}

obj/%.o: %.c ${INCS}
	@mkdir -p ${@D}
	$(CC) ${CFLAGS} -I/usr/include -Imlx -c $< -o $@
	@echo "\033[33m[OK]	" $@ "\033[0m"

${NAME}:  ${OBJ}
	@make --no-print-directory -C mlx
	@$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  -o $(NAME)
	@echo -n "\033[92m[OK]	 "
	@echo -n $(NAME)
	@echo " ready to use\033[0m"
	@echo "------------------------------"
	
all: $(NAME)

clean:
	@rm -rf obj/
	@echo "\033[31mTemporary object files deleted\033[0m"

clean_mlx:
	@make clean -C mlx

fclean: clean
	@rm -rf ${NAME}
	@echo "\033[31mExecutable deleted\033[0m"

fclean_all: fclean clean_mlx

newLine:
	@echo ""

re: fclean newLine all

norm:
	norminette -R CheckForbiddenSourceHeader srcs/*
	norminette -R CheckDefine incs/*

.SILENT: ${OBJ}

.PHONY: all re clean fclean