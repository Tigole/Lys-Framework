#ifndef _GUI_BUTTON_HPP
#define _GUI_BUTTON_HPP 1

#include "Lys/GUIModule/GUI_Element.hpp"

#if 0
namespace lys
{

namespace gui
{
#if LYS_USE_IMGUI

class Button : public Element
{
public:
    Button(const std::string& text);

    void mt_OnUpdate(float elapsed_time) override;

    void mt_Set_Text(const std::string& text);
    const std::string& mt_Get_Text(void) const;

private:
    bool m_Is_Clicked;
    bool m_Is_Hovered;
    std::string m_Text;
};


#else
class LYS_API Button : public Element
{
public:
	Button(const std::string& id, const std::string& text, Element* owner);

	void mt_Set_Text(const std::string& text);

	void mt_OnUpdate(float delta_time_s) override;
	void mt_OnDraw(void) override;

	Vector2f mt_Get_Required_Space(void) const override;

private:
    std::string m_Text;
    Vector2f m_Required_Space;
};
#endif // 1

}

}
#endif // 0

#endif // !_GUI_BUTTON_HPP
