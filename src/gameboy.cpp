#include "gameboy.hpp"
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"

GameBoy::GameBoy() : 
    cpu(*this),
    gpu(*this),
    mmu(*this)
{
}