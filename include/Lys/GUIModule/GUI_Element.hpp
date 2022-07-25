#ifndef _GUI_ELEMENT_HPP
#define _GUI_ELEMENT_HPP 1

#include "GUI_Styles.hpp"
#include "Lys/MathModule/Rect.hpp"
#include "GUI_Manager.hpp"

#include <string>
#include <map>


#if LYS_USE_IMGUI
#include "imgui.h"
#endif // LYS_USE_IMGUI

namespace lys
{

namespace gui
{
#if LYS_USE_IMGUI

class Interface_Predefined;

class Element
{
    friend Interface_Predefined;
public:

    virtual void mt_OnUpdate(float elapsed_time) = 0;

    bool mt_Is_Active(void) const;
    void mt_Set_Active(bool active);

    const std::string& mt_Get_Id(void) const;

protected:
    const std::string* m_Interface_Id;
    std::string m_Element_Id;
    bool m_Is_Active = true;
};

#else

class Interface;

/*struct Data
{
	sf::Vector2u m_size;

};*/

enum class Element_State
{
	Neutral,
	Focused,
	Clicked,
};


using StateStyles = std::map<Element_State, Style>;

class LYS_API Element
{
public:
	Element(const std::string& id, Element* owner);
	virtual ~Element(){}
	Element(const Element&) = delete;
	Element& operator=(const Element&) = delete;

	virtual void mt_OnUpdate(float delta_time_s) = 0;
	virtual void mt_OnDraw(void) = 0;

	void mt_Set_Style(const Element_State& state, const Style& style);
	void mt_Set_State(const Element_State& state);
	Element_State mt_Get_State(void) const;

	virtual void mt_On_Click(const Vector2f& mousePos);
	virtual void mt_On_Release(const Vector2f& mousePos);
	virtual void mt_On_Hover(const Vector2f& mousePos);
	virtual void mt_On_Leave() {}
	virtual void mt_On_Focus() {}
	virtual void mt_On_Defocus() {}
	virtual void mt_On_Active() { mt_Set_State(Element_State::Neutral); }
	virtual void mt_On_Deactive() { mt_Set_State(Element_State::Neutral); }

	bool mt_Is_Inside(const Vector2f& position);

	void mt_Set_Id(const std::string& id);
	const std::string& mt_Get_Id(void) const;

	void mt_Set_Allocation(const Rectf& rect);
	Vector2f mt_Get_Screen_Position(void) const;
	const Rectf& mt_Get_Screen_Space(void) const;

	virtual Vector2f mt_Get_Required_Space(void) const;

	virtual void mt_Redraw(void);

protected:

    const Style* mt_Get_Current_Style(void) const;

	Rectf m_Allocation;
	std::string m_Id;

	StateStyles m_Styles;
	Element_State m_Current_State;
	Element* m_Owner;

    static Vector2f smt_Get_Text_Size(const std::string& text, const TextSettings& style);
};
#endif // 1
}

}

#if LYS_USE_IMGUI
#else
std::string fn_GUIElementState_ToString(const lys::gui::Element_State& state);
lys::gui::Element_State fn_GUIElementState_ToEnum(const std::string& state);
#endif // LYS_USE_IMGUI

#endif // !_GUI_ELEMENT_HPP
