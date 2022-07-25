#ifndef _LYS_RENDERER_HPP
#define _LYS_RENDERER_HPP 1

#include "Lys/LysConfig.hpp"
#include "Lys/Core/Core.hpp"
#include "Lys/MathModule/Rect.hpp"

#include <SFML/Graphics.hpp>

namespace sf
{

class RenderWindow;

}

namespace lys
{

class Window;

struct LineSettings;
struct RectangleSettings;
struct CircleSettings;
struct HexagonSettings;
struct Sprite;
namespace gui
{
struct TextSettings;
}
struct VertexArray;
struct TextureData;



class LYS_API Renderer
{
    LYS_CLASS_NO_COPY(Renderer)
public:
    ~Renderer();

    static void smt_Create(Window* wnd);
    static void smt_Destroy(void);
    static Renderer& smt_Get(void);

public:

    void mt_Begin_Scene(float elapsed_time);

    void mt_End_Scene(void);

    void mt_Draw_Line(const LineSettings& line_settings);
    void mt_Draw_Rectangle(const RectangleSettings& rectangle_settings);
    void mt_Draw_Circle(const CircleSettings& circle_settings);
    void mt_Draw_Hexagon(const HexagonSettings& hexagon_settings);
    Rectf mt_Draw_Text(const char* text, const Vector2f& screen_pos, const gui::TextSettings& text_settings);
    void mt_Draw_VertexArray(const VertexArray& va);

    const sf::Font& mt_Get_Default_Font(void) const;

private:

    void mt_Set_Texture(sf::Shape& s, const TextureData& data);

    sf::RenderWindow* m_Wnd;

    sf::Font m_Default_Font;

    static std::unique_ptr<Renderer> sm_Renderer;
    Renderer(Window* wnd);
};

}

#endif // _LYS_RENDERER_HPP
