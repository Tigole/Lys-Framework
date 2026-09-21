#include "Lys/Application/Window.hpp"

#include "Lys/Core/Log.hpp"
#include "Lys/Core/SFML_Conversion.hpp"
#include "Lys/StateModule/StateManager.hpp"

#if (LYS_PLATFORM == LYS_PLATFORM_WINDOWS)
#include <windows.h>
#endif

// #include "imgui-SFML.h"

namespace lys
{

WindowSettings::WindowSettings(const char* title, const sf::VideoMode& vm, bool full_screen) :
    m_Title(title), m_VideoMode(vm), m_Full_Screen(full_screen)
{}

Window& Window::smt_Get(void)
{
    static Window ls_Singleton;

    return ls_Singleton;
}

Window::Window() : m_Wnd(nullptr) {}

void Window::mt_Create(const WindowSettings& settings)
{
    m_Wnd = std::make_unique<sf::RenderWindow>();
    m_Wnd->create(settings.m_VideoMode, settings.m_Title, sf::Style::Default,
                  (settings.m_Full_Screen == true) ? sf::State::Fullscreen : sf::State::Windowed);

#if (LYS_PLATFORM == LYS_PLATFORM_WINDOWS)
    if (settings.m_VideoMode == sf::VideoMode::getDesktopMode())
    {
        ShowWindow(m_Wnd->getNativeHandle(), SW_MAXIMIZE);
    }
#endif

#if 0
    if (ImGui::SFML::Init(m_Wnd, true) == false)
    {
        LYS_LOG_CORE_FATAL("Failed to initialize imgui for SFML");
        exit(-1);
    }
#endif

    m_Wnd->setFramerateLimit(0);
    m_Wnd->setKeyRepeatEnabled(false);
}

void Window::mt_Destroy(void)
{
    LYS_LOG_CORE_DEBUG("Closing window");
#if 0
    ImGui::SFML::Shutdown();
#endif
    m_Wnd->close();
    m_Wnd.reset(nullptr);
}

bool Window::mt_Handle_Events(StateManager& state_manager)
{
    bool l_b_Ret = false;
    m_Wnd->handleEvents(
        [&](const sf::Event::Closed& event)
    {
        LYS_LOG_CORE_DEBUG("Closed");
        l_b_Ret = true;
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
    },
        [&](const sf::Event::Resized& event)
    {
        LYS_LOG_CORE_DEBUG("Resized");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        sf::Vector2f l_Size(event.size.x, event.size.y);
        sf::View l_Default_View = m_Wnd->getDefaultView();

        LYS_LOG_CORE_TRACE("Window size: [%.0f %.0f]", l_Size.x, l_Size.y);

        m_Wnd->setView(sf::View({ l_Size.x / 2, l_Size.y / 2 }, l_Size));
    },
        [&](const sf::Event::FocusLost& event)
    {
        LYS_LOG_CORE_DEBUG("FocusLost");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_FocusLost(WindowFocusLostEvent());
    },
        [&](const sf::Event::FocusGained& event)
    {
        LYS_LOG_CORE_DEBUG("FocusGained");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_FocusGained(WindowFocusGainedEvent());
    },
        [&](const sf::Event::TextEntered& event)
    {
        LYS_LOG_CORE_DEBUG("TextEntered");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_TextEntered(TextEvent { event.unicode });
    },
        [&](const sf::Event::KeyPressed& event)
    {
        LYS_LOG_CORE_DEBUG("KeyPressed");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_KeyPressed(KeyPressedEvent { event });
    },
        [&](const sf::Event::KeyReleased& event)
    {
        LYS_LOG_CORE_DEBUG("KeyReleased");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_KeyReleased(KeyReleasedEvent { event });
    },
        [&](const sf::Event::MouseWheelScrolled& event)
    {
        LYS_LOG_CORE_DEBUG("MouseWheelScrolled");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_MouseWheelScrolled(MouseWheelScrolledEvent { event });
    },
        [&](const sf::Event::MouseButtonPressed& event)
    {
        LYS_LOG_CORE_DEBUG("MouseButtonPressed");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_MouseButtonPressed(MouseButtonPressedEvent { sf_From(event.button), sf_From<int>(event.position) });
    },
        [&](const sf::Event::MouseButtonReleased& event)
    {
        LYS_LOG_CORE_DEBUG("MouseButtonReleased");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_MouseButtonReleased(MouseButtonReleasedEvent { sf_From(event.button), sf_From<int>(event.position) });
    },
        [&](const sf::Event::MouseMoved& event)
    {
#if 0
        LYS_LOG_CORE_DEBUG("MouseMoved");
#endif
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_MouseMoved(MouseMovedEvent { sf_From<int>(event.position) });
    },
        [&](const sf::Event::MouseMovedRaw& event)
    {
#if 0
        LYS_LOG_CORE_DEBUG("MouseMovedRaw");
#endif
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
    },
        [&](const sf::Event::MouseEntered& event)
    {
        LYS_LOG_CORE_DEBUG("MouseEntered");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
    },
        [&](const sf::Event::MouseLeft& event)
    {
        LYS_LOG_CORE_DEBUG("MouseLeft");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
    },
        [&](const sf::Event::JoystickButtonPressed& event)
    {
        LYS_LOG_CORE_DEBUG("JoystickButtonPressed");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_JoystickButtonPressed(JoystickButtonPressedEvent { event });
    },
        [&](const sf::Event::JoystickButtonReleased& event)
    {
        LYS_LOG_CORE_DEBUG("JoystickButtonReleased");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_JoystickButtonReleased(JoystickButtonReleasedEvent { event });
    },
        [&](const sf::Event::JoystickMoved& event)
    {
        LYS_LOG_CORE_DEBUG("JoystickMoved");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_JoystickMoved(JoystickMovedEvent { event });
    },
        [&](const sf::Event::JoystickConnected& event)
    {
        LYS_LOG_CORE_DEBUG("JoystickConnected");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_JoystickConnected(JoystickConnectedEvent { event });
    },
        [&](const sf::Event::JoystickDisconnected& event)
    {
        LYS_LOG_CORE_DEBUG("JoystickDisconnected");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
        state_manager.mt_On_Event_JoystickDisconnected(JoystickDisconnectedEvent { event });
    },
        [&](const sf::Event::TouchBegan& event)
    {
        LYS_LOG_CORE_DEBUG("TouchBegan");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
    },
        [&](const sf::Event::TouchMoved& event)
    {
        LYS_LOG_CORE_DEBUG("TouchMoved");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
    },
        [&](const sf::Event::TouchEnded& event)
    {
        LYS_LOG_CORE_DEBUG("TouchEnded");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
    }, [&](const sf::Event::SensorChanged& event)
    {
        LYS_LOG_CORE_DEBUG("SensorChanged");
#if 0
        ImGui::SFML::ProcessEvent(m_Wnd, sf::Event(event));
#endif
    });
    return l_b_Ret;
}

Vector2u Window::mt_Get_Size(void) const
{
    return sf_From<uint32_t, unsigned int>(m_Wnd->getSize());
}

}  // namespace lys
