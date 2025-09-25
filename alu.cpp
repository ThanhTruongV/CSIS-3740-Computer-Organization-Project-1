#include "alu.hpp"
#include <climits>
#include <cstdint>

void ALU::setZN(int16_t res, Flags &flags) {
    flags.Z = (res == 0);
    flags.N = (res < 0);
}

bool ALU::detectCarryAdd(int32_t wideResult) {
    // carry out of 16 bits if wideResult not representable in unsigned 16 bits
    return (wideResult & (~0xFFFF)) != 0;
}
bool ALU::detectCarrySub(int32_t wideResult) {
    // We can reuse same check: if result outside 16-bit unsigned range, there's borrow/carry perception
    return (wideResult & (~0xFFFF)) != 0;
}
bool ALU::detectOverflowAdd(int16_t a, int16_t b, int16_t res) {
    // signed overflow when a and b have same sign but res has different sign
    bool signA = (a < 0);
    bool signB = (b < 0);
    bool signR = (res < 0);
    return (signA == signB) && (signR != signA);
}
bool ALU::detectOverflowSub(int16_t a, int16_t b, int16_t res) {
    // a - b = res ; overflow if a and b have different signs and result sign differs from a
    bool signA = (a < 0);
    bool signB = (b < 0);
    bool signR = (res < 0);
    return (signA != signB) && (signR != signA);
}

int16_t ALU::add(int16_t a, int16_t b, Flags &flags) {
    int32_t wide = static_cast<int32_t>(static_cast<int32_t>(a)) + static_cast<int32_t>(b);
    int16_t res = static_cast<int16_t>(wide & 0xFFFF);
    setZN(res, flags);
    flags.C = detectCarryAdd(wide);
    flags.V = detectOverflowAdd(a, b, res);
    return res;
}

int16_t ALU::sub(int16_t a, int16_t b, Flags &flags) {
    int32_t wide = static_cast<int32_t>(a) - static_cast<int32_t>(b);
    int16_t res = static_cast<int16_t>(wide & 0xFFFF);
    setZN(res, flags);
    flags.C = detectCarrySub(wide); // borrow/carry logic simplified as "out of 16-bit"
    flags.V = detectOverflowSub(a, b, res);
    return res;
}

int16_t ALU::BAND(int16_t a, int16_t b, Flags &flags) {
    int16_t res = a & b;
    setZN(res, flags);
    flags.C = false;
    flags.V = false;
    return res;
}

int16_t ALU::BOR(int16_t a, int16_t b, Flags &flags) {
    int16_t res = a | b;
    setZN(res, flags);
    flags.C = false;
    flags.V = false;
    return res;
}

int16_t ALU::BXOR(int16_t a, int16_t b, Flags &flags) {
    int16_t res = a ^ b;
    setZN(res, flags);
    flags.C = false;
    flags.V = false;
    return res;
}

int16_t ALU::BNOT(int16_t a, Flags &flags) {
    int16_t res = ~a;
    setZN(res, flags);
    flags.C = false;
    flags.V = false;
    return res;
}

int16_t ALU::shl(int16_t a, unsigned int count, Flags &flags) {
    // Shift left logical: bits shifted out of left produce carry (last bit shifted out)
    if (count == 0) {
        setZN(a, flags);
        flags.C = false;
        flags.V = false;
        return a;
    }
    uint32_t ua = static_cast<uint16_t>(a);
    // Determine carry: last bit shifted out (the bit at position 16-count..)
    uint32_t shifted = (ua << count) & 0xFFFF;
    // carry true if any of the bits shifted out (bits above 15) are non-zero
    uint32_t outBits = (ua << count) & ~0xFFFFu;
    flags.C = (outBits != 0);
    int16_t res = static_cast<int16_t>(shifted);
    setZN(res, flags);
    flags.V = false; // left shift does not define signed overflow here (implementation choice)
    return res;
}

int16_t ALU::shr(int16_t a, unsigned int count, Flags &flags) {
    // Arithmetic right shift: sign bit preserved
    if (count == 0) {
        setZN(a, flags);
        flags.C = false;
        flags.V = false;
        return a;
    }
    // determine carry: last bit shifted out (LSB)
    uint32_t ua = static_cast<uint16_t>(a);
    uint32_t outBits = ua & ((1u << count) - 1);
    flags.C = (outBits != 0);

    // arithmetic shift preserve sign
    int16_t res = a >> count; // implementation-defined in C++ for negative right shift, but commonly arithmetic on two's complement; acceptable for this project
    setZN(res, flags);
    flags.V = false;
    return res;
}
