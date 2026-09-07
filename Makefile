CC = clang
CFLAGS = -Wall -Wextra
TARGET = lordfetch

all: $(TARGET)

$(TARGET): src/main.c
	$(CC) $(CFLAGS) src/main.c  src/asciis.c src/info.c -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
