# Bakge unit tests makefile
# A generic makefile to build unit tests.
#
# Add your test to the TESTS variable to build it with make tests
#
# If your test needs to be compiled a different way make sure you mention
# it in the test source file.


TESTS=window.cpp types.cpp glfw.cpp
EXECS=$(TESTS:.cpp=)
LIBBAKGE=../lib/libbakge.a
LFLAGS=-lX11 -lXrandr -lGL -lGLU -lpthread

# First line builds libbakge in case it has changed
tests:
	@cd .. && make -s all;
	@make -s $(EXECS);

# Depend on libbakge so tests rebuild if it changed
%: %.cpp $(LIBBAKGE)
	@echo "Compiling test $@...";
	@g++ -o $@ $< -I../include -L../lib -lm -lbakge $(LFLAGS);
	@echo "  - Done";

clean:
	rm -f $(EXECS);
