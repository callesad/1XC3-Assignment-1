# Compiler to use
CC = gcc 

# Compilation flags for warnings
CFLAGS = -Wall -Wextra -std=c11  

# Object files to be compiled
OBJ = test.o myAO.o utility.o  

# Default target to compile the executable
all: myAO

# Link object files into the executable
myAO: $(OBJ)
	$(CC) $(CFLAGS) -o myAO $(OBJ)

# Compile C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the files and executable
clean:
	rm -f *.o myAO
