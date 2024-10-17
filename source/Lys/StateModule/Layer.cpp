#include "Lys/StateModule/Layer.hpp"

#include "Lys/Application/Event.hpp"

namespace lys
{

LayerForward Layer::mt_On_Event(const Event& event)
{
    if (event.m_SFML.is<sf::Event::TextEntered>() == true)
    {
        return mt_On_Event_Text_Entered(TextEvent { *event.m_SFML.getIf<sf::Event::TextEntered>() });
    }
    if (event.m_SFML.is<sf::Event::KeyPressed>() == true)
    {
        return mt_On_Event_Key_Pressed(KeyEvent { true, *event.m_SFML.getIf<sf::Event::KeyPressed>(), sf::Event::KeyReleased() });
    }
    if (event.m_SFML.is<sf::Event::KeyReleased>() == true)
    {
        return mt_On_Event_Key_Released(KeyEvent { false, sf::Event::KeyPressed(), *event.m_SFML.getIf<sf::Event::KeyReleased>() });
    }
    if (event.m_SFML.is<sf::Event::MouseWheelScrolled>() == true)
    {
        return mt_On_Event_Mouse_Wheel_Scroll(MouseWheelScrollEvent { *event.m_SFML.getIf<sf::Event::MouseWheelScrolled>() });
    }
    if (event.m_SFML.is<sf::Event::MouseButtonPressed>() == true)
    {
        return mt_On_Event_Mouse_Button_Pressed(
            MouseButtonEvent { true, *event.m_SFML.getIf<sf::Event::MouseButtonPressed>(), sf::Event::MouseButtonReleased() });
    }
    if (event.m_SFML.is<sf::Event::MouseButtonReleased>() == true)
    {
        return mt_On_Event_Mouse_Button_Released(
            MouseButtonEvent { false, sf::Event::MouseButtonPressed(), *event.m_SFML.getIf<sf::Event::MouseButtonReleased>() });
    }
    if (event.m_SFML.is<sf::Event::MouseMoved>() == true)
    {
        return mt_On_Event_Mouse_Move(MouseMoveEvent { *event.m_SFML.getIf<sf::Event::MouseMoved>() });
    }
    if (event.m_SFML.is<sf::Event::JoystickButtonPressed>() == true)
    {
        return mt_On_Event_Joystick_Button_Pressed(
            JoystickButtonEvent { true, *event.m_SFML.getIf<sf::Event::JoystickButtonPressed>(), sf::Event::JoystickButtonReleased() });
    }
    if (event.m_SFML.is<sf::Event::JoystickButtonReleased>() == true)
    {
        return mt_On_Event_Joystick_Button_Released(
            JoystickButtonEvent { false, sf::Event::JoystickButtonPressed(), *event.m_SFML.getIf<sf::Event::JoystickButtonReleased>() });
    }
    if (event.m_SFML.is<sf::Event::JoystickMoved>() == true)
    {
        return mt_On_Event_Joystick_Move(JoystickMoveEvent { *event.m_SFML.getIf<sf::Event::JoystickMoved>() });
    }

    return LayerForward::Stop;
}

}  // namespace lys
