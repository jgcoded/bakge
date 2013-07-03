# Convenience makefile

DEBUG?=ON
TARGET=build
SDK=sdk

BUILD_DYNAMIC?=OFF
BUILD_TESTS?=ON
BUILD_EXAMPLES?=ON

GLFW_OPTIONS=-DGLFW_USE_EGL=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF

BAKGE_OPTIONS=-DBAKGE_SDK_PATH=$(SDK) -DBAKGE_BUILD_TESTS=$(BUILD_TESTS) -DBAKGE_BUILD_EXAMPLES=$(BUILD_EXAMPLES) -DBUILD_SHARED_LIBS=$(BUILD_DYNAMIC)

# All options
OPTIONS=$(GLFW_OPTIONS) $(BAKGE_OPTIONS)

help:
	@echo ""
	@echo "Bakge Makefile targets"
	@echo "======================"
	@echo " - Debug: Build a debug configuration"
	@echo " - Release: Build a release configuration"
	@echo ""

Debug:
	@mkdir -p $(TARGET) && cd $(TARGET) && cmake .. -G "Unix Makefiles" $(OPTIONS) -DCMAKE_BUILD_TYPE=Debug && make -s;

Release:
	@mkdir -p $(TARGET) && cd $(TARGET) && cmake .. -G "Unix Makefiles" $(OPTIONS) -DCMAKE_BUILD_TYPE=Release && make -s;

codeblocks:
	@mkdir -p $(TARGET) && cd $(TARGET) && cmake .. -G "CodeBlocks - Unix Makefiles" $(OPTIONS);

clean:
	rm -rf $(TARGET) $(SDK);

