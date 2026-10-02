#ifndef _LYS_RANDOM_ENGINE_HPP
#define _LYS_RANDOM_ENGINE_HPP 1

#include <cstdint>
#include <limits>
#include <lys-config.hpp>

namespace lys
{

class LYS_API RandomEngine
{
public:
    uint32_t Generate_Int(void);

    int Generate_IntRange(int min_incl, int max_excl);

    float Generate_Normalized_Float(void);

    float Generate_Float_Range(float min_incl, float max_excl);

    void Set_Seed(uint32_t seed);

    uint32_t Get_Seed(void) const;

private:
    uint32_t m_Seed;
    uint32_t m_Call_Count;
    uint32_t m_Lehmer_State;
};

}  // namespace lys

#endif  // _LYS_RANDOM_ENGINE_HPP
