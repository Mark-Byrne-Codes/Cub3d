# ================================= COLORS =================================== #
BOLD	= \033[1m
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
RESET	= \033[0m

# ================================ SETTINGS ================================== #
NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBMLX		= ./MLX42
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
HEADERS		= -I $(LIBMLX)/include -I include
LIBS		= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# ================================ SOURCES =================================== #

SRCS	:= srcs/main.c \
			srcs/parse/parsing.c \
			srcs/parse/flood_fill.c\
			srcs/parse/parse_error.c \
			srcs/parse/map_init.c \
			srcs/parse/map_config.c \
			srcs/parse/utils.c \
			srcs/parse/validate_map.c \
			srcs/game/game_loop.c \
			srcs/game/game_utils.c \
			srcs/game/raycast_utils.c \
			srcs/game/graphics.c \
			srcs/game/raycast.c \
   

OBJ_DIR		= objs
OBJS		= $(SRCS:srcs/%.c=$(OBJ_DIR)/%.o)

# ================================ RULES ===================================== #
all: libmlx $(LIBFT) $(NAME)

$(NAME): $(OBJS) | $(LIBFT)
	@echo "$(CYAN)$(BOLD)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)✅ Successfully built $(NAME)!$(RESET)"

libmlx: $(LIBMLX)/build/libmlx42.a

$(LIBMLX)/build/libmlx42.a:
	@echo "$(YELLOW)$(BOLD)🚀 Cloning and building MLX42...$(RESET)"
	@if [ ! -d "$(LIBMLX)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@echo "$(GREEN)$(BOLD)✔️  MLX42 ready!$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)$(BOLD)✔️  libft ready!$(RESET)"

$(OBJ_DIR)/%.o: srcs/%.c | libmlx
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🔧 Compiling: $(PURPLE)$<$(RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/game
	@mkdir -p $(OBJ_DIR)/parse

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)✔️  Object files removed!$(RESET)"

fclean: clean
	@echo "$(RED)🔥 Full clean...$(RESET)"
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✔️  Everything cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re libmlx