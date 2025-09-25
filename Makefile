# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fabi <fabi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/03 14:12:42 by fabi              #+#    #+#              #
#    Updated: 2025/09/18 23:28:01 by fabi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx_linux -I/usr/include/SDL2
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lSDL2 -lSDL2_mixer

SRCS = src/main.c \
       src/game.c \
       src/movement.c \
       src/simple_map_parser.c \
       src/texture_loader.c \
       src/start_screen.c \
       src/raycast.c \
       src/wall_rendering.c \
       src/draw.c \
       src/hooks.c \
       src/game_loop.c \
       src/audio.c \
       src/end_screen.c \
       src/timer_system.c \
       src/cleanup.c \
       src/torch_animation.c \
       src/utils.c \
       src/string_utils.c \
       src/get_next_line.c \
       src/conversion.c \
       src/validate.c \
       src/movement_utils.c \
	   src/timer_utils.c \
	   src/door_interaction.c \
	   src/init.c \
	   src/texture_utils.c \
	   src/torch_loader.c\
	   src/string_utils_split.c\
	   src/draw_map.c \
	   src/map_utils.c \
	   src/parser_config.c \
	   src/parser_utils.c \
	   src/raycast_utils.c \
	   src/valid.c \
	   src/validate_complete.c\
	   src/validate_flood.c \
	   src/validate_borders.c \
	   src/map_extraction.c \
	   src/wall_texture_helpers.c \
	   src/wall_drawing.c \
	   src/timer_texture_loader.c \
	   src/color_validation.c \
	   src/door_initialization_fix.c \
	   src/simple_map_parser_helpers.c \
	   src/config_parser_helpers.c \
	   src/get_next_line_helpers.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "";
	@echo "        ░░   \033[38;5;94m▓▓     \033[38;5;94m▓▓▓▓▓▓▓\033[0m \033[38;5;94m▓▓▓▓\033[0m                     ";
	@echo "    ░░░░░     \033[38;5;94m▓▓\033[0m ░░ \033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓\033[0m    ██████████████████";
	@echo " ░    ░░░    ░\033[38;5;94m▓▓▓\033[0m░░ \033[38;5;94m ▓▓▓▓▓▓▓\033[0m███████████████████████\033[0m  ";
	@echo "░░░ ░░      ░░ \033[38;5;94m▓▓▓▓  ▓▓▓▓▓▓▓\033[0m       ▐            ██ ██";
	@echo "     ░░░░░░     \033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓\033[0m     █████ ▒▒▒▒▒▒▒  ███\033[31m░░░\033[0m";
	@echo "      ░░░░░░      \033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓\033[0m          ▒Θ▒▒Θ ▒ ██\033[31m░░░░\033[0m";
	@echo "      ░░░░░░░       \033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓\033[0m    ▄▄▄▄▄▒▒▒▒▒▒██ \033[31m░░░░\033[0m";
	@echo "       ░░░░░░░░     \033[38;5;94m▓▓▓▓▓▓▓▓▓▓\033[0m   \033[0m ▐\\   /▐▒▒▒▒██\033[31m░░\033[0m████";
	@echo "           ░░░░░░   \033[38;5;94m▓▓▓▓▓▓▓▓▓\033[0m    \033[0m ▌ \\ ░░░░░░░███ \033[31m░░░\033[0m";
	@echo "          ░░░░░░░  █\033[38;5;94m▓▓▓▓▓▓▓▓▓▓\033[0m████░░░░░░░█░░░█  \033[31m░░░░░\033[0m";
	@echo "          ░░░░░░░██\033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓\033[0m  ░░░░░░ █████ \033[31m░░░░░░░░\033[0m";
	@echo "           ██░░░░  \033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓\033[0m  ░░ ████ \033[31m░░░░░░░░░░░░░\033[0m";
	@echo "         ██████████\033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓\033[0m█████\033[31m░░░░░░░░░░░░\033[0m ████   ";
	@echo "       █\033[33m░\033[0m\033[33m░\033[0m██\033[31m░░░░░░░\033[0m\033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓▓\033[0m·█\033[33m░\033[0m\033[33m░\033[0m█\033[31m░░░░░░░\033[0m███▓\033[0m    ";
	@echo "        █▄▄▄▄██████\033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓▓▓▓\033[0m▄▄▄█▄\033[31m░░\033[0m█████▓▓██\033[0m    ";
	@echo "         ████\033[31m░░░░░░\033[0m\033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓▓▓▓\033[0m██░░\033[0m████████▓██\033[0m     ";
	@echo "           ███████\033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\033[0m██    ██████      ";
	@echo "                 \033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\033[0m                ";
	@echo "                \033[38;5;94m▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\033[0m     ";
	@echo "";
	@echo "                𝖜𝖍𝖆𝖙 𝖉𝖎𝖉 𝖞𝖔𝖚 𝖉𝖔 𝖜𝖗𝖔𝖓𝖌";
	@echo "                   𝖜𝖍𝖞 𝖆𝖗𝖊 𝖞𝖔𝖚 𝖍𝖊𝖗𝖊";
	@echo "            𝖒𝖆𝖞𝖇𝖊 \033[33m𝖗𝖊𝖒𝖊𝖒𝖇𝖊𝖗𝖎𝖓𝖌\033[0m 𝖜𝖎𝖑𝖑 𝖘𝖆𝖛𝖊 𝖞𝖔𝖚";
	@echo "";


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re