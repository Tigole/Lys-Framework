#ifndef _LYS_WINDOW_HPP
#define _LYS_WINDOW_HPP 1

#include <SFML/Graphics.hpp>

#include "Event.hpp"
#include "Lys/Core/Singleton.hpp"
#include "Lys/MathModule/Vector2.hpp"

namespace lys
{

class Renderer;
class StateManager;

struct LYS_API WindowSettings
{
    WindowSettings(const char* title, const sf::VideoMode& vm, bool full_screen);

    const char* m_Title;
    sf::VideoMode m_VideoMode;
    bool m_Full_Screen;
};

class LYS_API Window
{
    friend Renderer;

public:
    static Window& smt_Get(void);

    void mt_Create(const WindowSettings& settings);
    void mt_Destroy(void);

    bool mt_Handle_Events(StateManager& state_manager);

    Vector2u mt_Get_Size(void) const;

private:
    Window();

    sf::RenderWindow m_Wnd;
};

}  // namespace lys

#endif  // _LYS_WINDOW_HPP
