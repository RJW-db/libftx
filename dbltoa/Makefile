# Compiler and flags
NAME		= floattest
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
CFLAGS		+= -g

# Header files path
SRC_HEADER	= ./includes

# Source directories
SRC_DIRS	= srcs_libft dbltoa
OBJ_PATH	= obj

# Sources
SRCS		=	dbltoa/dbltoa.c \
				dbltoa/fraction_conversion.c \
				dbltoa/fraction_operations.c \
				dbltoa/convert_binary_to_decimal.c \
				dbltoa/convert_binary_to_decimal2.c \
				dbltoa/scientific_notation.c \
				dbltoa/double_to_string.c \
				dbltoa/precision.c \
				dbltoa/init_helpers.c \
				dbltoa/ft_addition.c	\
				dbltoa/ft_subtraction.c \
				dbltoa/ft_multiply.c \
				dbltoa/ft_division.c \
				srcs_libft/ft_memset.c \
				srcs_libft/ft_atoi.c \
				srcs_libft/ft_strlen.c \
				srcs_libft/ft_strchr.c \
				srcs_libft/ft_strlcpy.c \
				srcs_libft/ft_strjoin.c \
				srcs_libft/ft_putstr_fd.c \
				srcs_libft/ft_substr.c \
				srcs_libft/ft_itoa_base.c \
				srcs_libft/ft_memmove.c

# Create list of object files (replace .c with .o and store in OBJ_PATH)
OBJ			= $(SRCS:%.c=$(OBJ_PATH)/%.o)

# Colors
PINK 		= \033[35m
BLUE		= \033[34;1m
GREEN		= \033[32;1m
CORAL		= \033[38;2;255;127;80m
BOLD		= \033[1m
ITALIC		= \033[3m
UNDER 		= \033[4m
RESET		= \033[0m

# Targets
all:		$(NAME)

# Build the executable
$(NAME):	$(OBJ)
		ar rcs $(NAME) $(OBJ)

# Rule for compiling .c into .o in obj/ folder
$(OBJ_PATH)/%.o: %.c
		@mkdir -p $(OBJ_PATH)/srcs_libft
		@mkdir -p $(OBJ_PATH)/dbltoa
		$(CC) $(CFLAGS) -c -I $(SRC_HEADER) -o $@ $<

# Clean
clean:
		@rm -rf $(OBJ_PATH)
		@echo "$(GREEN) $(ITALIC) ✅ Cleaned object files ✅$(RESET)"

fclean: clean
		@rm -f $(NAME)
		@echo "$(GREEN) $(ITALIC)   ✅ Cleaned executable ✅$(RESET)"

re: fclean all

.PHONY:	all clean fclean re
