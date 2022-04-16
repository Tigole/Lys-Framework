#include "Lys/Application/Application.hpp"

#include "Lys/StateModule/StateLys.hpp"
#include "Lys/MessageModule/MessageManager.hpp"

namespace lys
{



CommandLineArguments::CommandLineArguments(int argc, char** argv) :
    m_Argc(argc),
    m_Argv(argv)
{}

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
    m_CLA(cla),
    m_Window_Settings(title, sf::VideoMode::getDesktopMode(), false),
    m_State_Manager()
{
    Renderer::smt_Create(&Window::smt_Get());
}


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

    l_Startup_State->mt_Set_Next_State(mt_Initialize());
    m_State_Manager.mt_Change_State(-1);

    m_Message_Manager.mt_Add_Receiver(&Application::mt_On_Change_State, this, true);

    l_Elapsed_Time = 0.0f;
    l_Clk.restart();
    while(l_Run)
    {
        while(Window::smt_Get().mt_Poll_Event(l_Event))
        {
            if (l_Event.m_SFML.type == sf::Event::Closed)
            {
                l_Run = false;
            }

            m_State_Manager.mt_OnEvent(l_Event);
        }

        Renderer::smt_Get().mt_Begin_Scene(l_Elapsed_Time);

        m_State_Manager.mt_OnUpdate(l_Elapsed_Time);

        Renderer::smt_Get().mt_End_Scene();

        sf::sleep(sf::milliseconds(5));
        l_Elapsed_Time = l_Clk.restart().asSeconds();
    }

    return l_Return_Code;
}

void Application::mt_On_Change_State(const Message_ChangeState& msg)
{
    m_State_Manager.mt_Change_State(msg.m_Next_State);
}


}
