#include <gtest/gtest.h>

#include <cstdint>
#include <lys-module-particle-system.hpp>

template<std::size_t MaxParticleCount>
struct ParticleContainerList
{
    void Swap_Particles(std::size_t aa, std::size_t bb)
    {
        m_Mono_Field.Swap_Particles(aa, bb);
        m_Duration.Swap_Particles(aa, bb);
        m_Interpolated.Swap_Particles(aa, bb);
    }

    lys::ParticleContainer_MonoField<MaxParticleCount, int8_t> m_Mono_Field;
    lys::ParticleContainer_DurationX<MaxParticleCount> m_Duration;
    lys::ParticleContainer_DurationY<MaxParticleCount, int8_t> m_Interpolated;
};

TEST(ParticleSystem, Enabling_Disabling)
{
    lys::ParticleSystem<20, ParticleContainerList<20>> system;

    /// Basic usage
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 0);
    system.Enable_Particle(0);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 1);
    system.Disable_Particle(0);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 0);

    /// No creation if required idx > MaxParticleCount
    system.Enable_Particle(20);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 0);

    /// No crash / deletion if required idx > MaxParticleCount
    system.Disable_Particle(20);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 0);

    /// No crash / deletion if no particle enabled
    system.Disable_Particle(0);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 0);

    /// Working with forwarded idx
    {
        for (std::size_t ii = 0; ii < system.Get_Max_Particle_Count(); ii++)
        {
            system.m_Container_List.m_Mono_Field.m_Field[ii] = ii;
        }

        system.Enable_Particle(5);
        EXPECT_EQ(system.Get_Alive_Particle_Count(), 1);
        EXPECT_EQ(system.m_Container_List.m_Mono_Field.m_Field[0], 5);
        EXPECT_EQ(system.m_Container_List.m_Mono_Field.m_Field[5], 0);
        system.Disable_Particle(5);
        EXPECT_EQ(system.Get_Alive_Particle_Count(), 1);
        EXPECT_EQ(system.m_Container_List.m_Mono_Field.m_Field[0], 5);
        EXPECT_EQ(system.m_Container_List.m_Mono_Field.m_Field[5], 0);
        system.Disable_Particle(0);
        EXPECT_EQ(system.Get_Alive_Particle_Count(), 0);
        EXPECT_EQ(system.m_Container_List.m_Mono_Field.m_Field[0], 5);
        EXPECT_EQ(system.m_Container_List.m_Mono_Field.m_Field[5], 0);
    }
}

TEST(ParticleSystem, Built_In_Updater_Lifetime)
{
    lys::ParticleSystem<20, ParticleContainerList<20>> system;

    system.m_Container_List.m_Duration.m_Current_Duration[0] = 0.0f;
    system.m_Container_List.m_Duration.m_Limit_Duration[0]   = 10.0f;
    system.m_Container_List.m_Interpolated.m_Current[0]      = 10;
    system.m_Container_List.m_Interpolated.m_Start[0]        = 0;
    system.m_Container_List.m_Interpolated.m_Final[0]        = 20;

    system.Enable_Particle(0);
    EXPECT_EQ(system.m_Container_List.m_Duration.m_Current_Duration[0], 0.0f);

    lys::ParticleUpdater::Update_Particles_Lifetime(system, system.m_Container_List.m_Duration, 0.0f);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 1);
    EXPECT_EQ(system.m_Container_List.m_Duration.m_Current_Duration[0], 0.0f);

    lys::ParticleUpdater::Update_Particles_Lifetime(system, system.m_Container_List.m_Duration, 5.0f);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 1);
    EXPECT_EQ(system.m_Container_List.m_Duration.m_Current_Duration[0], 5.0f);

    lys::ParticleUpdater::Update_Particles_Lifetime(system, system.m_Container_List.m_Duration, 5.0f);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 1);
    EXPECT_EQ(system.m_Container_List.m_Duration.m_Current_Duration[0], 10.0f);

    lys::ParticleUpdater::Update_Particles_Lifetime(system, system.m_Container_List.m_Duration, 5.0f);
    EXPECT_EQ(system.Get_Alive_Particle_Count(), 0);
    EXPECT_EQ(system.m_Container_List.m_Duration.m_Current_Duration[0], 15.0f);
}

TEST(ParticleSystem, Built_In_Updater_Interpolation)
{
    lys::ParticleSystem<20, ParticleContainerList<20>> system;

    system.m_Container_List.m_Duration.m_Current_Duration[0] = 0.0f;
    system.m_Container_List.m_Duration.m_Limit_Duration[0]   = 1.0f;
    system.m_Container_List.m_Interpolated.m_Current[0]      = 10;
    system.m_Container_List.m_Interpolated.m_Start[0]        = 0;
    system.m_Container_List.m_Interpolated.m_Final[0]        = 20;

    system.Enable_Particle(0);
    EXPECT_EQ(system.m_Container_List.m_Interpolated.m_Current[0], 10);

    lys::ParticleUpdater::Update_Particles_Interpolation(system.Get_Alive_Particle_Count(), system.m_Container_List.m_Duration,
                                                         system.m_Container_List.m_Interpolated);
    EXPECT_EQ(system.m_Container_List.m_Interpolated.m_Current[0], 0);

    system.m_Container_List.m_Duration.m_Current_Duration[0] = 0.5f;
    lys::ParticleUpdater::Update_Particles_Interpolation(system.Get_Alive_Particle_Count(), system.m_Container_List.m_Duration,
                                                         system.m_Container_List.m_Interpolated);
    EXPECT_EQ(system.m_Container_List.m_Interpolated.m_Current[0], 10);

    system.m_Container_List.m_Duration.m_Current_Duration[0] = 1.0f;
    lys::ParticleUpdater::Update_Particles_Interpolation(system.Get_Alive_Particle_Count(), system.m_Container_List.m_Duration,
                                                         system.m_Container_List.m_Interpolated);
    EXPECT_EQ(system.m_Container_List.m_Interpolated.m_Current[0], 20);
}
