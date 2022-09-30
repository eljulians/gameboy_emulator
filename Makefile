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

cpu.o: registers.o
	$(CC) $(CFLAGS) -c src/cpu/cpu.cpp

gpu.o:
	$(CC) $(CFLAGS) -c src/gpu/gpu.cpp

mmu.o:
	$(CC) $(CFLAGS) -c src/mmu/mmu.cpp

gameboy.o: cpu.o gpu.o mmu.o
	$(CC) $(CFLAGS) -c src/gameboy.cpp

test_alu_8bit.o:
	$(CC) $(CFLAGS) -c tests/test_alu_8bit.cpp

test-registers: clean gameboy.o registers.o test_registers.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) registers.o test_registers.o gameboy.o cpu.o mmu.o gpu.o
	./$(TEST_TARGET)

test_alu_8bit: clean alu_8bit.o gameboy.o test_alu_8bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) alu_8bit.o registers.o gameboy.o cpu.o mmu.o gpu.o test_alu_8bit.o
	./$(TEST_TARGET)

test-all: clean test-registers test_alu_8bit

clean:
	$(RM) $(TARGET) $(TEST_TARGET) *.o
