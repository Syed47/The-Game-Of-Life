CC = g++ # compiler
CFLAGS = -Wall # flag to use e.g ggdb, -Wall etc
LDFLAGS = # libraries to use e.g -lm, -lefence
# object files to include in the program
OBJFILES = Board.o Simulation.o main.o
TARGET = run # executable file name

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

run:
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) && ./$(TARGET)
