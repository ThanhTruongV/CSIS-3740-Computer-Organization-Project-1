#ifndef ALU_HPP
#define ALU_HPP

#include <cstdint>

struct Flags {
    bool Z; // Zero
    bool N; // Negative (sign)
    bool C; // Carry
    bool V; // Overflow
    Flags(): Z(false), N(false), C(false), V(false) {}
};

class ALU {
public:
    // arithmetic
    int16_t add(int16_t a, int16_t b, Flags &flags);
    int16_t sub(int16_t a, int16_t b, Flags &flags);

    // bitwise
    int16_t BAND(int16_t a, int16_t b, Flags &flags);
    int16_t BOR(int16_t a, int16_t b, Flags &flags);
    int16_t BXOR(int16_t a, int16_t b, Flags &flags);
    int16_t BNOT(int16_t a, Flags &flags);

    // shifts (logical/arithmetical)
    // here we implement logical left (same as arithmetic left) and arithmetic right (preserve sign)
    int16_t shl(int16_t a, unsigned int count, Flags &flags); // shift left (logical)
    int16_t shr(int16_t a, unsigned int count, Flags &flags); // arithmetic right shift (preserve sign)

private:
    void setZN(int16_t res, Flags &flags);
    // detect carry and overflow for add/sub
    bool detectCarryAdd(int32_t wideResult);
    bool detectCarrySub(int32_t wideResult);
    bool detectOverflowAdd(int16_t a, int16_t b, int16_t res);
    bool detectOverflowSub(int16_t a, int16_t b, int16_t res);
};

#endif // ALU_HPP
