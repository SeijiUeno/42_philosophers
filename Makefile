# Set the compiler and compilation flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Define the object files
OBJS = basic_functions.o input_handler.o main.o

# Define the executable name
EXECUTABLE = philosophers

# Default target: build the executable
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)
    
# Rule to compile each source file into an object file
%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove only object files 
clean:
	rm -f *.o 

# Force clean target: remove object files and the executable
fclean: 
	rm -f *.o $(EXECUTABLE)

# Re target: clean and rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re
