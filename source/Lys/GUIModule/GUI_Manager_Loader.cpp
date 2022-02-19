#include "GUI_Manager_Loader.hpp"
/*
#include "XMLFileLoader.hpp"
#include "GUI_Manager.hpp"

#include "GUI_Element.hpp"
#include "Elements/GUI_Button.hpp"
#include "Elements/GUI_Layout.hpp"
#include "GUI_Interface.hpp"

#include "Environment.hpp"

GUI_Manager_Interface_Loader::~GUI_Manager_Interface_Loader()
{
	for (auto& el : m_elements)
		delete el;
}

void GUI_Manager_Interface_Loader::mt_Prepare(const std::string& file_name, XMLFileLoader& loader, GUI_Manager* target)
{
	m_target = target;

	loader.mt_Set_File(file_name);
	loader.mt_Add_On_Entry_Callback(file_name, "/Interface", &GUI_Manager_Interface_Loader::mt_Load_Interface, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Interface/Button", &GUI_Manager_Interface_Loader::mt_Load_Button, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Interface/Layout", &GUI_Manager_Interface_Loader::mt_Load_Layout, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Interface/Layout/Button", &GUI_Manager_Interface_Loader::mt_Load_Layout_Button, this);

	loader.mt_Add_On_Exit_Callback(file_name, "/Interface", &GUI_Manager_Interface_Loader::mt_Finalize_Interface, this);
	loader.mt_Add_On_Exit_Callback(file_name, "/Interface/Layout", &GUI_Manager_Interface_Loader::mt_Finalize_Layout, this);
}

bool GUI_Manager_Interface_Loader::mt_Load_Button(const XML_Element& button)
{
	bool l_b_ret(false);
	GUI_Button* l_button;

	l_button = mt_Load_Button_From_Element(button, m_interface);

	if (l_button != nullptr)
	{
		m_interface->mt_Add_Element(l_button);
		l_b_ret = true;
	}

	return l_b_ret;
}

bool GUI_Manager_Interface_Loader::mt_Load_Interface(const XML_Element& element)
{
	bool l_b_ret(false);
	std::string l_id;

	l_b_ret = element.mt_Get_Attribute("id", l_id);

	if (l_b_ret == true)
	{
		m_interface = new GUI_Interface(l_id, m_target);
	}

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute<GameStateType>("game_state", m_game_state, &fn_GameStateType_ToEnum);
	}

	return l_b_ret;
}

bool GUI_Manager_Interface_Loader::mt_Finalize_Interface(const XML_Element& element)
{
	bool l_b_ret(false);

	if (m_interface != nullptr)
	{
		m_target->mt_Add_Interface(m_game_state, m_interface);

		l_b_ret = true;
	}

	return l_b_ret;
}

bool GUI_Manager_Interface_Loader::mt_Load_Layout(const XML_Element& layout)
{
	bool l_b_ret;
	sf::FloatRect l_allocation;
	std::string l_text_id;
	std::string l_id;
	sf::Vector2f l_margin;

	l_b_ret = layout.mt_Get_Attribute("id", l_id);

	if (l_b_ret == true)
	{
		l_b_ret = layout.mt_Get_Attribute("text_id", l_text_id);
	}

	if (l_b_ret == true)
	{
		l_b_ret = mt_Load_Allocation(layout, l_allocation);
	}

	if (l_b_ret == true)
	{
		l_b_ret = mt_Load_Margin(layout, l_margin);
	}

	if (l_b_ret == true)
	{
		m_layout = new GUI_Layout(l_id, m_interface);

		l_b_ret = (m_layout != nullptr);
	}

	if (l_b_ret == true)
	{
		m_layout->mt_Set_Margin(l_margin);
		m_layout->mt_Set_Allocation(l_allocation);
		m_layout->mt_Set_Text(m_target->mt_Get_Environment()->m_string_manager.mt_Get_String(m_target->mt_Get_Environment()->m_string_manager.mt_Get_Current_Lang(), l_text_id));
	}

	return l_b_ret;
}

bool GUI_Manager_Interface_Loader::mt_Finalize_Layout(const XML_Element& layout)
{
	bool l_b_ret(true);

	m_interface->mt_Add_Element(m_layout);

	return l_b_ret;
}

bool GUI_Manager_Interface_Loader::mt_Load_Layout_Button(const XML_Element& button)
{
	bool l_b_ret;
	sf::FloatRect l_allocation;
	GUI_Button* l_button(nullptr);

	l_button = mt_Load_Button_From_Element(button, m_layout);

	if (l_button != nullptr)
	{
		m_layout->mt_Add_Element(l_button->mt_Get_Id(), l_button->mt_Get_Screen_Space());
		m_interface->mt_Add_Element(l_button);

		l_b_ret = true;
	}
	else
	{
		l_b_ret = false;
	}

	return l_b_ret;
}

GUI_Button* GUI_Manager_Interface_Loader::mt_Load_Button_From_Element(const XML_Element& button, GUI_Element* owner)
{
	bool l_b_ret(false);
	std::string l_id;
	std::string text_id;
	std::string l_style_id;
	GUI_Button* l_button(nullptr);
	const Style* l_style(nullptr);
	sf::FloatRect l_allocation;

	l_b_ret = button.mt_Get_Attribute("id", l_id);

	if (l_b_ret == true)
	{
		l_b_ret = button.mt_Get_Attribute("text_id", text_id);
	}

	if (l_b_ret == true)
	{
		l_b_ret = button.mt_Get_Attribute("style_id", l_style_id);
	}

	if (l_b_ret == true)
	{
		l_b_ret = mt_Load_Allocation(button, l_allocation);
	}

	if (l_b_ret == true)
	{
		l_style = m_target->mt_Get_Style(l_style_id);

		l_b_ret = (l_style != nullptr);
	}

	if (l_b_ret == true)
	{
		l_button = new GUI_Button(l_id, owner);

		l_button->mt_Set_Text(m_target->mt_Get_Environment()->m_string_manager.mt_Get_String(m_target->mt_Get_Environment()->m_string_manager.mt_Get_Current_Lang(), text_id));
		l_button->mt_Set_Allocation(l_allocation);

		for (auto& s : *l_style)
		{
			l_button->mt_Set_Style(s.first, s.second);
		}
	}

	return l_button;
}

bool GUI_Manager_Interface_Loader::mt_Load_Allocation(const XML_Element& element, sf::FloatRect& rect)
{
	bool l_b_ret;

	l_b_ret = element.mt_Get_Attribute("x_pos", rect.left);

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute("y_pos", rect.top);
	}

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute("x_size", rect.width);
	}

	if (l_b_ret == true)
	{
		l_b_ret = element.mt_Get_Attribute("y_size", rect.height);
	}

	return l_b_ret;
}

bool GUI_Manager_Interface_Loader::mt_Load_Margin(const XML_Element& element, sf::Vector2f& margin)
{
	bool l_b_ret;

	l_b_ret = element.mt_Get_Attribute("x_margin", margin.x) && element.mt_Get_Attribute("y_margin", margin.y);

	return l_b_ret;
}







GUI_Manager_Style_Loader::~GUI_Manager_Style_Loader()
{}

void GUI_Manager_Style_Loader::mt_Prepare(const std::string& file_name, XMLFileLoader& loader, GUI_Manager* target)
{
	m_target = target;

	loader.mt_Set_File(file_name);

	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style", &GUI_Manager_Style_Loader::mt_Load_Style, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style/State", &GUI_Manager_Style_Loader::mt_Load_State, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style/State/Text", &GUI_Manager_Style_Loader::mt_Load_Text, this);
	loader.mt_Add_On_Entry_Callback(file_name, "/Styles/Style/State/Background", &GUI_Manager_Style_Loader::mt_Load_Background, this);

	loader.mt_Add_On_Exit_Callback(file_name, "/Styles/Style/State", &GUI_Manager_Style_Loader::mt_Finalize_State, this);
}

bool GUI_Manager_Style_Loader::mt_Load_Style(const XML_Element& style)
{
	bool l_b_ret(false);

	mt_Reset_Style();

	l_b_ret = style.mt_Get_Attribute("id", m_style_id);

	return l_b_ret;
}

bool GUI_Manager_Style_Loader::mt_Load_State(const XML_Element& state)
{
	bool l_b_ret(true);

	state.mt_Get_Attribute<GUI_Element_State>("id", m_state_id, &fn_GUIElementState_ToEnum);

	return l_b_ret;
}

bool GUI_Manager_Style_Loader::mt_Load_Text(const XML_Element& text)
{
	bool l_b_ret(true);

	text.mt_Get_Attribute("font_id", m_style.m_text.m_font_id);
	text.mt_Get_Attribute("char_size", m_style.m_text.m_size);
	text.mt_Get_Attribute<GUI_Style_TextHAlign>("h_align", m_style.m_text.m_h_align, &fn_GUIStyleTextHAlign_ToEnum);
	text.mt_Get_Attribute<GUI_Style_TextVAlign>("v_align", m_style.m_text.m_v_align, &fn_GUIStyleTextVAlign_ToEnum);
	mt_Load_Color(text, m_style.m_text.m_color);

	return l_b_ret;
}

bool GUI_Manager_Style_Loader::mt_Load_Background(const XML_Element& background)
{
	bool l_b_ret(true);

	mt_Load_Color(background, m_style.m_background.m_background_color);

	return l_b_ret;
}

bool GUI_Manager_Style_Loader::mt_Finalize_State(const XML_Element& state)
{
	bool l_b_ret(true);

	m_target->mt_Add_Style(m_style_id, m_state_id, m_style);

	return l_b_ret;
}

void GUI_Manager_Style_Loader::mt_Load_Color(const XML_Element& element, sf::Color& color)
{
	int r, g, b, a;
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;

	element.mt_Get_Attribute("r", r);
	element.mt_Get_Attribute("g", g);
	element.mt_Get_Attribute("b", b);
	element.mt_Get_Attribute("a", a);

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void GUI_Manager_Style_Loader::mt_Reset_Style(void)
{
	m_style.m_text.m_color = sf::Color(255, 250, 205);
	m_style.m_text.m_h_align = GUI_Style_TextHAlign::Left;
	m_style.m_text.m_v_align = GUI_Style_TextVAlign::Top;
	m_style.m_text.m_font_id = "";
	m_style.m_text.m_size = 0;
	m_style.m_background.m_background_color = sf::Color(0, 51, 102);
	m_style.m_background.m_outline_color = m_style.m_text.m_color;
	m_style.m_background.m_outline_thickness = 1.0f;
}
*/
