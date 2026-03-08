# CoreVM Memory Layout

CoreVM uses a simple contiguous memory array.

## Memory

- **Size:** 0x000 - 0xFFF (4096 bytes)
- **Type:** uint8_t memory[4096]

## Memory Regions

| Address Range | Purpose                     |
|---------------|----------------------------|
| 0x000 - 0x0FF | Reserved for system use    |
| 0x100 - 0x7FF | Program instructions       |
| 0x800 - 0xFFF | Stack / runtime variables  |

## Access Rules

- All reads/writes are checked against valid memory ranges.
- Invalid access triggers a safe halt with error logging.
- Registers can only hold 8-bit values (0-255).

## Example

memory[0x100] = 0x01 ; opcode for SET
memory[0x101] = 0x00 ; R0
memory[0x102] = 0x05 ; immediate value 5
