# Bakge libs makefile
#
# Downloads and builds required libraries locally


GLFWURL=http://sourceforge.net/projects/glfw/files/glfw/2.7.9/glfw-2.7.9.zip/download?use_mirror=autoselect

libs: glfw-2.7.9
	@make build;

build:
	cd glfw-2.7.9 && make x11;


glfw-2.7.9:
	@echo "Downloading GLFW 2.7.9...";
	@wget $(GLFWURL) -O $@.zip;
	@unzip glfw-2.7.9.zip;
	@rm glfw-2.7.9.zip;



