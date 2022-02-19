#include "Lys/GUIModule/GUI_Element.hpp"

#include "Lys/MathModule/CollisionHandling.hpp"
#include "Lys/GraphicModule/Renderer.hpp"

#include <unordered_map>



#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Lys/Core/SFML_Conversion.hpp"

#if LYS_USE_IMGUI

namespace lys
{
namespace gui
{

bool Element::mt_Is_Active(void) const
{
    return m_Is_Active;
}

void Element::mt_Set_Active(bool active)
{
    m_Is_Active = active;
}

const std::string& Element::mt_Get_Id(void) const
{
    return m_Element_Id;
}

}
}

#else
std::string fn_GUIElementState_ToString(const lys::gui::Element_State& state)
{
	std::string l_ret("");
	std::map<lys::gui::Element_State, std::string> l_map;
	std::map<lys::gui::Element_State, std::string>::iterator l_it;

	l_map[lys::gui::Element_State::Neutral] = "Neutral";
	l_map[lys::gui::Element_State::Clicked] = "Clicked";
	l_map[lys::gui::Element_State::Focused] = "Focused";

	l_it = l_map.find(state);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

lys::gui::Element_State fn_GUIElementState_ToEnum(const std::string& state)
{
	lys::gui::Element_State l_ret((lys::gui::Element_State)0xff);
	std::unordered_map<std::string, lys::gui::Element_State> l_map;
	std::unordered_map<std::string, lys::gui::Element_State>::iterator l_it;

	l_map["Neutral"] = lys::gui::Element_State::Neutral;
	l_map["Clicked"] = lys::gui::Element_State::Clicked;
	l_map["Focused"] = lys::gui::Element_State::Focused;

	l_it = l_map.find(state);
	if (l_it != l_map.end())
	{
		l_ret = l_it->second;
	}

	return l_ret;
}

#endif // 1


namespace lys
{

namespace gui
{

#if LYS_USE_IMGUI



#else
Element::Element(const std::string& id, Element* owner) :
    m_Id(id), m_Owner(owner), m_Current_State(Element_State::Neutral)
{}

void Element::mt_Set_Allocation(const Rectf& rect)
{
	m_Allocation = rect;
}

void Element::mt_Set_Style(const Element_State& state, const Style& style)
{
	m_Styles.emplace(std::make_pair(state, style));
}

void Element::mt_Set_State(const Element_State& state)
{
    m_Current_State = state;
}

Element_State Element::mt_Get_State(void) const
{
	return m_Current_State;
}

void Element::mt_On_Click([[maybe_unused]]const Vector2f& mousePos)
{
	mt_Set_State(Element_State::Clicked);
}

void Element::mt_On_Release(const Vector2f& mousePos)
{
	if (mt_Is_Inside(mousePos) == true)
	{
		mt_Set_State(Element_State::Focused);
	}
	else
	{
		mt_Set_State(Element_State::Neutral);
	}
}

void Element::mt_On_Hover(const Vector2f& mousePos)
{
	if (m_Current_State != Element_State::Clicked)
	{
		bool l_is_inside(mt_Is_Inside(mousePos));

		if (l_is_inside == true)
		{
			mt_Set_State(Element_State::Focused);
		}
		else
		{
			mt_Set_State(Element_State::Neutral);
		}
	}
}

const Rectf& Element::mt_Get_Screen_Space(void) const
{
	return m_Allocation;
}

Vector2f Element::mt_Get_Required_Space(void) const
{
	Vector2f l_ret(0, 0);

	return l_ret;
}

bool Element::mt_Is_Inside(const Vector2f& position)
{
	return fn_Check_Collision_Point_Rect(position, mt_Get_Screen_Space());
}

const std::string& Element::mt_Get_Id(void) const
{
	return m_Id;
}

Vector2f Element::mt_Get_Screen_Position(void) const
{
	Vector2f l_Ret(m_Allocation.m_Top_Left.x, m_Allocation.m_Top_Left.y);

	if (m_Owner != nullptr)
	{
		l_Ret += m_Owner->mt_Get_Screen_Position();
	}

	return l_Ret;
}

void Element::mt_Redraw(void) {}

const Style* Element::mt_Get_Current_Style(void) const
{
    const Style* l_Style = nullptr;
    auto l_it = m_Styles.find(m_Current_State);

    if (l_it != m_Styles.end())
    {
        l_Style = &l_it->second;
    }

    return l_Style;
}


Vector2f Element::smt_Get_Text_Size(const std::string& text, const TextSettings& style)
{
    sf::Text l_Text;
    sf::FloatRect l_Bounds;

    l_Text.setString(text);
    l_Text.setFont(Renderer::smt_Get().mt_Get_Default_Font());
    l_Text.setCharacterSize(style.m_Character_Size);
    l_Text.setStyle(sf_To(style.m_Style));

    l_Bounds = l_Text.getGlobalBounds();

    l_Bounds = l_Text.getLocalBounds();

    return Vector2f(l_Bounds.width, l_Bounds.height);
}

#endif

}

}
