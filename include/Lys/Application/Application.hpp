#ifndef _LYS_APPLICATION_HPP
#define _LYS_APPLICATION_HPP 1

#include "Lys/StateModule/StateManager.hpp"
#include "Lys/GraphicModule/Renderer.hpp"
#include "Lys/MessageModule/MessageManager.hpp"
#include "Window.hpp"

namespace lys
{


struct Message_ChangeState
{
    Message_ChangeState(std::size_t next_state) : m_Next_State(next_state) {}

    std::size_t m_Next_State;
};


class CommandLineArguments
{
public:
    CommandLineArguments(int argc, char** argv);

    const char* mt_Get_Arg(int index);

private:
    int m_Argc;
    char** m_Argv;
};


class Application
{
public:
    Application(const char* title, const CommandLineArguments& cla);
    virtual ~Application(){}

    virtual std::size_t mt_Initialize(void) = 0;

    int mt_Run(void);

protected:

    CommandLineArguments m_CLA;
    WindowSettings m_Window_Settings;

    StateManager m_State_Manager;
    MessageManager m_Message_Manager;

private:

    void mt_On_Change_State(const Message_ChangeState& msg);
};



}


#endif // _LYS_APPLICATION_HPP
