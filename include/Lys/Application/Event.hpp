#ifndef _LYS_EVENT_HPP
#define _LYS_EVENT_HPP 1

#include <SFML/Window/Event.hpp>

namespace lys
{

struct MouseButtonEvent
{
    bool m_Pressed;
    sf::Event::MouseButtonEvent m_Mouse;
};

struct KeyEvent
{
    bool m_Pressed;
    sf::Event::KeyEvent m_Key;
};

struct JoystickButtonEvent
{
    bool m_Pressed;
    sf::Event::JoystickButtonEvent m_Button;
};

struct Event
{
    sf::Event m_SFML;
};


}

#endif // _LYS_EVENT_HPP
