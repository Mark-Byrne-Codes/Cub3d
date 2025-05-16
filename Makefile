NAME	:= cub3d
CFLAGS	:= -Wextra -Wall -Werror
CC = cc
LIBMLX	:= ./MLX42
LIBFT = libft/libft.a

HEADERS	:= -I $(LIBMLX)/include
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	:= srcs/main.c \
			srcs/utils.c \
			srcs/game/run_game.c \
			srcs/game/init.c \
			srcs/game/game_utils.c \
			srcs/game/raycast_utils.c \
			srcs/game/render.c \
			srcs/game/raycast.c \
			srcs/game/minimap.c \
			srcs/parse/parsing.c \
      srcs/parse/flood_fill.c\
      srcs/parse/parse_error.c \
      srcs/parse/init_map.c \
      srcs/parse/utils.c\
      srcs/parse/validate_map.c\
   

OBJS	:= ${SRCS:.c=.o}

all: libmlx $(LIBFT) $(NAME)

$(LIBMLX):
	@git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	@make -C ./libft

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C ./libft


fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re libmlx