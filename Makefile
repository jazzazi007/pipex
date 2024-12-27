# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Source directory
SRC_DIR = src

# Header directory
INC_DIR = include

# Source files
SRCS = $(SRC_DIR)/pipex.c $(SRC_DIR)/ft_execute.c $(SRC_DIR)/ft_getpath.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
NAME = pipex.out

# Header files
HEADERS = $(INC_DIR)/pipex.h

# Libft directory
LIBFT_DIR = libft

# Libft library
LIBFT = $(LIBFT_DIR)/libft.a

# Default target
all: $(LIBFT) $(NAME)

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
# Link object files to create the executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Clean object files and executable
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re