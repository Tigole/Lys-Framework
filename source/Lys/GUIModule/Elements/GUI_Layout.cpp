#include "Lys/GUIModule/Elements/GUI_Layout.hpp"
#include "Lys/GUIModule/GUI_Interface.hpp"

namespace lys
{

namespace gui
{
#if LYS_USE_IMGUI

#else
Layout::Layout(const std::string& id, Interface* owner) :
    Element(id, owner),
	m_Interface(owner)
{}

void Layout::mt_OnUpdate(float delta_time_s)
{
	//
}

void Layout::mt_OnDraw(void)
{
	//
}

void Layout::mt_On_Active()
{
	mt_Set_State(Element_State::Neutral);
}

void Layout::mt_Add_Element(const std::string& element, const Rectf& rect)
{
	m_Children.emplace(element, rect);
}

void Layout::mt_Redraw(void)
{
	Vector2f l_Required_Space(0.0f, 0.0f), l_Tmp;
	Rectf l_Allocation;
	std::unordered_map<Element*, Rectf> l_Children;

	for (auto& el : m_Children)
	{
		l_Children.emplace(m_Interface->mt_Get_Element(el.first), el.second);
	}

	for (auto& el : l_Children)
	{
		l_Tmp = el.first->mt_Get_Required_Space();

		l_Required_Space.x = std::max(l_Tmp.x, l_Required_Space.x);
		l_Required_Space.y = std::max(l_Tmp.y, l_Required_Space.y);
	}

	for (auto& el : l_Children)
	{
		l_Allocation.m_Width_Height.x = l_Required_Space.x * el.second.m_Width_Height.x;
		if (el.second.m_Width_Height.x > 1)
			l_Allocation.m_Width_Height.x += m_Margin.x;
		l_Allocation.m_Width_Height.y = l_Required_Space.y * el.second.m_Width_Height.y;
		if (el.second.m_Width_Height.y > 1)
			l_Allocation.m_Width_Height.y += m_Margin.y;

		l_Allocation.m_Top_Left.x = m_Allocation.m_Top_Left.x + (l_Required_Space.x + m_Margin.x) * el.second.m_Top_Left.x;
		l_Allocation.m_Top_Left.y = m_Allocation.m_Top_Left.y + (l_Required_Space.y + m_Margin.y) * el.second.m_Top_Left.y;
		/*if (el.second.top != 0)
			l_Allocation.top += m_Margin.y;*/

		el.first->mt_Set_Allocation(l_Allocation);
	}

	for (auto& el : l_Children)
	{
		el.first->mt_Redraw();
	}
}

void Layout::mt_Set_Margin(const Vector2f& margin)
{
	m_Margin = margin;
}

#endif // 1
}

}
