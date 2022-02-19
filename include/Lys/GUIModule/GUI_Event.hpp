#ifndef _GUI_EVENT_HPP
#define _GUI_EVENT_HPP 1

#include <string>


#if LYS_USE_IMGUI

namespace lys
{
namespace gui
{
enum class GUIEventType
{
    None,
    BtnClicked,
};

struct BtnClicked
{
    BtnClicked() : m_Interface_Id(), m_Button_Id(){}
    BtnClicked(const std::string& interface_id, const std::string btn_id) : m_Interface_Id(interface_id), m_Button_Id(btn_id){}
    bool mt_Is_Valid(const std::string& interface_id, const std::string& btn_id)
    {
        return m_Interface_Id == interface_id && m_Button_Id == btn_id;
    }
    std::string m_Interface_Id;
    std::string m_Button_Id;
};

struct GUIEvent
{
    GUIEvent() : m_Type(GUIEventType::None), m_Btn_Clicked() {}
    GUIEvent(const BtnClicked& b) : m_Type(GUIEventType::BtnClicked), m_Btn_Clicked(b) {}

    GUIEventType m_Type;

    BtnClicked m_Btn_Clicked;
};

}
}

#else
enum class EventDataGUIType
{
	None,
	Clicked,
	Released,
	Hover,
};

struct EventDataGUI
{
	EventDataGUI() : m_type(EventDataGUIType::None), m_interface_id(), m_element_id() {}

	EventDataGUIType m_type;
	std::string m_interface_id;
	std::string m_element_id;
};

#endif // LYS_USE_IMGUI

#endif // !_GUI_EVENT_HPP
