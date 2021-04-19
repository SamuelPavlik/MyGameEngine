#ifndef Bitmask_hpp
#define Bitmask_hpp

#include <stdint.h>

class Bitmask {
public:
    Bitmask();

    void SetMask(const Bitmask& other);
    uint32_t GetMask() const;

    bool GetBit(size_t pos) const;
    void SetBit(size_t pos, bool on);
    void SetBit(size_t pos);
    void ClearBit(size_t pos);
    void Clear();

private:
    uint32_t bits;
};

#endif /* Bitmask_hpp */