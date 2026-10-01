#ifndef _LYS_PARTICLE_SYSTEM_HPP
#define _LYS_PARTICLE_SYSTEM_HPP 1

#include <cstdint>
#include <vector>

namespace lys
{

struct ParticleContainer_Base;

template<std::size_t MaxParticleCount, class ParticleContainerList>
struct ParticleSystem
{
    void Enable_Particle(std::size_t particle_idx)
    {
        if (particle_idx < MaxParticleCount)
        {
            m_Container_List.Swap_Particles(particle_idx, m_Particle_Alive_Count);
            m_Particle_Alive_Count++;
        }
    }

    void Disable_Particle(std::size_t particle_idx)
    {
        if ((m_Particle_Alive_Count > 0) && (particle_idx < m_Particle_Alive_Count))
        {
            m_Container_List.Swap_Particles(particle_idx, m_Particle_Alive_Count - 1);
            m_Particle_Alive_Count--;
        }
    }

    std::size_t Get_Alive_Particle_Count(void) const
    {
        return m_Particle_Alive_Count;
    }

    constexpr std::size_t Get_Max_Particle_Count(void) const
    {
        return MaxParticleCount;
    }

    ParticleContainerList m_Container_List = {};

private:
    std::size_t m_Particle_Alive_Count = 0;
};

}  // namespace lys

#endif  // _LYS_PARTICLE_SYSTEM_HPP
