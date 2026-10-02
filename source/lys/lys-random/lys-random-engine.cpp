#include <lys-random/lys-random-engine.hpp>

namespace lys
{

uint32_t RandomEngine::Generate_Int(void)
{
    m_Lehmer_State += 0xe120fc15;
    uint64_t tmp = (uint64_t)m_Lehmer_State * 0x4a39b70d;
    uint32_t m1  = (tmp >> 32) ^ tmp;
    tmp          = m1 * (uint64_t)m1 * 0x12fad5c9;
    m1           = (tmp >> 32) ^ tmp;
    return m1;
}

int RandomEngine::Generate_IntRange(int min_incl, int max_excl)
{
    if (min_incl == max_excl)
    {
        return min_incl;
    }

    return (Generate_Int() % (max_excl - min_incl)) + min_incl;
}

float RandomEngine::Generate_Normalized_Float(void)
{
    return static_cast<float>(Generate_Int()) / std::numeric_limits<uint32_t>::max();
}

float RandomEngine::Generate_Float_Range(float min_incl, float max_excl)
{
    return Generate_Normalized_Float() * (max_excl - min_incl) + min_incl;
}

void RandomEngine::Set_Seed(uint32_t seed)
{
    m_Seed         = seed;
    m_Lehmer_State = seed;
}

uint32_t RandomEngine::Get_Seed(void) const
{
    return m_Lehmer_State;
}

}  // namespace lys
