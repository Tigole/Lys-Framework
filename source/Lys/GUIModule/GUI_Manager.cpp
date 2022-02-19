#include "Lys/GUIModule/GUI_Manager.hpp"


#include "XMLFileLoader.hpp"
#include "Lys/GUIModule/GUI_Manager_Loader.hpp"
#include "Lys/GUIModule/GUI_Interface.hpp"

#include "Lys/Application/Event.hpp"

namespace lys
{

namespace gui
{
#if LYS_USE_IMGUI



Manager::Manager() :
    m_Interfaces(),
    m_Mouse_Captured(false),
    m_Keyboard_Captured(false),
    m_Text_Captured(false),
    m_Events_Queue()
{}

void Manager::mt_Push_Interface(Interface* interface)
{
    m_Interfaces.emplace(interface->mt_Get_Id(), interface);
}

bool Manager::mt_Handled_Event(const Event& event)
{
    bool l_b_Ret = false;

    if (    (event.m_SFML.type == sf::Event::MouseButtonPressed)
        ||  (event.m_SFML.type == sf::Event::MouseButtonReleased))
    {
        l_b_Ret = m_Mouse_Captured;
    }
    else if (   (event.m_SFML.type == sf::Event::KeyPressed)
             || (event.m_SFML.type == sf::Event::KeyReleased))
    {
        l_b_Ret = m_Keyboard_Captured;
    }
    else if (event.m_SFML.type == sf::Event::TextEntered)
    {
        l_b_Ret = m_Text_Captured;
    }

    return l_b_Ret;
}

void Manager::mt_OnUpdate(float elapsed_time)
{
    const ImGuiIO& io = ImGui::GetIO();

    for (auto& i : m_Interfaces)
    {
        if (i.second->mt_Is_Active())
        {
            i.second->mt_OnUpdate(elapsed_time);
        }
    }

    m_Mouse_Captured = io.WantCaptureMouse;
    m_Keyboard_Captured = io.WantCaptureKeyboard;
    m_Text_Captured = io.WantTextInput;
}

bool Manager::mt_Poll_Event(GUIEvent& e)
{
    bool l_b_Ret = false;

    if (m_Events_Queue.size() > 0)
    {
        e = m_Events_Queue.front();
        m_Events_Queue.pop();
        l_b_Ret = true;
    }

    return l_b_Ret;
}

void Manager::mt_Push_Event(const BtnClicked& btn_clicked)
{
    m_Events_Queue.push(GUIEvent(btn_clicked));
}



#else

int Manager::ms_mouse_elevation = 5000;

Manager::Manager() :
    m_Interfaces(),
    m_Styles()
{}

void Manager::mt_Add_Style(const std::string& style_id, const Element_State& state, const Style& style)
{
	auto l_style = m_Styles.find(style_id);

	if (l_style == m_Styles.end())
	{
		l_style = m_Styles.emplace(style_id, StyleState()).first;
	}

	l_style->second.emplace(state, style);
}

const StyleState* Manager::mt_Get_Style(const std::string& style_id) const
{
	const StyleState* l_ret(nullptr);
	auto l_style = m_Styles.find(style_id);

	if (l_style != m_Styles.end())
	{
		l_ret = &l_style->second;
	}

	return l_ret;
}

void Manager::mt_Push_Interface(const std::string& interface_id, Interface* inter)
{
	m_Interfaces.emplace(interface_id, inter);
}

Interface* Manager::mt_Get_Interface(const std::string& interface_id)
{
	Interface* l_Ret(nullptr);
	auto l_it = m_Interfaces.find(interface_id);

	if (l_it != m_Interfaces.end())
    {
        l_Ret = l_it->second;
    }

	return l_Ret;
}

/*void Manager::mt_Add_Event(const EventDataGUI& gui_event)
{
	m_events[m_current_state].push(gui_event);
}

bool Manager::mt_Poll_Event(EventDataGUI& gui_event)
{
	bool l_b_ret(false);
	if (m_events[m_current_state].size() != 0)
	{
		gui_event = m_events[m_current_state].top();
		m_events[m_current_state].pop();
		l_b_ret = true;
	}
	return l_b_ret;
}*/

/*void Manager::mt_Load_Interfaces(const std::string& conf_file)
{
	XMLFileLoader l_xml_loader;

	l_xml_loader.mt_Set_File(conf_file);
	l_xml_loader.mt_Add_On_Entry_Callback(conf_file, "/Interfaces/Interface", &GUI_Manager::mt_Load_Path, this);

	l_xml_loader.mt_Start();
	l_xml_loader.mt_Wait_For_Ending(100);
}

void Manager::mt_Load_Styles(const std::string& conf_file)
{
	GUI_Manager_Style_Loader l_loader;
	XMLFileLoader l_xml_loader;

	l_loader.mt_Prepare(conf_file, l_xml_loader, this);

	l_xml_loader.mt_Start();
	l_xml_loader.mt_Wait_For_Ending(100);
}*/

void Manager::mt_On_Mouse_Move(const Vector2f& mouse_pos)
{
    for (auto& l_interface : m_Interfaces)
    {
        if (l_interface.second->mt_Is_Active() == true)
        {
            l_interface.second->mt_On_Hover(mouse_pos);
        }
    }
}

void Manager::mt_On_Mouse_Click(const Vector2f& mouse_pos)
{
    for (auto& l_interface : m_Interfaces)
    {
        if (l_interface.second->mt_Is_Active() == true)
        {
            l_interface.second->mt_On_Click(mouse_pos);
        }
    }
}

void Manager::mt_On_Mouse_Release(const Vector2f& mouse_pos)
{
    for (auto& l_interface : m_Interfaces)
    {
        if (l_interface.second->mt_Is_Active() == true)
        {
            l_interface.second->mt_On_Release(mouse_pos);
        }
    }
}

void Manager::mt_On_Text_Entered(void)
{
	//
}

void Manager::mt_On_Key_Navigation(void)
{
	//
}

void Manager::mt_OnUpdate(float delta_time_s)
{
    for (auto& l_interface : m_Interfaces)
    {
        if (l_interface.second->mt_Is_Active() == true)
        {
            l_interface.second->mt_OnUpdate(delta_time_s);
        }
    }
}

void Manager::mt_OnDraw(void)
{
    for (auto& l_interface : m_Interfaces)
    {
        if (l_interface.second->mt_Is_Active() == true)
        {
            l_interface.second->mt_OnDraw();
        }
    }
}

/*bool Manager::mt_Load_Path(const XML_Element& element)
{
	bool l_b_ret;
	std::string l_id;
	std::string l_path;
	GameStateType l_game_state;

	l_b_ret = element.mt_Get_Attribute("id", l_id);

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute("path", l_path);
	}

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute<GameStateType>("game_state", l_game_state, fn_GameStateType_ToEnum);
	}

	if (l_b_ret == true)
	{
		m_paths[l_game_state].emplace(l_id, l_path);
	}

	return l_b_ret;
}*/
#endif // LYS_USE_IMGUI

}

}
