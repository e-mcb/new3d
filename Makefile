## **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME		= parser
CC			= cc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_PATH)
RM			= rm -f

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRCS		=	init.c \
				main.c \
				render.c \
				raycast.c \
			  	parsing/parsing.c \
				parsing/spawn.c \
			  	parsing/validate_map.c \
			  	parsing/fill_struct.c \
			  	utils/utils.c \
				utils/utils_array.c \
				utils/new_split.c \
				utils/cleanup_utils.c \
				utils/maths_utils.c \
				utils/hooks.c

OBJS		= $(SRCS:.c=.o)

# **************************************************************************** #
#                                   LIBFT                                      #
# **************************************************************************** #

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                                   MINILIBX                                   #
# **************************************************************************** #

MLX_REPO	= https://github.com/42Paris/minilibx-linux.git
MLX_PATH	= minilibx
MLX			= $(MLX_PATH)/libmlx.a
MLX_FLAGS	= -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(MLX) $(LIBFT) $(NAME)

$(LIBFT):
	@echo "📚 Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(MLX):
	@echo "🧩 Checking MiniLibX..."
	@git clone $(MLX_REPO) $(MLX_PATH) 2>/dev/null || true
	@$(MAKE) -C $(MLX_PATH)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) built successfully!"

clean:
	@$(RM) $(OBJS)
	@[ -d $(LIBFT_DIR) ] && $(MAKE) -C $(LIBFT_DIR) clean || true
	@[ -d $(MLX_PATH) ] && $(MAKE) -C $(MLX_PATH) clean || true
	@echo "🧹 Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@[ -d $(LIBFT_DIR) ] && $(MAKE) -C $(LIBFT_DIR) fclean || true
	@rm -rf $(MLX_PATH)
	@echo "🗑️  Full clean done."

re: fclean all

.PHONY: all clean fclean re
