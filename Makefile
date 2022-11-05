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

alu_16bit.o:
	$(CC) $(CFLAGS) -c src/cpu/alu_16bit.cpp

rotates.o:
	$(CC) $(CFLAGS) -c src/cpu/rotates.cpp

bit.o:
	$(CC) $(CFLAGS) -c src/cpu/bit.cpp

jumps.o:
	$(CC) $(CFLAGS) -c src/cpu/jumps.cpp

loads_8bit.o:
	$(CC) $(CFLAGS) -c src/cpu/loads_8bit.cpp

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

test_alu_16bit.o:
	$(CC) $(CFLAGS) -c tests/test_alu_16bit.cpp

test_rotates.o:
	$(CC) $(CFLAGS) -c tests/test_rotates.cpp

test_bit.o:
	$(CC) $(CFLAGS) -c tests/test_bit.cpp

test_jumps.o:
	$(CC) $(CFLAGS) -c tests/test_jumps.cpp

test_loads_8bit.o:
	$(CC) $(CFLAGS) -c tests/test_loads_8bit.cpp

test-registers: clean gameboy.o registers.o test_registers.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) registers.o test_registers.o gameboy.o cpu.o mmu.o gpu.o
	./$(TEST_TARGET)

test_alu_8bit: clean alu_8bit.o gameboy.o test_alu_8bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) alu_8bit.o registers.o gameboy.o cpu.o mmu.o gpu.o test_alu_8bit.o
	./$(TEST_TARGET)

test_loads_8bit: clean loads_8bit.o gameboy.o test_loads_8bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) loads_8bit.o registers.o gameboy.o cpu.o mmu.o gpu.o test_loads_8bit.o
	./$(TEST_TARGET)

test_alu_16bit: clean alu_16bit.o gameboy.o test_alu_16bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) alu_16bit.o registers.o gameboy.o cpu.o mmu.o gpu.o test_alu_16bit.o
	./$(TEST_TARGET)

test-rotates: clean rotates.o gameboy.o test_rotates.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) rotates.o registers.o gameboy.o cpu.o mmu.o gpu.o test_rotates.o
	./$(TEST_TARGET)

test-bit: clean bit.o gameboy.o test_bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) bit.o registers.o gameboy.o cpu.o mmu.o gpu.o test_bit.o
	./$(TEST_TARGET)

test-jumps: clean jumps.o gameboy.o test_jumps.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) jumps.o registers.o gameboy.o cpu.o mmu.o gpu.o test_jumps.o
	./$(TEST_TARGET)

test-all: clean test-registers test_alu_8bit test_loads_8bit test_alu_16bit rotates

clean:
	$(RM) $(TARGET) $(TEST_TARGET) *.o
