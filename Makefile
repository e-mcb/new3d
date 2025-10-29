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

SRCS		= cleanup_utils.c \
			  init.c \
			  main.c \
			  new_split.c \
			  parsing.c \
			  utils.c \
			  spawn.c \
			  validate_map.c \
			  lst_utils.c

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
