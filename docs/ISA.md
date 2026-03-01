# CoreVM Instruction Set Architecture (ISA)

Memory Size: 0x000 - 0xFFF (4096 bytes)
Registers: R0 - R3 (4 registers)
PC: Program Counter (16-bit)

----------------------------------------
0x01 SET dst, imm
Bytes: [opcode][dst][imm]
Total: 3 bytes
Description:
    Set register dst to immediate value imm

----------------------------------------
0x02 ADD dst, rA, rB
Bytes: [opcode][dst][rA][rB]
Total: 4 bytes
Description:
    dst = rA + rB

----------------------------------------
0x03 SUB dst, rA, rB
Bytes: 4 bytes
Description:
    dst = rA - rB

----------------------------------------
0x04 MUL dst, rA, rB
Bytes: 4 bytes
Description:
    dst = rA * rB

----------------------------------------
0x05 MOV dst, src
Bytes: 3 bytes
Description:
    Copy value from src to dst

----------------------------------------
0x06 PRINT src
Bytes: 2 bytes
Description:
    Print register value

----------------------------------------
0xFF HALT
Bytes: 1 byte
Description:
    Stop execution
