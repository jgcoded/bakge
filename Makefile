# Bakge makefile

CWD=$(shell pwd)
SRCDIR=$(CWD)/src
OBJDIR=$(CWD)/obj
INCDIR=$(CWD)/include
LIBDIR=$(CWD)/lib
TESTDIR=$(CWD)/test

MODULES=core
SOURCES=$(foreach mod, $(MODULES), $(wildcard src/$(mod)/*.cpp))
OBJECTS=$(SOURCES:.cpp=.o)

# Path of the static library
LIBBAKGE=$(LIBDIR)/libbakge.a

# Other object files to build our static library
GLFW=$(LIBDIR)/glfw-2.7.9
GLFWOBJ=$(wildcard $(LIBDIR)/glfw-2.7.9/lib/x11/*.o)
LIBOBJ=$(GLFWOBJ)

# Compilation flags
CFLAGS=-I$(CWD)/include -I$(LIBDIR)/glfw-2.7.9/include

help:
	@echo "";
	@echo "Bakge build targets";
	@echo "===================";
	@echo " - all: Build Bakge";
	@echo " - suite: Build Bakge and associated tests";
	@echo " - clean: Clean all Bakge engine generated files";
	@echo " - purge: Clean all libs, tests and engine generated files.";
	@echo "";

all:
	@mkdir -p $(OBJDIR)/src;
	@cd $(OBJDIR)/src && mkdir -p $(MODULES);
	@make -s $(LIBBAKGE);

suite:
	@make -s all;
	@cd $(TESTDIR) && make -s;

$(LIBBAKGE): $(patsubst %, $(OBJDIR)/%, $(OBJECTS))
	@echo "Linking $@...";
	@ar rcs $@ $^ $(LIBOBJ);
	@echo "  - Done";

$(OBJDIR)/%.o: %.cpp $(INCDIR)/bakge/Bakge.h $(GLFW)
	@echo "Compiling $@...";
	@g++ -o $@ -c $< $(CFLAGS);
	@echo "  - Done";

clean:
	rm -f $(LIBBAKGE);
	rm -rf $(OBJDIR)/src;

purge:
	@make -s clean;
	@cd $(LIBDIR) && make -s clean;
	@cd $(TESTDIR) && make -s clean;

$(GLFW):
	@cd $(LIBDIR) && make -s;
