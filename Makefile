# Convenience makefile

DEBUG?=ON
TARGET=build
SDK=sdk

GLFW_OPTIONS=-DGLFW_USE_EGL=OFF -DGLFW_BUILD_UNIVERSAL=ON -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF

BAKGE_OPTIONS=-DDEBUG_BUILD=$(DEBUG) -DBAKGE_SDK_PATH=$(SDK)

# All options
OPTIONS=$(GLFW_OPTIONS) $(BAKGE_OPTIONS)

all:
	@mkdir $(TARGET) && cd $(TARGET) && cmake .. -G "Unix Makefiles" $(OPTIONS) && make -s;

codeblocks:
	@mkdir $(TARGET) && cd $(TARGET) && cmake .. -G "Unix Makefiles" $(OPTIONS);

clean:
	rm -rf $(TARGET) $(SDK);

