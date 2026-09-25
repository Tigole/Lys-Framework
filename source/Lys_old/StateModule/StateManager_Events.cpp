#include "Lys/StateModule/StateManager.hpp"

namespace lys
{
void StateManager::mt_On_Event_Closed(const WindowCloseRequestEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_Closed);
}

void StateManager::mt_On_Event_Resized(const WindowResizeEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_Resized);
}

void StateManager::mt_On_Event_FocusLost(const WindowFocusLostEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_FocusLost);
}

void StateManager::mt_On_Event_FocusGained(const WindowFocusGainedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_FocusGained);
}

void StateManager::mt_On_Event_TextEntered(const TextEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_TextEntered);
}

void StateManager::mt_On_Event_KeyPressed(const KeyPressedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_KeyPressed);
}

void StateManager::mt_On_Event_KeyReleased(const KeyReleasedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_KeyReleased);
}

void StateManager::mt_On_Event_MouseButtonPressed(const MouseButtonPressedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_MouseButtonPressed);
}

void StateManager::mt_On_Event_MouseButtonReleased(const MouseButtonReleasedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_MouseButtonReleased);
}

void StateManager::mt_On_Event_MouseMoved(const MouseMovedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_MouseMoved);
}

void StateManager::mt_On_Event_MouseWheelScrolled(const MouseWheelScrolledEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_MouseWheelScrolled);
}

void StateManager::mt_On_Event_JoystickConnected(const JoystickConnectedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickConnected);
}

void StateManager::mt_On_Event_JoystickDisconnected(const JoystickDisconnectedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickDisconnected);
}

void StateManager::mt_On_Event_JoystickButtonPressed(const JoystickButtonPressedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickButtonPressed);
}

void StateManager::mt_On_Event_JoystickButtonReleased(const JoystickButtonReleasedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickButtonReleased);
}

void StateManager::mt_On_Event_JoystickMoved(const JoystickMovedEvent& event)
{
    mt_On_Event(event, &State::mt_On_Event_JoystickMoved);
}
}  // namespace lys
