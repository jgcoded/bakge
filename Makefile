# Convenience makefile

TARGET=build

all:
	@mkdir $(TARGET) && cd $(TARGET) && cmake .. -G "Unix Makefiles" && make;

clean:
	rm -rf $(TARGET);

