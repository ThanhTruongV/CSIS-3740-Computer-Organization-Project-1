#include <iostream>
#include <cassert>
#include "converters.hpp"

int main() {
    std::cout << "Running converter tests...\n";

    // edge cases focusing on 16-bit:
    int16_t v0 = 0;
    int16_t vneg1 = -1;
    int16_t vmax = 32767; // INT16_MAX
    int16_t vmin = -32768; // INT16_MIN

    std::cout << "0 -> bin: " << decToBin(v0) << " hex: " << decToHex(v0) << "\n";
    assert(decToBin(v0) == "0000000000000000");
    assert(decToHex(v0) == "0x0000");
    assert(binToDec("0000000000000000") == 0);

    std::cout << "-1 -> bin: " << decToBin(vneg1) << " hex: " << decToHex(vneg1) << "\n";
    assert(decToBin(vneg1) == "1111111111111111");
    assert(decToHex(vneg1) == "0xFFFF");
    assert(binToDec("1111111111111111") == -1);

    std::cout << "32767 -> bin: " << decToBin(vmax) << " hex: " << decToHex(vmax) << "\n";
    assert(decToBin(vmax) == "0111111111111111");
    assert(decToHex(vmax) == "0x7FFF");

    std::cout << "-32768 -> bin: " << decToBin(vmin) << " hex: " << decToHex(vmin) << "\n";
    assert(decToBin(vmin) == "1000000000000000");
    assert(decToHex(vmin) == "0x8000");

    // hex parsing
    assert(hexToDec("0x7FFF") == 32767);
    assert(hexToDec("FFFF") == -1);

    // bin parsing
    assert(binToDec("0b0111111111111111") == 32767);
    assert(binToDec("1111111111111111") == -1);

    std::cout << "All converter tests passed.\n";
    return 0;
}
