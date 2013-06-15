# Convenience makefile

TARGET=build

OPTIONS=-DGLFW_BUILD_UNIVERSAL=OFF -DGLFW_USE_MENUBAR=ON -DGLFW_BUILD_EXAMPLES=ON -DGLFW_BUILD_TESTS=OFF

all:
	@mkdir $(TARGET) && cd $(TARGET) && cmake .. -G "Unix Makefiles" $(OPTIONS) && make -s;

clean:
	rm -rf $(TARGET);

