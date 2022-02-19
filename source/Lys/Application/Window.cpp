#include "Lys/Application/Window.hpp"

#include "Lys/Core/SFML_Conversion.hpp"
#include "Lys/Core/Log.hpp"

#include <windows.h>

#if LYS_USE_IMGUI
#include "imgui-SFML.h"
#endif // LYS_USE_IMGUI

namespace lys
{

WindowSettings::WindowSettings(const char* title, const sf::VideoMode& vm, bool full_screen) :
    m_Title(title),
    m_VideoMode(vm),
    m_Full_Screen(full_screen)
{}



void Window::mt_Create(const WindowSettings& settings)
{
    m_Wnd.create(settings.m_VideoMode, settings.m_Title, (settings.m_Full_Screen == true) ? sf::Style::Fullscreen : sf::Style::Default);

    if (settings.m_VideoMode == sf::VideoMode::getDesktopMode())
    {
        ShowWindow(m_Wnd.getSystemHandle(), SW_MAXIMIZE);
    }

#if LYS_USE_IMGUI
    ImGui::SFML::Init(m_Wnd, true);
#endif // LYS_USE_IMGUI

    m_Wnd.setFramerateLimit(0);
    m_Wnd.setKeyRepeatEnabled(false);
}

bool Window::mt_Poll_Event(Event& event)
{
    bool l_b_Ret = m_Wnd.pollEvent(event.m_SFML);

    if (event.m_SFML.type == sf::Event::Resized)
    {
        sf::Vector2f l_Size(event.m_SFML.size.width, event.m_SFML.size.height);
        sf::View l_Default_View = m_Wnd.getDefaultView();

        LYS_LOG_CORE_TRACE("Window size: [%.0f %.0f]", l_Size.x, l_Size.y);

        m_Wnd.setView(sf::View({l_Size.x / 2, l_Size.y / 2}, l_Size));
    }

#if LYS_USE_IMGUI
    ImGui::SFML::ProcessEvent(event.m_SFML);
#endif // LYS_USE_IMGUI

    return l_b_Ret;
}

Vector2u Window::mt_Get_Size(void) const
{
    return sf_From<uint32_t, unsigned int>(m_Wnd.getSize());
}


/*
void Window_SFML::mt_Initialize(const sf::VideoMode& vm, bool full_screen)
{
    sf::String l_Title("Lithomancia - JDR");

    //m_Wnd.create(vm, "Lithomancia - JDR " + VERSION_STR + " (" + std::to_string(VERSION) + ")", (full_screen == true) ? sf::Style::Fullscreen : sf::Style::Default);
    m_Wnd.create(vm, l_Title, (full_screen == true) ? sf::Style::Fullscreen : sf::Style::Default);

    ImGui::SFML::Init(m_Wnd, true);

    m_Current_Zoom = 1.0f;

    mt_Add_Event_Callback(sf::Event::MouseWheelScrolled, &Window_SFML::mt_Handle_Zoom, this, true);
}

bool Window_SFML::mt_Poll_Event(sf::Event& event)
{
    PROFILE_FUNCTION();
    bool l_Ret = m_Wnd.pollEvent(event);

    if (m_Wnd.hasFocus() == false)
    {
        l_Ret = false;
    }

    if (l_Ret == true)
    {
        if (event.type == sf::Event::GainedFocus)
        {
            m_Old_Mouse_Pos = sf::Mouse::getPosition(m_Wnd);
        }
        else if (event.type == sf::Event::Resized)
        {
            sf::Vector2f l_Size(event.size.width, event.size.height);
            sf::View l_Default_View = m_Wnd.getDefaultView();

            m_Wnd.setView(sf::View({l_Size.x / 2, l_Size.y / 2}, l_Size));
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            //
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            //
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f l_Current_Pos(event.mouseMove.x, event.mouseMove.y);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                sf::View l_View = m_Wnd.getView();

                l_View.move((m_Old_Mouse_Pos - l_Current_Pos) * m_Current_Zoom);

                m_Wnd.setView(l_View);
            }

            m_Old_Mouse_Pos = l_Current_Pos;
        }

        {
            PROFILE_SCOPE("Callbacks");

            auto l_Callbacks = m_Callbacks[event.type];
            for (auto& cb : l_Callbacks)
            {
                Callback& l_cb = cb.second;

                if (l_cb.m_Active == true)
                {
                    l_cb.m_Callback(event);
                }
            }
        }

        {
            PROFILE_SCOPE("ImGui");
            ImGui::SFML::ProcessEvent(event);
        }
    }

    if (event.type == sf::Event::LostFocus)
    {
        ImGui::SFML::ProcessEvent(event);
    }

    return l_Ret;
}

sf::Vector2i Window_SFML::mt_Get_Mouse_Position_Raw(void)
{
    return sf::Mouse::getPosition();
}

sf::Vector2f Window_SFML::mt_Get_Mouse_Position_World(void)
{
    return m_Wnd.mapPixelToCoords(sf::Mouse::getPosition(m_Wnd));
}


void Window_SFML::mt_Handle_Zoom(const sf::Event& event)
{
    const sf::Event::MouseWheelScrollEvent& l_Scroll = event.mouseWheelScroll;
    sf::View l_View = m_Wnd.getView();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        if (l_Scroll.delta > 0.0f)
        {
            m_Current_Zoom *= 0.9;
            l_View.zoom(0.9f);
        }
        else if (l_Scroll.delta < 0.0f)
        {
            m_Current_Zoom *= 1.1f;
            l_View.zoom(1.1f);
        }
        m_Wnd.setView(l_View);
    }
}*/




}
