#include "Lys/Application/Window.hpp"

#include "Lys/Core/SFML_Conversion.hpp"
#include "Lys/Core/Log.hpp"

#if (PLATFORM == PLATFORM_WINDOWS)
    #include <windows.h>
#endif

#include "imgui-SFML.h"

namespace lys
{

WindowSettings::WindowSettings(const char* title, const sf::VideoMode& vm, bool full_screen) :
    m_Title(title),
    m_VideoMode(vm),
    m_Full_Screen(full_screen)
{}


Window& Window::smt_Get(void)
{
    static Window ls_Singleton;

    return ls_Singleton;
}


Window::Window() :
    m_Wnd()
{}

void Window::mt_Create(const WindowSettings& settings)
{
    m_Wnd.create(settings.m_VideoMode, settings.m_Title, (settings.m_Full_Screen == true) ? sf::Style::Fullscreen : sf::Style::Default);

#if (PLATFORM == PLATFORM_WINDOWS)
    if (settings.m_VideoMode == sf::VideoMode::getDesktopMode())
    {
        ShowWindow(m_Wnd.getNativeHandle(), SW_MAXIMIZE);
    }
#endif

    ImGui::SFML::Init(m_Wnd, true);

    m_Wnd.setFramerateLimit(0);
    m_Wnd.setKeyRepeatEnabled(false);
}

void Window::mt_Destroy(void)
{
    LYS_LOG_CORE_DEBUG("Closing window");
    ImGui::SFML::Shutdown();
    m_Wnd.close();
}

bool Window::mt_Poll_Event(Event& event)
{
    bool l_b_Ret = m_Wnd.pollEvent(event.m_SFML);

    if (l_b_Ret == true)
    {
        if (event.m_SFML.type == sf::Event::Resized)
        {
            sf::Vector2f l_Size(event.m_SFML.size.width, event.m_SFML.size.height);
            sf::View l_Default_View = m_Wnd.getDefaultView();

            LYS_LOG_CORE_TRACE("Window size: [%.0f %.0f]", l_Size.x, l_Size.y);

            m_Wnd.setView(sf::View({l_Size.x / 2, l_Size.y / 2}, l_Size));
        }

        ImGui::SFML::ProcessEvent(m_Wnd, event.m_SFML);
    }

    return l_b_Ret;
}

Vector2u Window::mt_Get_Size(void) const
{
    return sf_From<uint32_t, unsigned int>(m_Wnd.getSize());
}

}
