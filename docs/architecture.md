# CoreVM Architecture

**Description:**  
This document explains the internal architecture of CoreVM, including its CPU, registers, and execution cycle. It’s meant to give a developer or reviewer a clear understanding of how the virtual machine works.

## CPU

Registers:
- **R0 - R3**: General-purpose 8-bit registers
- **PC**: 16-bit Program Counter

## Execution Cycle

1. **Fetch**: Read the instruction at the address pointed by PC.
2. **Decode**: Determine the opcode and operands.
3. **Execute**: Perform the instruction logic.
4. **Update PC**: Move to the next instruction.

### Example Cycle
PC = 0x0000
Instruction = 0x01 0x00 0x05 ; SET R0, 5
R0 = 5
PC += 3

## Debugger

- CLI-based, allows stepping through instructions.
- Prints current PC, register values, and memory regions.
- Halts on invalid memory access or unrecognized opcode.
