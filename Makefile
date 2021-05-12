#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = clang
CFLAGS  = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -lm

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: filter

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
filter:  filter.o helpers.o
	$(CC) $(CFLAGS) -o filter filter.o helpers.o

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
filter.o:  filter.c helpers.h 
	$(CC) $(CFLAGS) -c filter.c

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
helpers.o:  helpers.c helpers.h 
	$(CC) $(CFLAGS) -c helpers.c

# To create the object file scanner.o, we need the source files
# scanner.c and scanner.h:
#
# scanner.o:  scanner.c scanner.h s
# 	$(CC) $(CFLAGS) -c scanner.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) filter *.o *~
	$(RM) filter
