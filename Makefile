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

# Default target
all: $(NAME)

# Link object files to create the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -f $(OBJS) $(NAME)

fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re