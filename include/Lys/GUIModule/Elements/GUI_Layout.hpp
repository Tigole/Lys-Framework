#ifndef _GUI_LAYOUT_HPP
#define _GUI_LAYOUT_HPP 1

#include "Lys/GUIModule/GUI_Element.hpp"

#include <unordered_map>
#include <memory>
#include <vector>

namespace lys
{

namespace gui
{
#if LYS_USE_IMGUI
#else
class Interface;

class LYS_API Layout : public Element
{
public:
	Layout(const std::string& id, Interface* owner);
	void mt_OnUpdate(float delta_time_s) override;
	void mt_OnDraw(void) override;
	void mt_Add_Element(const std::string& element, const Rectf& rect);
	void mt_Redraw(void) override;
	void mt_On_Active() override;
	void mt_Set_Margin(const Vector2f& margin);

protected:
	Vector2f m_Margin;
	std::unordered_map<std::string, Rectf> m_Children;
	Interface* m_Interface;
};

#endif // 1
}

}
#endif // !_GUI_LAYOUT_HPP
