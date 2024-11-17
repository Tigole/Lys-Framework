#ifndef _LYS_EVENT_HPP
#define _LYS_EVENT_HPP 1

#include <SFML/Window/Event.hpp>

#include "Lys/LysConfig.hpp"
#include "Lys/MathModule/Vector2.hpp"

namespace lys
{

/// @brief Based on SFML Buttons
enum class MouseButtonType
{
    Left,      //!< The left mouse button
    Right,     //!< The right mouse button
    Middle,    //!< The middle (wheel) mouse button
    XButton1,  //!< The first extra mouse button
    XButton2,  //!< The second extra mouse button

    ButtonCount  //!< Keep last -- the total number of mouse buttons
};

struct LYS_API WindowCloseRequestEvent
{};

/*struct LYS_API WindowResizeEvent
{
    lys::Vector2u m_New_Size = {};
};*/

struct LYS_API MouseButtonPressedEvent
{
    lys::MouseButtonType m_Button = {};
    lys::Vector2i m_Position      = {};
};

struct LYS_API MouseButtonReleasedEvent
{
    lys::MouseButtonType m_Button = {};
    lys::Vector2i m_Position      = {};
};

struct LYS_API MouseMoveEvent
{
    lys::Vector2i m_Position = {};
};

struct LYS_API MouseWheelScrollEvent
{
    sf::Event::MouseWheelScrolled m_Scroll = {};
};

struct LYS_API KeyPressedEvent
{
    sf::Event::KeyPressed m_Pressed = {};
};

struct LYS_API KeyReleasedEvent
{
    sf::Event::KeyReleased m_Released = {};
};

struct LYS_API JoystickConnectedEvent
{
    sf::Event::JoystickConnected m_Connection = {};
};

struct LYS_API JoystickDisconnectedEvent
{
    sf::Event::JoystickDisconnected m_Disconnection = {};
};

struct LYS_API JoystickButtonPressedEvent
{
    sf::Event::JoystickButtonPressed m_Pressed = {};
};

struct LYS_API JoystickButtonReleasedEvent
{
    sf::Event::JoystickButtonReleased m_Released = {};
};

struct LYS_API JoystickMoveEvent
{
    sf::Event::JoystickMoved m_Joystick = {};
};

struct LYS_API TextEvent
{
    std::uint32_t m_Unicode = {};
};

}  // namespace lys

#endif  // _LYS_EVENT_HPP
