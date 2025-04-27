# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
#
# @author Javier Gómez Alayón
# @date 8 Jun 2020
# @brief A Makefile
# 
# @see https://www.gnu.org/software/make/
# @see http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CXX = g++						# The C++ compiler command
CXXFLAGS = -std=c++17 -O0 -g -Wall	  # The C++ compiler options (preserve debug symbols and No optimization)
LDFLAGS =						# The linker options (if any)
OBJS = *.cc
PROGRAM = ramificación_y_poda
PARAM = 

# Se busca todos los .cc del directorio src/ 
INSTRUCCION_SRCS = $(shell find src/ -name '*.cc')

# List all source files
CC = $(INSTRUCCION_SRCS)

# The all target builds all of the programs handled by the makefile.
# This target has the dependency chain:
#     all -> hello -> hello.o -> hello.cc
main: $(CC)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $^ $(LDFLAGS)


all: file_append
programa: $(CC)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $^ $(LDFLAGS)

test: $(CC)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $^ $(LDFLAGS)
	clear
	./$(PROGRAM) $(PARAM) 1

# Indicate that the all and clean targets do not
# correspond to actual files.
.PHONY: all clean

# The following rule is effectively built into make and
# therefore need not be explicitly specified:
# hello_world.o: hello_world.cc
#
	$(CXX) $(CXXFLAGS) -c $<

# The clean target removes all of the executable files
# and object files produced by the build process
# We can use it for additional housekeeping purposes


clean :
	rm -f *.o
	rm -rf *~ basura* b i
	rm -rf a.out 
	rm -drf programad/ 
	rm  -f $(PROGRAM)
	rm  -f fileout.txt
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;

cleanall :
	rm -f *.o
	rm -rf *~ basura* b i
	rm -rf a.out 
	rm -drf programa programad/ programa.tar.gz programa.cc
	find . -name '*~' -exec rm {} \;

git:
	git add . 
	git commit -m "Another example" 
	git push

tarall:
	tar cvfz directorio_comprimido.tar.gz ./