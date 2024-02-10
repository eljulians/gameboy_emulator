CC = clang++
CFLAGS = -std=c++20 -g -Wall -Llibraries/ -lSDL2
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

timer.o:
	$(CC) $(CFLAGS) -c src/cpu/timer/timer.cpp

test_timer.o:
	$(CC) $(CFLAGS) -c tests/cpu/timer/test_timer.cpp

test_timer: clean test_timer.o timer.o gameboy.o loads_8bit.o jumps.o bit.o rotates.o alu_16bit.o alu_8bit.o registers.o cartridge.o control_unit.o misc_control.o interrupt_manager.o interrupt.o cpu.o mmu.o gpu.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) test_timer.o timer.o gameboy.o loads_8bit.o jumps.o bit.o rotates.o alu_16bit.o alu_8bit.o registers.o cartridge.o control_unit.o misc_control.o interrupt_manager.o interrupt.o cpu.o mmu.o gpu.o
	./$(TEST_TARGET)


control_unit.o:
	$(CC) $(CFLAGS) -c src/cpu/control_unit.cpp

misc_control.o:
	$(CC) $(CFLAGS) -c src/cpu/misc_control.cpp

gameboy.o: cpu.o gpu.o mmu.o cartridge.o control_unit.o
	$(CC) $(CFLAGS) -c src/gameboy.cpp

cartridge.o:
	$(CC) $(CFLAGS) -c src/mmu/cartridge.cpp

tile.o:
	$(CC) $(CFLAGS) -c src/gpu/tile.cpp

interrupt.o: gameboy.o
	$(CC) $(CFLAGS) -c src/interrupts/interrupt.cpp

interrupt_manager.o: interrupt.o
	$(CC) $(CFLAGS) -c src/interrupts/interrupt_manager.cpp

#gameboy: clean gameboy.o loads_8bit.o jumps.o bit.o rotates.o alu_16bit.o alu_8bit.o registers.o cartridge.o
	#$(CC) $(CFLAGS) -o $(TARGET) gameboy.o cpu.o gpu.o mmu.o loads_8bit.o jumps.o bit.o rotates.o alu_16bit.o alu_8bit.o registers.o cartridge.o

bit_operations.o:
	$(CC) $(CFLAGS) -c src/common/bit_operations.cpp


gameboy_main.o: gameboy.o
	$(CC) $(CFLAGS) -c src/gameboy_main.cpp

gameboy_emulator: clean gameboy_main.o gameboy.o loads_8bit.o jumps.o bit.o rotates.o alu_16bit.o alu_8bit.o registers.o cartridge.o control_unit.o misc_control.o interrupt_manager.o interrupt.o
	$(CC) $(CFLAGS) -o $(TARGET) gameboy_main.o gameboy.o cpu.o gpu.o mmu.o loads_8bit.o jumps.o bit.o rotates.o alu_16bit.o alu_8bit.o registers.o cartridge.o control_unit.o misc_control.o interrupt_manager.o interrupt.o

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

test_cpu.o:
	$(CC) $(CFLAGS) -c tests/test_cpu.cpp

test_interrupt.o:
	$(CC) $(CFLAGS) -c tests/test_interrupt.cpp

test-registers: clean gameboy.o registers.o test_registers.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o jumps.o bit.o rotates.o loads_8bit.o misc_control.o interrupt_manager.o interrupt.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) registers.o test_registers.o gameboy.o cpu.o mmu.o gpu.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o jumps.o bit.o rotates.o loads_8bit.o misc_control.o interrupt_manager.o interrupt.o
	./$(TEST_TARGET)

test_alu_8bit: clean alu_8bit.o gameboy.o test_alu_8bit.o cartridge.o control_unit.o alu_16bit.o jumps.o bit.o rotates.o loads_8bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) alu_8bit.o registers.o gameboy.o cpu.o mmu.o gpu.o  cartridge.o control_unit.o alu_16bit.o jumps.o bit.o rotates.o loads_8bit.o test_alu_8bit.o
	./$(TEST_TARGET)

test_loads_8bit: clean loads_8bit.o gameboy.o test_loads_8bit.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o jumps.o bit.o rotates.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) loads_8bit.o registers.o gameboy.o cpu.o mmu.o gpu.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o jumps.o bit.o rotates.o test_loads_8bit.o
	./$(TEST_TARGET)

test_alu_16bit: clean alu_16bit.o gameboy.o test_alu_16bit.o cartridge.o control_unit.o alu_8bit.o jumps.o bit.o rotates.o loads_8bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) alu_16bit.o registers.o gameboy.o cpu.o mmu.o gpu.o test_alu_16bit.o cartridge.o control_unit.o alu_8bit.o jumps.o bit.o rotates.o loads_8bit.o
	./$(TEST_TARGET)

test-rotates: clean rotates.o gameboy.o test_rotates.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o jumps.o bit.o loads_8bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) rotates.o registers.o gameboy.o cpu.o mmu.o gpu.o test_rotates.o control_unit.o alu_8bit.o alu_16bit.o jumps.o bit.o loads_8bit.o cartridge.o
	./$(TEST_TARGET)

test-bit: clean bit.o gameboy.o test_bit.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o jumps.o loads_8bit.o rotates.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) bit.o registers.o gameboy.o cpu.o mmu.o gpu.o test_bit.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o jumps.o loads_8bit.o rotates.o
	./$(TEST_TARGET)

test-jumps: clean jumps.o gameboy.o test_jumps.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o bit.o loads_8bit.o rotates.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) jumps.o registers.o gameboy.o cpu.o mmu.o gpu.o test_jumps.o cartridge.o control_unit.o alu_8bit.o alu_16bit.o bit.o loads_8bit.o rotates.o
	./$(TEST_TARGET)

test-cpu: clean gameboy.o cpu.o mmu.o test_cpu.o registers.o loads_8bit.o jumps.o bit.o rotates.o alu_8bit.o alu_16bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) gameboy.o registers.o cpu.o mmu.o gpu.o test_cpu.o cartridge.o control_unit.o loads_8bit.o jumps.o bit.o rotates.o alu_8bit.o alu_16bit.o
	./$(TEST_TARGET)

test-interrupt: clean interrupt.o test_interrupt.o gameboy.o cpu.o mmu.o registers.o loads_8bit.o jumps.o bit.o rotates.o alu_8bit.o alu_16bit.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) gameboy.o interrupt.o registers.o cpu.o mmu.o gpu.o test_interrupt.o cartridge.o control_unit.o loads_8bit.o jumps.o bit.o rotates.o alu_8bit.o alu_16bit.o
	./$(TEST_TARGET)

test-tile.o:
	$(CC) $(CFLAGS) -c tests/gpu/test_tile.cpp

test-tile: clean test-tile.o tile.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) tile.o test_tile.o
	./$(TEST_TARGET)

test_bit_operations.o: bit_operations.o
	$(CC) $(CFLAGS) -c tests/common/test_bit_operations.cpp
test_bit_operations: clean bit_operations.o test_bit_operations.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) bit_operations.o test_bit_operations.o
	./$(TEST_TARGET)



test-all: clean test-registers test_alu_8bit test_loads_8bit test_alu_16bit test-rotates test-jumps test-interrupt

clean:
	$(RM) $(TARGET) $(TEST_TARGET) *.o
