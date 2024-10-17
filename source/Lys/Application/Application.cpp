#include "Lys/Application/Application.hpp"

#include <GL/gl.h>
#include <GL/glew.h>

#include "Lys/Core/Log.hpp"
#include "Lys/MessageModule/MessageManager.hpp"
#include "Lys/StateModule/StateLys.hpp"

namespace lys
{

CommandLineArguments::CommandLineArguments(int argc, char** argv) : m_Argc(argc), m_Argv(argv) {}

const char* CommandLineArguments::mt_Get_Arg(int index)
{
    const char* l_Ret = nullptr;

    if (index < m_Argc)
    {
        l_Ret = m_Argv[index];
    }

    return l_Ret;
}

Application::Application(const char* title, const CommandLineArguments& cla) :
    m_CLA(cla), m_Window_Settings(title, sf::VideoMode::getDesktopMode(), false), m_State_Manager()
{}

int Application::mt_Run(void)
{
    int l_Return_Code = 0;
    Event l_Event;
    sf::Clock l_Clk;
    float l_Elapsed_Time;
    bool l_Run(true);
    std::size_t l_Next_State;
    State_Lys* l_Startup_State = new State_Lys;

    m_State_Manager.mt_Add_State(-1, l_Startup_State);

    Window::smt_Get().mt_Create(WindowSettings(m_Window_Settings.m_Title, m_Window_Settings.m_VideoMode, m_Window_Settings.m_Full_Screen));
    LYS_LOG_CORE_ERROR("glewInit: %d", glewInit());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    Renderer::smt_Create(&Window::smt_Get());

    l_Startup_State->mt_Set_Next_State(mt_Initialize());
    m_State_Manager.mt_Change_State(-1);

    m_Message_Manager.mt_Add_Receiver(&Application::mt_On_Change_State, this, true);

    l_Elapsed_Time = 0.0f;
    l_Clk.restart();
    while (l_Run == true)
    {
        l_Run = Window::smt_Get().mt_Handle_Events(m_State_Manager) == false;

        Renderer::smt_Get().mt_Begin_Scene(l_Elapsed_Time);

        m_State_Manager.mt_OnUpdate(l_Elapsed_Time);

        Renderer::smt_Get().mt_End_Scene();

        sf::sleep(sf::milliseconds(5));
        l_Elapsed_Time = l_Clk.restart().asSeconds();
    }

    mt_On_Shutdown();

    Renderer::smt_Destroy();
    Window::smt_Get().mt_Destroy();
    WorkingThread::smt_Get().mt_Stop_Thread();

    return l_Return_Code;
}

void Application::mt_On_Change_State(const Message_ChangeState& msg)
{
    m_State_Manager.mt_Change_State(msg.m_Next_State);
}

}  // namespace lys
