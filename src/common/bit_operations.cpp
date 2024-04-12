#include "bit_operations.hpp"

bool testBit(int byte, int bit) {
    return byte & (1 << bit);
}

uint8_t setBit(uint8_t byte, int bit) {
    return byte | (1 << bit);
}