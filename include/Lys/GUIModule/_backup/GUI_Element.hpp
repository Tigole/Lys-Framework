#ifndef _LYS_GUI_ELEMENT_HPP
#define _LYS_GUI_ELEMENT_HPP 1

#include "GUI_Style.hpp"
#include "Lys/MathModule/Rect.hpp"
#include "Lys/GraphicModule/Renderer.hpp"
#include "Lys/GraphicModule/DrawCommandSettings.hpp"

#include <map>

namespace lys
{

namespace gui
{

enum class ElementState
{
    Neutral,
    Focused,
    Clicked
};

struct BackgroundStyle
{
    Color m_Fill_Color;
    Color m_Outline_Color;
    float m_Outline_Thickness;
};

struct ElementStyle
{
    BackgroundStyle m_Background;
    TextSettings m_Text;
};

class Element
{
public:
    Element();

    virtual void mt_OnUpdate(float elapsed_time);

    bool mt_OnMouseMove(const Vector2f& screen_pos);
    bool mt_OnMouseClick(const Vector2f& screen_pos);
    bool mt_OnMouseRelease(const Vector2f& screen_pos);

    virtual void mt_Set_Position(const Vector2f& pos);
    virtual void mt_Set_Size(const Vector2f& size);
    void mt_Set_Area(const Rectf& area);

    Vector2f mt_Get_Position(void) const;
    Vector2f mt_Get_Size(void) const;
    Vector2f mt_Get_Required_Size(void) const;
    Rectf mt_Get_Area(void) const;

    virtual void mt_Redraw(void);

    void mt_Set_Parent(Element* parent);

protected:
    Element* m_Parent;

    void mt_Set_State(ElementState state);
    ElementState m_Current_State;

    void mt_Add_Style(ElementState state, const ElementStyle& style);
    void mt_Add_Style(ElementState state,
                      TextOriginMode x_origin_mode, TextOriginMode y_origin_mode,
                      TextStyle style, unsigned int character_size, const Color& fill_color, const Color& outline_color, float outline_thickness,
                      const Color& background_fill_color, const Color& background_outline_color, float background_outline_thickness);
    void mt_Apply_Style(const ElementStyle& style);
    ElementStyle mt_Get_Style(void) const;

private:
    std::map<ElementState, ElementStyle> m_Styles;

protected:
    Vector2f m_Position;
    Vector2f m_Size;
    Vector2f m_Required_Size;

    static Vector2f smt_Get_Text_Size(const std::string& text, const TextSettings& style);
};

}

}

#endif // _LYS_GUI_ELEMENT_HPP
