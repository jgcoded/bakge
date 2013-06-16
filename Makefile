# Convenience makefile

TARGET=build

OPTIONS=-DGLFW_USE_EGL=OFF -DGLFW_BUILD_UNIVERSAL=ON -DGLFW_BUILD_EXAMPLES=ON -DGLFW_BUILD_TESTS=OFF

all:
	@mkdir $(TARGET) && cd $(TARGET) && cmake .. -G "Unix Makefiles" $(OPTIONS) && make -s;

clean:
	rm -rf $(TARGET);

