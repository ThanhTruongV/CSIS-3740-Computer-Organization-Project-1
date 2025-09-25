#include <iostream>
#include <cassert>
#include "alu.hpp"
#include "converters.hpp"

int main() {
    std::cout << "Running ALU tests...\n";

    ALU alu;
    Flags f;

    int16_t a = 32767; // INT16_MAX
    int16_t b = 1;
    int16_t r = alu.add(a,b,f);
    std::cout << "32767 + 1 = " << static_cast<int>(r) << " bin: " << decToBin(r) << " flags: "
              << f.Z << f.N << f.C << f.V << "\n";
    // signed overflow expected, result wraps to -32768
    assert(r == static_cast<int16_t>(-32768));
    assert(f.V == true);

    // subtraction overflow
    a = -32768;
    b = 1;
    r = alu.sub(a,b,f);
    std::cout << "-32768 - 1 = " << static_cast<int>(r) << " bin: " << decToBin(r) << " flags: "
              << f.Z << f.N << f.C << f.V << "\n";
    assert(r == static_cast<int16_t>(32767));
    assert(f.V == true);

    // zero test
    a = 5;
    b = 5;
    r = alu.sub(a,b,f);
    assert(r == 0);
    assert(f.Z == true);

    // bitwise NOT of -1 -> 0
    a = -1;
    r = alu.BNOT(a,f);
    assert(r == 0);
    assert(f.Z == true);

    std::cout << "All ALU tests passed.\n";
    return 0;
}
