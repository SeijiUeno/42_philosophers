# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread

# Executable name
EXECUTABLE = philosophers

# Object directory
OBJDIR = obj

# Source files
SRCS = basic_functions.c input_utils.c init.c philosopher.c main.c

# Object files (in OBJDIR)
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Default target: build the executable
all: $(OBJDIR) $(EXECUTABLE)

# Ensure the object directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to build the executable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE) $(LDFLAGS)
    
# Rule to compile each source file into an object file in $(OBJDIR)
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove only object files
clean:
	rm -f $(OBJDIR)/*.o

# Force clean target: remove object files, the executable, and the obj directory
fclean: clean
	rm -f $(EXECUTABLE)
	rm -rf $(OBJDIR)

# Re target: clean and rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re
