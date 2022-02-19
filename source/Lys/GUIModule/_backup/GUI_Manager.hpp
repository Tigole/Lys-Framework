#ifndef _LYS_GUI_MANAGER_HPP
#define _LYS_GUI_MANAGER_HPP 1

#include "MathModule/Vector2.hpp"

#include "GUIModule/GUI_Interface.hpp"

namespace lys
{

namespace gui
{


class Manager
{
public:

    /// true when handled, false otherwise
    bool mt_OnMouseMove(const Vector2f& screen_pos);
    bool mt_OnMouseClick(const Vector2f& screen_pos);
    bool mt_OnMouseRelease(const Vector2f& screen_pos);

    void mt_OnUpdate(float elapsed_time);

    void mt_Push_Interface(Interface* interface);
    void mt_Pop_Interface(Interface* interface);

private:

    std::vector<Interface*> m_Interfaces;
};


}


}

#endif // _LYS_GUI_MANAGER_HPP
