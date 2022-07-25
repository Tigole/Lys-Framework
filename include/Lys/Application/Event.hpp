#ifndef _LYS_EVENT_HPP
#define _LYS_EVENT_HPP 1

#include "Lys/LysConfig.hpp"
#include <SFML/Window/Event.hpp>

namespace lys
{

struct LYS_API MouseButtonEvent
{
    bool m_Pressed;
    sf::Event::MouseButtonEvent m_Mouse;
};

struct LYS_API KeyEvent
{
    bool m_Pressed;
    sf::Event::KeyEvent m_Key;
};

struct LYS_API JoystickButtonEvent
{
    bool m_Pressed;
    sf::Event::JoystickButtonEvent m_Button;
};

struct LYS_API Event
{
    sf::Event m_SFML;
};


}

#endif // _LYS_EVENT_HPP
