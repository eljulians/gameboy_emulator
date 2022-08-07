CC = clang++
CFLAGS = -std=c++20 -g -Wall
TARGET = gameboy_emulator
TEST_TARGET = gameboy_emulator_test


all: $(TARGET)

$(TARGET): clean
	$(CC) $(CFLAGS) -c src/*.cpp
	$(CC) $(CFLAGS) -o $(TARGET) *.o

registers.o:
	$(CC) $(CFLAGS) -c src/cpu/registers.cpp

test_registers.o:
	$(CC) $(CFLAGS) -c tests/test_registers.cpp

alu_8bit.o:
	$(CC) $(CFLAGS) -c src/cpu/alu_8bit.cpp

test_alu_8bit.o:
	$(CC) $(CFLAGS) -c tests/test_alu_8bit.cpp

test-registers: registers.o test_registers.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) registers.o test_registers.o
	./$(TEST_TARGET)

test_alu_8bit: alu_8bit.o test_alu_8bit.o registers.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) alu_8bit.o test_alu_8bit.o registers.o
	./$(TEST_TARGET)

test-all: clean test-registers

clean:
	$(RM) $(TARGET) $(TEST_TARGET) *.o
