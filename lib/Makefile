# Bakge libs makefile
#
# Downloads and builds required libraries locally


GLFWURL=http://sourceforge.net/projects/glfw/files/glfw/2.7.9/glfw-2.7.9.zip/download?use_mirror=autoselect

libs: glfw-2.7.9
	@make build;

build:
	cd glfw-2.7.9 && make x11;


glfw-2.7.9:
	@echo "Downloading $@...";
	@wget $(GLFWURL) -O $@.zip 2> /dev/null;
	@echo "  - Done";
	@echo "Unzipping $@...";
	@unzip glfw-2.7.9.zip;
	@rm glfw-2.7.9.zip;
	@echo "  - Done";

clean:
	rm -rf glfw-2.7.9;
