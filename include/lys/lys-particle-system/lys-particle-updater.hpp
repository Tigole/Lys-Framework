#ifndef _LYS_PARTICLE_UPDATER_HPP
#define _LYS_PARTICLE_UPDATER_HPP 1

#include <lys-particle-system/lys-particle-container.hpp>
#include <lys-particle-system/lys-particle-system.hpp>

namespace lys
{

class ParticleUpdater
{
public:
    template<std::size_t MaxParticleCount, typename T>
    static void Update_Particles_Interpolation(std::size_t alive_particle_count, const ParticleContainer_DurationX<MaxParticleCount>& x,
                                               ParticleContainer_DurationY<MaxParticleCount, T>& y)
    {
        auto& l_Y_Current = y.m_Current;
        auto& l_Y_Start   = y.m_Start;
        auto& l_Y_Final   = y.m_Final;
        auto& l_X_Current = x.m_Current_Duration;
        auto& l_X_Limit   = x.m_Limit_Duration;

        for (std::size_t ii = 0; ii < alive_particle_count; ii++)
        {
            const float t   = l_X_Current[ii] / l_X_Limit[ii];
            l_Y_Current[ii] = l_Y_Start[ii] + t * (l_Y_Final[ii] - l_Y_Start[ii]);
        }
    }

    template<std::size_t MaxParticleCount, class ParticleSystemType>
    static void Update_Particles_Lifetime(ParticleSystemType& system, ParticleContainer_DurationX<MaxParticleCount>& x, float dt)
    {
        for (std::size_t ii = 0; ii < system.Get_Alive_Particle_Count(); ii++)
        {
            x.m_Current_Duration[ii] += dt;
            if (x.m_Current_Duration[ii] > x.m_Limit_Duration[ii])
            {
                system.Disable_Particle(ii);
                ii--;
            }
        }
    }

private:
};

}  // namespace lys

#endif  // _LYS_PARTICLE_UPDATER_HPP
