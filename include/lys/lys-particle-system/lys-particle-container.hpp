#ifndef _LYS_PARTICLE_CONTAINER_HPP
#define _LYS_PARTICLE_CONTAINER_HPP 1

#include <cstdint>

namespace lys
{

template<std::size_t MaxParticleCount>
struct ParticleContainer_DurationX
{
    void Swap_Particles(std::size_t aa, std::size_t bb)
    {
        std::swap(m_Current_Duration[aa], m_Current_Duration[bb]);
        std::swap(m_Limit_Duration[aa], m_Limit_Duration[bb]);
    }

    float m_Current_Duration[MaxParticleCount] = {};
    float m_Limit_Duration[MaxParticleCount]   = {};
};

template<std::size_t MaxParticleCount, typename T>
struct ParticleContainer_MonoField
{
    void Swap_Particles(std::size_t aa, std::size_t bb)
    {
        std::swap(m_Field[aa], m_Field[bb]);
    }

    T m_Field[MaxParticleCount] = {};
};

template<std::size_t MaxParticleCount, typename T>
struct ParticleContainer_DurationY
{
    void Swap_Particles(std::size_t aa, std::size_t bb)
    {
        std::swap(m_Current[aa], m_Current[bb]);
        std::swap(m_Start[aa], m_Start[bb]);
        std::swap(m_Final[aa], m_Final[bb]);
    }

    T m_Current[MaxParticleCount] = {};
    T m_Start[MaxParticleCount]   = {};
    T m_Final[MaxParticleCount]   = {};
};

}  // namespace lys

#endif  // _LYS_PARTICLE_CONTAINER_HPP
