#include "Lys/StateModule/StateLys.hpp"

#include "Lys/Application/Application.hpp"
#include "Lys/MessageModule/MessageManager.hpp"
#include "Lys/GraphicModule/DrawCommandSettings.hpp"

namespace lys
{


State_Lys::State_Lys() :
    m_Next_State(-1),
    m_Condition_Change_State(false)
{}

void State_Lys::mt_OnEvent(const Event& event)
{
    if (event.m_SFML.type == sf::Event::KeyReleased && event.m_SFML.key.code == sf::Keyboard::Space)
    {
        m_Condition_Change_State = true;
    }
}

void State_Lys::mt_OnUpdate(float elapsed_time)
{
    if (m_Condition_Change_State == true)
    {
        MessageManager::smt_Get().mt_Send_Message(Message_ChangeState(m_Next_State));
    }

    gui::TextSettings l_Text_Settings;

    l_Text_Settings.m_Vertical_Align = gui::TextOriginMode::Centered;
    l_Text_Settings.m_Horizontal_Align = gui::TextOriginMode::Centered;
    l_Text_Settings.m_Character_Size = 30;
    l_Text_Settings.m_Fill_Color = Color::White;
    l_Text_Settings.m_Outline_Color = Color::Black;
    l_Text_Settings.m_Outline_Thickness = 0.0f;

    Renderer::smt_Get().mt_Draw_Text("Lys", Vector2f(Window::smt_Get().mt_Get_Size().x * 0.5f, Window::smt_Get().mt_Get_Size().y * 0.66f), l_Text_Settings);
}



}
