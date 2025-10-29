# **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME		= parser
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRCS		=	init.c \
				main.c \
			  	parsing/parsing.c \
				parsing/spawn.c \
			  	parsing/validate_map.c \
			  	parsing/fill_struct.c \
			  	utils/utils.c \
				utils/utils_array.c \
				utils/new_split.c \
				utils/cleanup_utils.c \
				utils/maths_utils.c
			  

OBJS		= $(SRCS:.c=.o)

# **************************************************************************** #
#                                   LIBFT                                      #
# **************************************************************************** #

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "✅ $(NAME) built successfully!"

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "🧹 Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "🗑️  Full clean done."

re: fclean all

.PHONY: all clean fclean re
