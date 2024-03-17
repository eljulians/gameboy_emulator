#pragma once

#include <string>
#include <stdint.h>
#include <vector>

#define ROM_ONLY_SIZE 0x8000
#define MBC1_SIZE 0x0

#define CARTRIDGE_TYPE_HEADER 0x147
#define ROM_SIZE_ADDRESS 0x148
#define RAM_SIZE_ADDRESS 0x149


typedef std::vector<uint8_t> memory_t;
typedef std::vector<memory_t> memory_bank_t;


class AbstractCartridge {
    protected:
        memory_t rom;
        memory_t ram;
        memory_bank_t romBanks;
        memory_bank_t ramBanks;
        int romSize;
        int ramSize;
        int romBankCount;
        int ramBankCount;

        virtual int getRomBankIndex(uint8_t address) = 0;
        virtual int getRamBankIndex(uint8_t address) = 0;

    public:
        AbstractCartridge(memory_t rom, int romSize, int ramSize) :
            rom(rom),
            romSize(romSize),
            ramSize(ramSize)
        {
            romBankCount = (int)romSize/16;
            ramBankCount = (int)ramSize/8;
            romBanks = memory_bank_t(romBankCount);
            ramBanks = memory_bank_t(ramBankCount);
        };
        uint8_t read(uint16_t address);
        void write(uint16_t adress, uint8_t value);
};


class CartridgeROMOnly : public AbstractCartridge {
    protected:
        int getRomBankIndex(uint8_t address);
        int getRamBankIndex(uint8_t address);

    public:
        using AbstractCartridge::AbstractCartridge;

        /*
        uint8_t read(uint16_t address);
        void write(uint16_t adress, uint8_t value);
        */
};


class CartridgeMBC1 : public AbstractCartridge {
    protected:
        int getRomBankIndex(uint8_t address);
        int getRamBankIndex(uint8_t address);

    public:
        using AbstractCartridge::AbstractCartridge;

        /*
        uint8_t read(uint16_t address);
        void write(uint16_t adress, uint8_t value);
        */
};


AbstractCartridge* createCartridge(std::string romPath);