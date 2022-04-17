#ifndef _GUI_MANAGER_HPP
#define _GUI_MANAGER_HPP 1

#include "Lys/Core/Singleton.hpp"
#include "GUI_Event.hpp"

#include <unordered_map>
#include <stack>
#include <queue>

namespace lys
{

struct Event;

namespace gui
{

class Interface;

class Manager : public Singleton<Manager>
{
    friend Singleton<Manager>;
public:

    void mt_Push_Interface(Interface* i);

    bool mt_Handled_Event(const Event& event);

    void mt_OnUpdate(float elapsed_time);

    //bool mt_Poll_Event(GUIEvent& e);

    //void mt_Push_Event(const BtnClicked& btn_clicked);

private:
    Manager();

    std::unordered_map<std::string, Interface*> m_Interfaces;

    bool m_Mouse_Captured = false;
    bool m_Keyboard_Captured = false;
    bool m_Text_Captured = false;

    //std::queue<GUIEvent> m_Events_Queue;
};


}

}

#endif // !_GUI_MANAGER_HPP
