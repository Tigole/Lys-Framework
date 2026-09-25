#include <gtest/gtest.h>

#include <lys-module-application-states.hpp>

std::vector<uint8_t> phases;

class State;

class MonitoredLayer: public lys::ApplicationLayer
{
public:
    MonitoredLayer(State& state) : lys::ApplicationLayer("MonitoredLayer"), m_State(state) {}
    State& m_State;

    void On_Activate(void) override;

    void On_Deactivate(void) override;

    lys::ApplicationLayerForward On_Update(void) override;

    void On_Render(void) override;

    lys::ApplicationLayerForward Get_Rendering_Forward_Strategy(void) const override;
};

class UnMonitoredLayer: public lys::ApplicationLayer
{
public:
    UnMonitoredLayer(State& state) : lys::ApplicationLayer("UnMonitoredLayer"), m_State(state) {}

    State& m_State;
};

class State: public lys::ApplicationState
{
public:
    State() : m_Monitored_Layer(*this), m_Unmonitored_Layer(*this) {}

    void On_Create()
    {
        Push_Layer(&m_Monitored_Layer);
    }

    void Change_Layer(void)
    {
        Pop_Layer(&m_Monitored_Layer);
        Push_Layer(&m_Unmonitored_Layer);
    }

    MonitoredLayer m_Monitored_Layer;
    UnMonitoredLayer m_Unmonitored_Layer;
};

void MonitoredLayer::On_Activate(void)
{
    phases.push_back(0);
}

void MonitoredLayer::On_Deactivate(void)
{
    phases.push_back(4);
}

lys::ApplicationLayerForward MonitoredLayer::On_Update(void)
{
    phases.push_back(1);
    return lys::ApplicationLayerForward::Continue;
}

void MonitoredLayer::On_Render(void)
{
    phases.push_back(3);
    m_State.Change_Layer();
}

lys::ApplicationLayerForward MonitoredLayer::Get_Rendering_Forward_Strategy(void) const
{
    phases.push_back(2);
    return lys::ApplicationLayerForward::Stop;
}

TEST(ApplicationStateModule, SequenceDiagram)
{
    lys::ApplicationStateManager applicationStateManager;

    applicationStateManager.Register_State<State>(0);

    applicationStateManager.Set_Initial_State<State>(0, [](State&) { phases.clear(); });

    applicationStateManager.On_Update_Logic();
    applicationStateManager.On_Update_Render();

    ASSERT_EQ(phases.size(), (std::size_t)4);
    EXPECT_EQ(phases[0], 0);
    EXPECT_EQ(phases[1], 1);
    EXPECT_EQ(phases[2], 2);
    EXPECT_EQ(phases[3], 3);

    applicationStateManager.On_Update_Logic();
    applicationStateManager.On_Update_Render();

    ASSERT_EQ(phases.size(), (std::size_t)5);
    EXPECT_EQ(phases[0], 0);
    EXPECT_EQ(phases[1], 1);
    EXPECT_EQ(phases[2], 2);
    EXPECT_EQ(phases[3], 3);
    EXPECT_EQ(phases[4], 4);
}
