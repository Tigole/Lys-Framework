#include "Lys/StateModule/Layer.hpp"

#include "Lys/Application/Event.hpp"

namespace lys
{


void Layer::mt_OnEvent(const Event& event)
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

    case sf::Event::TextEntered:
        mt_Send_Message(event.m_SFML.text);
        break;
    case sf::Event::KeyPressed:
        mt_Send_Message(KeyEvent{true, event.m_SFML.key});
        break;
    case sf::Event::KeyReleased:
        mt_Send_Message(KeyEvent{false, event.m_SFML.key});
        break;

    case sf::Event::MouseWheelMoved:        /// Ignored (deprecated)
        break;
    case sf::Event::MouseWheelScrolled:
        mt_Send_Message(event.m_SFML.mouseWheelScroll);
        break;
    case sf::Event::MouseButtonPressed:
        mt_Send_Message(event.m_SFML.mouseButton);
        break;
    case sf::Event::MouseButtonReleased:
        mt_Send_Message(event.m_SFML.mouseButton);
        break;
    case sf::Event::MouseMoved:
        mt_Send_Message(event.m_SFML.mouseMove);
        break;
    case sf::Event::MouseEntered:           /// Ignored
        break;
    case sf::Event::MouseLeft:              /// Ignored
        break;

    case sf::Event::JoystickButtonPressed:
        mt_Send_Message(JoystickButtonEvent{true, event.m_SFML.joystickButton});
        break;
    case sf::Event::JoystickButtonReleased:
        mt_Send_Message(JoystickButtonEvent{false, event.m_SFML.joystickButton});
        break;
    case sf::Event::JoystickMoved:
        mt_Send_Message(event.m_SFML.joystickMove);
        break;
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
}


}
