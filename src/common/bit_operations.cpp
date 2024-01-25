#include "bit_operations.hpp"

bool testBit(int byte, int bit) {
    return byte & (1 << bit);
}