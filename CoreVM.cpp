//Here only the class body and logic is written
#include "CoreVM.hpp"
#include <iostream>
#include <iomanip>

// ---------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------
CoreVM::CoreVM() {
    for (int i = 0; i < MEM_SIZE; i++) memory[i] = 0;
    for (int i = 0; i < NUM_REGS;  i++) registers[i] = 0;

    pc = 0;
    running = true;

    std::cout << "CoreVM Initialized. Memory Range: 0x000 - 0xFFF" << std::endl;
}

// ---------------------------------------------------------------
// Safe single-byte fetch
// ---------------------------------------------------------------
bool CoreVM::fetch_byte(uint16_t addr, uint8_t& out) {
    if (addr >= MEM_SIZE) {
        std::cout << "\n!!! KERNEL PANIC !!!" << std::endl;
        std::cout << "PC operand fetch out of bounds at: 0x"
                  << std::hex << std::uppercase << addr << std::endl;
        running = false;
        return false;
    }
    out = memory[addr];
    return true;
}

// ---------------------------------------------------------------
// Register validation
// ---------------------------------------------------------------
bool CoreVM::valid_reg(uint8_t idx, const char* label) {
    if (idx >= NUM_REGS) {
        std::cout << "\n!!! KERNEL PANIC !!!" << std::endl;
        std::cout << "Invalid " << label << " register index: " << (int)idx
                  << " (valid: R0–R" << (NUM_REGS - 1) << ")" << std::endl;
        running = false;
        return false;
    }
    return true;
}

// ---------------------------------------------------------------
// Write memory
// ---------------------------------------------------------------
void CoreVM::write_memory(uint16_t address, uint8_t value) {
    if (address >= MEM_SIZE) {
        std::cout << "\n!!! KERNEL PANIC !!!" << std::endl;
        std::cout << "Memory write out of bounds at: 0x"
                  << std::hex << std::uppercase << address << std::endl;
        running = false;
    } else {
        memory[address] = value;
    }
}

// ---------------------------------------------------------------
// Dump registers
// ---------------------------------------------------------------
void CoreVM::dump_registers() const {
    std::cout << "\n--- Register Dump ---" << std::endl;
    for (int i = 0; i < NUM_REGS; i++) {
        std::cout << "  R" << i << " = " << std::dec << registers[i] << std::endl;
    }
    std::cout << "---------------------" << std::endl;
}

// ---------------------------------------------------------------
// Execution loop
// ---------------------------------------------------------------
void CoreVM::run() {
    std::cout << "\nStarting Execution..." << std::endl;

    while (running && pc < MEM_SIZE) {
        uint8_t opcode = memory[pc];

        switch (opcode) {

            case 0x01: {
                uint8_t dst, value;
                if (!fetch_byte(pc + 1, dst)) break;
                if (!valid_reg(dst, "dst"))    break;
                if (!fetch_byte(pc + 2, value)) break;

                registers[dst] = (int)value;
                std::cout << "[SET  ] R" << (int)dst << " = " << (int)value << std::endl;
                pc += 3;
                break;
            }

            case 0x02: {
                uint8_t dst, a, b;
                if (!fetch_byte(pc + 1, dst)) break;
                if (!fetch_byte(pc + 2, a))   break;
                if (!fetch_byte(pc + 3, b))   break;
                if (!valid_reg(dst, "dst"))   break;
                if (!valid_reg(a, "src_a"))   break;
                if (!valid_reg(b, "src_b"))   break;

                registers[dst] = registers[a] + registers[b];
                std::cout << "[ADD  ] R" << (int)dst
                          << " = R" << (int)a << " + R" << (int)b
                          << " => " << registers[dst] << std::endl;
                pc += 4;
                break;
            }

            case 0x03: {
                uint8_t dst, a, b;
                if (!fetch_byte(pc + 1, dst)) break;
                if (!fetch_byte(pc + 2, a))   break;
                if (!fetch_byte(pc + 3, b))   break;
                if (!valid_reg(dst, "dst"))   break;
                if (!valid_reg(a, "src_a"))   break;
                if (!valid_reg(b, "src_b"))   break;

                registers[dst] = registers[a] - registers[b];
                std::cout << "[SUB  ] R" << (int)dst
                          << " = R" << (int)a << " - R" << (int)b
                          << " => " << registers[dst] << std::endl;
                pc += 4;
                break;
            }

            case 0x04: {
                uint8_t dst, a, b;
                if (!fetch_byte(pc + 1, dst)) break;
                if (!fetch_byte(pc + 2, a))   break;
                if (!fetch_byte(pc + 3, b))   break;
                if (!valid_reg(dst, "dst"))   break;
                if (!valid_reg(a, "src_a"))   break;
                if (!valid_reg(b, "src_b"))   break;

                registers[dst] = registers[a] * registers[b];
                std::cout << "[MUL  ] R" << (int)dst
                          << " = R" << (int)a << " * R" << (int)b
                          << " => " << registers[dst] << std::endl;
                pc += 4;
                break;
            }

            case 0x05: {
                uint8_t dst, src;
                if (!fetch_byte(pc + 1, dst)) break;
                if (!fetch_byte(pc + 2, src)) break;
                if (!valid_reg(dst, "dst"))   break;
                if (!valid_reg(src, "src"))   break;

                registers[dst] = registers[src];
                std::cout << "[MOV  ] R" << (int)dst
                          << " = R" << (int)src
                          << " => " << registers[dst] << std::endl;
                pc += 3;
                break;
            }

            case 0x06: {
                uint8_t src;
                if (!fetch_byte(pc + 1, src)) break;
                if (!valid_reg(src, "src"))   break;

                std::cout << "[PRINT] R" << (int)src
                          << " => " << registers[src] << std::endl;
                pc += 2;
                break;
            }

            case 0xFF:
                std::cout << "[HALT ] System Halted." << std::endl;
                running = false;
                break;

            default:
                pc++;
                break;
        }
    }
}