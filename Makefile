# Convenience makefile

TARGET=build

all:
	@mkdir $(TARGET) && cd $(TARGET) && cmake .. -G "Unix Makefiles" && make -s;

clean:
	rm -rf $(TARGET);
	rm -rf bin;

