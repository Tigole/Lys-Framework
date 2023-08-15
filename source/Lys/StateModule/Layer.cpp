#include "Lys/StateModule/Layer.hpp"

#include "Lys/Application/Event.hpp"

namespace lys
{


LayerForward Layer::mt_On_Event(const Event& event)
{
    switch(event.m_SFML.type)
    {
    case sf::Event::Closed:                 /// Ignored
        break;
    case sf::Event::Resized:                /// Ignored
        break;
    case sf::Event::LostFocus:              /// Ignored
        break;
    case sf::Event::GainedFocus:            /// Ignored
        break;

    case sf::Event::TextEntered: return mt_On_Event_Text_Entered(TextEvent{event.m_SFML.text});
    case sf::Event::KeyPressed: return mt_On_Event_Key_Pressed(KeyEvent{event.m_SFML.key});
    case sf::Event::KeyReleased: return mt_On_Event_Key_Released(KeyEvent{event.m_SFML.key});

    case sf::Event::MouseWheelMoved:        /// Ignored (deprecated)
        break;
    case sf::Event::MouseWheelScrolled: return mt_On_Event_Mouse_Wheel_Scroll(MouseWheelScrollEvent{event.m_SFML.mouseWheelScroll});
    case sf::Event::MouseButtonPressed: return mt_On_Event_Mouse_Button_Pressed(MouseButtonEvent{event.m_SFML.mouseButton});
    case sf::Event::MouseButtonReleased: return mt_On_Event_Mouse_Button_Released(MouseButtonEvent{event.m_SFML.mouseButton});
    case sf::Event::MouseMoved: return mt_On_Event_Mouse_Move(MouseMoveEvent{event.m_SFML.mouseMove});
    case sf::Event::MouseEntered:           /// Ignored
        break;
    case sf::Event::MouseLeft:              /// Ignored
        break;

    case sf::Event::JoystickButtonPressed: return mt_On_Event_Joystick_Button_Pressed(JoystickButtonEvent{event.m_SFML.joystickButton});
    case sf::Event::JoystickButtonReleased: return mt_On_Event_Joystick_Button_Released(JoystickButtonEvent{event.m_SFML.joystickButton});
    case sf::Event::JoystickMoved: return mt_On_Event_Joystick_Move(JoystickMoveEvent{event.m_SFML.joystickMove});
    case sf::Event::JoystickConnected:      /// Ignored
        break;
    case sf::Event::JoystickDisconnected:   /// Ignored
        break;

    case sf::Event::TouchBegan:             /// Ignored
        break;
    case sf::Event::TouchMoved:             /// Ignored
        break;
    case sf::Event::TouchEnded:             /// Ignored
        break;
    case sf::Event::SensorChanged:          /// Ignored
        break;
    }

    return LayerForward::Stop;
}


}
