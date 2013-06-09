# Bakge makefile

CWD=$(shell pwd)
SRCDIR=$(CWD)/src
OBJDIR=$(CWD)/obj
INCDIR=$(CWD)/include
LIBDIR=$(CWD)/lib

MODULES=core
SOURCES=$(foreach mod, $(MODULES), $(wildcard src/$(mod)/*.cpp))
OBJECTS=$(SOURCES:.cpp=.o)

LIBBAKGE=$(LIBDIR)/libbakge.a

help:
	@echo "";
	@echo "Bakge build targets";
	@echo "===================";
	@echo " - all: Build Bakge";
	@echo " - clean: Clean all Bakge generated files";
	@echo "";

all:
	@mkdir -p $(OBJDIR)/src;
	@cd $(OBJDIR)/src && mkdir -p $(MODULES);
	@make -s $(LIBBAKGE);


$(LIBBAKGE): $(patsubst %, $(OBJDIR)/%, $(OBJECTS))
	@echo "Linking $@...";
	@ar rcs $@ $^;
	@echo "  - Done";

$(OBJDIR)/%.o: %.cpp $(INCDIR)/bakge/Bakge.h
	@echo "Compiling $@...";
	@g++ -I$(INCDIR) -o $@ -c $<;
	@echo "  - Done";

clean:
	@rm -f $(LIBBAKGE);
	@rm -rf $(OBJDIR)/src;
