#ifndef _LYS_RAND_HPP
#define _LYS_RAND_HPP 1

#include <cstdint>
#include <cassert>
#include <limits>

#include "Lys/LysConfig.hpp"
#include "Lys/Core/Core.hpp"

namespace lys
{


class LYS_API Rand
{
public:

    uint32_t mt_Generate_Int(void)
    {
        m_Lehmer_State += 0xe120fc15;
        uint64_t tmp = (uint64_t)m_Lehmer_State * 0x4a39b70d;
        uint32_t m1 = (tmp >> 32) ^ tmp;
        tmp = m1 * (uint64_t)m1 * 0x12fad5c9;
        m1 = (tmp >> 32) ^ tmp;
        return m1;
    }

    int mt_Generate_IntRange(int min, int max)
    {
        LYS_ASSERT(min != max);

        return (mt_Generate_Int() % (max - min)) + min;
    }

    float mt_Generate_Normalized_Float(void)
    {
        return static_cast<float>(mt_Generate_Int()) / std::numeric_limits<uint32_t>::max();
    }

    float mt_Generate_Float_Range(float min, float max)
    {
        return mt_Generate_Normalized_Float() * (max - min) + min;
    }

    void mt_Set_Seed(uint32_t seed)
    {
        m_Seed = seed;
        m_Lehmer_State = seed;
    }

private:
    uint32_t m_Seed;
    uint32_t m_Call_Count;
    uint32_t m_Lehmer_State;
};



}

#endif // _LYS_RAND_HPP
