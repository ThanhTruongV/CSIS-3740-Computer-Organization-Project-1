# REPORT — Data Representation & 16-bit ALU

## Two's Complement (16-bit)
- Range: -32768 .. 32767
- Positive numbers: binary same as unsigned (leading 0 in MSB)
- Negative numbers: two's complement representation = invert bits of absolute value then add 1.
  Example: -1 -> invert(000...001) = 111...110 -> +1 = 111...111
- INT16_MAX = 32767 -> 0x7FFF -> 0111 1111 1111 1111
- INT16_MIN = -32768 -> 0x8000 -> 1000 0000 0000 0000

## ALU Flags
- Z (Zero): set when result == 0.
- N (Negative): set when result's sign bit (MSB) == 1.
- C (Carry): for addition/subtraction we set when result does not fit in 16 bits (unsigned carry/borrow). For shifts, set if bits are shifted out.
- V (Overflow): signed overflow. For addition: when operands had same sign but result has different sign. For subtraction: when operands had different signs and result sign differs from minuend.

## Example outputs (edge cases)
- 0 -> bin 0000000000000000, hex 0x0000
- -1 -> bin 1111111111111111, hex 0xFFFF
- 32767 -> bin 0111111111111111, hex 0x7FFF
- -32768 -> bin 1000000000000000, hex 0x8000

## Tests
Included `tests/test_converters.cpp` and `tests/test_alu.cpp`.
Run `make run_tests` to execute both tests.

## Notes / Limitations
- Right-shift uses implementation's arithmetic right-shift for negative values (typical two's complement compilers preserve sign).
- Carry semantics for subtraction implemented as "out-of-16-bit" detection; for teaching project this is sufficient and explained in report.

