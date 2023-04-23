# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touteiro <touteiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 18:45:23 by touteiro          #+#    #+#              #
#    Updated: 2023/04/22 20:27:34 by touteiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
CC		= cc
CFLAGS	= -I incs -Imlx -Wall -Werror -Wextra -g3 -O3 -march=native -ffast-math -funsafe-math-optimizations -ffinite-math-only #-fsanitize=thread

BODYS_FILES			= build build_bodys build_utils build_lights
CAM_FILES			= rotate_camera
COLLISION_FILES		= collisions
HANDLES_FILES		= keys mouse
THREADS_FILES		= threads
RAYTRACER_FILES		= render raytracer lights
GNL_FILES			= get_next_line  get_next_line_utils
LIST_FILES			= list_utils list_utils_2 list_utils_3 list_utils_4
MATH_FILES			= math coords
STRS_FILES			= ft_split  strings  strings_utils1  strings_utils2
UTILS_FILES			= mlx_utils viewport_utils utils parse_utils color_utils
GENERAL_FILES		= main

BODYS_SRCS			= ${addsuffix .c, ${addprefix srcs/bodys/, ${BODYS_FILES}}}
CAM_SRCS			= ${addsuffix .c, ${addprefix srcs/camera/, ${CAM_FILES}}}
THREADS_SRCS			= ${addsuffix .c, ${addprefix srcs/threads/, ${THREADS_FILES}}}
COLLISION_SRCS		= ${addsuffix .c, ${addprefix srcs/collisions/, ${COLLISION_FILES}}}
HANDLES_SRCS		= ${addsuffix .c, ${addprefix srcs/handles/, ${HANDLES_FILES}}}
RAYTRACER_SRCS		= ${addsuffix .c, ${addprefix srcs/raytracer/, ${RAYTRACER_FILES}}}
GNL_SRCS			= ${addsuffix .c, ${addprefix srcs/utils/gnl/, ${GNL_FILES}}}
LIST_SRCS			= ${addsuffix .c, ${addprefix srcs/utils/list/, ${LIST_FILES}}}
MATH_SRCS			= ${addsuffix .c, ${addprefix srcs/utils/math/, ${MATH_FILES}}}
STRS_SRCS			= ${addsuffix .c, ${addprefix srcs/utils/strs/, ${STRS_FILES}}}
UTILS_SRCS			= ${addsuffix .c, ${addprefix srcs/utils/, ${UTILS_FILES}}}
GENERAL_SRC			= ${addsuffix .c, ${addprefix srcs/, ${GENERAL_FILES}}}

SRCS	=  ${BODYS_SRCS} ${CAM_SRCS} ${COLLISION_SRCS} ${HANDLES_SRCS} \
			${RAYTRACER_SRCS} ${GNL_SRCS} ${LIST_SRCS} ${MATH_SRCS} \
			${STRS_SRCS} ${UTILS_SRCS} ${GENERAL_SRC} ${THREADS_SRCS}

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