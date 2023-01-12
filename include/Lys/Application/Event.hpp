#ifndef _LYS_EVENT_HPP
#define _LYS_EVENT_HPP 1

#include "Lys/LysConfig.hpp"
#include <SFML/Window/Event.hpp>

namespace lys
{

struct LYS_API MouseButtonEvent
{
    sf::Event::MouseButtonEvent m_Mouse;
};

struct LYS_API MouseMoveEvent
{
    sf::Event::MouseMoveEvent m_Mouse;
};

struct LYS_API MouseWheelScrollEvent
{
    sf::Event::MouseWheelScrollEvent m_Scroll;
};



struct LYS_API KeyEvent
{
    sf::Event::KeyEvent m_Key;
};



struct LYS_API JoystickButtonEvent
{
    sf::Event::JoystickButtonEvent m_Button;
};

struct LYS_API JoystickMoveEvent
{
    sf::Event::JoystickMoveEvent m_Joystick;
};



struct LYS_API TextEvent
{
    sf::Event::TextEvent m_Text;
};



struct LYS_API Event
{
    sf::Event m_SFML;
};


}

#endif // _LYS_EVENT_HPP
