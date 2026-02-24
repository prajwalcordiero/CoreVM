//This file should contain only the blueprint/interface.Add only class names and members in this.
// Dont write the logic here
#ifndef COREVM_HPP
#define COREVM_HPP

#include <cstdint>

class CoreVM {
private:
    static const int MEM_SIZE = 0x1000;
    static const int NUM_REGS = 4;

    uint8_t  memory[MEM_SIZE];
    int      registers[NUM_REGS];
    uint16_t pc;
    bool     running;

    // Helper functions (declarations only)
    bool fetch_byte(uint16_t addr, uint8_t& out);
    bool valid_reg(uint8_t idx, const char* label);

public:
    // Constructor
    CoreVM();

    // Public interface
    void write_memory(uint16_t address, uint8_t value);
    void dump_registers() const;
    void run();
};

#endif