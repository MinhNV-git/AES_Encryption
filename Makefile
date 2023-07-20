CC = gcc
CFLAGS  = -g -Wall
COMPONENT = *.c
FOLDER = *
TARGET = run
all:
	$(CC) $(CFLAGS) $(COMPONENT) $(FOLDER)/$(COMPONENT) -o $(TARGET)

clean:
	del /f /q *.o *.exe