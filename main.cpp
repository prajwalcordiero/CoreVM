//This is the main file.Only functions defined in the header files will be called here
#include "corevm.hpp"
#include <initializer_list>
#include <cstdint>

// ===================================================================
// Utility: write a multi-byte instruction into VM memory
// ===================================================================
static uint16_t emit(CoreVM& vm, uint16_t base,
                     std::initializer_list<uint8_t> bytes) {
    for (uint8_t b : bytes) {
        vm.write_memory(base++, b);
    }
    return base;
}

// ===================================================================
// main – demonstration program
// ===================================================================
int main() {
    CoreVM vm;

    uint16_t addr = 0x00;

    // SET R0 = 12
    addr = emit(vm, addr, {0x01, 0x00, 12});

    // SET R1 = 8
    addr = emit(vm, addr, {0x01, 0x01, 8});

    // ADD R2 = R0 + R1   (12 + 8 = 20)
    addr = emit(vm, addr, {0x02, 0x02, 0x00, 0x01});

    // SUB R3 = R0 - R1   (12 - 8 = 4)
    addr = emit(vm, addr, {0x03, 0x03, 0x00, 0x01});

    // MUL R0 = R2 * R3   (20 * 4 = 80)
    addr = emit(vm, addr, {0x04, 0x00, 0x02, 0x03});

    // MOV R1 = R2
    addr = emit(vm, addr, {0x05, 0x01, 0x02});

    // PRINT R0, R1, R2, R3
    addr = emit(vm, addr, {0x06, 0x00});
    addr = emit(vm, addr, {0x06, 0x01});
    addr = emit(vm, addr, {0x06, 0x02});
    addr = emit(vm, addr, {0x06, 0x03});

    // HALT
    emit(vm, addr, {0xFF});

    // Run the virtual machine
    vm.run();

    // Inspect final state
    vm.dump_registers();

    return 0;
}