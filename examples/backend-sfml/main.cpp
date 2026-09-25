#if 0
#include "Lys/Lys.hpp"

constexpr const char* TOKEN = "APP";

class Layer: public lys::Layer
{
public:
    Layer();

    lys::LayerForward mt_On_Update(float elapsed_time) override;
    void mt_On_Render(void) override;

private:
};

Layer::Layer() : lys::Layer("layerId")
{
    //
}

lys::LayerForward Layer::mt_On_Update(float elapsed_time)
{
    return lys::LayerForward::Stop;
}

void Layer::mt_On_Render(void)
{
    lys::CircleSettings settings;
    settings.m_Center     = lys::Window::smt_Get().mt_Get_Size() / 2;
    settings.m_Radius     = 20.0;
    settings.m_Fill_Color = lys::Color(204 / 255.0f, 32 / 255.0f, 184 / 255.0f);
    lys::Renderer::smt_Get().mt_Draw_Circle(settings);
}

template<typename LayerType>
class State: public lys::State
{
public:
    State() : m_Layer() {}

    bool mt_On_Entry(void) override
    {
        mt_Push_Layer(&m_Layer);

        return true;
    }

private:
    LayerType m_Layer;
};

class Application: public lys::Application
{
public:
    Application(const lys::CommandLineArguments& cla);

    std::size_t mt_Initialize(void) override;
};

Application::Application(const lys::CommandLineArguments& cla) : lys::Application("Lys-Sandbox", cla) {}

std::size_t Application::mt_Initialize(void)
{
    LYS_PROFILE_FUNCTION;

    m_State_Manager.mt_Register_State<State<Layer>>(0);

    return 0;
}

int main(int argc, char** argv)
{
    lys::profiler::fn_Initialize_Profiler("Profile.json");
    LYS_PROFILE_FUNCTION;

    lys::log::LoggerPool::smt_Get().mt_Get_Logger(LYS_LOG_TOKEN).mt_Add_Sink(new lys::log::Console);
    lys::log::LoggerPool::smt_Get().mt_Get_Logger(LYS_LOG_TOKEN).mt_Set_Level(lys::log::LogLevel::Debug);
    lys::log::LoggerPool::smt_Get().mt_Get_Logger(TOKEN).mt_Add_Sink(new lys::log::Console).mt_Add_Sink(new lys::log::File("log.txt"));

    Application l_Application(lys::CommandLineArguments(argc, argv));
    LYS_LOG_DEBUG(TOKEN, "test");

    return l_Application.mt_Run();
}
#endif
