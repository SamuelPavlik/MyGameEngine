#include "Bitmask.hpp"

Bitmask::Bitmask() : bits(0) {}

void Bitmask::SetMask(const Bitmask& other) {
    bits = other.GetMask();
}

uint32_t Bitmask::GetMask() const {
    return bits;
}

bool Bitmask::GetBit(size_t pos) const {
    return (bits & (1 << pos)) != 0;
}

void Bitmask::SetBit(size_t pos, bool on) {
    if (on) {
        SetBit(pos);
    }
    else {
        ClearBit(pos);
    }
}

void Bitmask::SetBit(size_t pos) {
    bits = bits | 1 << pos;
}

void Bitmask::ClearBit(size_t pos) {
    bits = bits & ~(1 << pos);
}

void Bitmask::Clear() {
    bits = 0;
}