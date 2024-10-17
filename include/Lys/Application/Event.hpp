#ifndef _LYS_EVENT_HPP
#define _LYS_EVENT_HPP 1

#include <SFML/Window/Event.hpp>

#include "Lys/LysConfig.hpp"

namespace lys
{

struct LYS_API MouseButtonEvent
{
    bool m_Is_Pressed                         = true;
    sf::Event::MouseButtonPressed m_Pressed   = {};
    sf::Event::MouseButtonReleased m_Released = {};
};

struct LYS_API MouseMoveEvent
{
    sf::Event::MouseMoved m_Mouse = {};
};

struct LYS_API MouseWheelScrollEvent
{
    sf::Event::MouseWheelScrolled m_Scroll = {};
};

struct LYS_API KeyEvent
{
    bool m_Is_Pressed                 = true;
    sf::Event::KeyPressed m_Pressed   = {};
    sf::Event::KeyReleased m_Released = {};
};

struct LYS_API JoystickButtonEvent
{
    bool m_Is_Pressed                            = true;
    sf::Event::JoystickButtonPressed m_Pressed   = {};
    sf::Event::JoystickButtonReleased m_Released = {};
};

struct LYS_API JoystickMoveEvent
{
    sf::Event::JoystickMoved m_Joystick = {};
};

struct LYS_API TextEvent
{
    sf::Event::TextEntered m_Text = {};
};

struct LYS_API Event
{
    sf::Event m_SFML = { sf::Event::Closed() };
};

}  // namespace lys

#endif  // _LYS_EVENT_HPP
