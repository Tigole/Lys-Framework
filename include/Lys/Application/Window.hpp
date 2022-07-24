#ifndef _LYS_WINDOW_HPP
#define _LYS_WINDOW_HPP 1

#include "Lys/MathModule/Vector2.hpp"
#include "Event.hpp"
#include "Lys/Core/Singleton.hpp"

#include <SFML/Graphics.hpp>

namespace lys
{

class Renderer;

struct WindowSettings
{
    WindowSettings(const char* title, const sf::VideoMode& vm, bool full_screen);

    const char* m_Title;
    sf::VideoMode m_VideoMode;
    bool m_Full_Screen;
};


class Window
{
    friend Renderer;
public:

    static Window& smt_Get(void);

    void mt_Create(const WindowSettings& settings);
    bool mt_Poll_Event(Event& event);

    Vector2u mt_Get_Size(void) const;

private:

    Window();

    sf::RenderWindow m_Wnd;
};

}


#endif // _LYS_WINDOW_HPP
