#include "Lys/StateModule/LayerLys.hpp"

#include "Lys/Application/Application.hpp"
#include "Lys/MessageModule/MessageManager.hpp"
#include "Lys/GraphicModule/DrawCommandSettings.hpp"

namespace lys
{


LayerLys::LayerLys() :
    lys::Layer("Lys"),
    m_Next_State(-1),
    m_Condition_Change_State(false),
    m_Remaining_Time(2.0f)
{}

LayerForward LayerLys::mt_On_Update([[maybe_unused]] float elapsed_time)
{
    m_Remaining_Time -= elapsed_time;

    if (m_Remaining_Time < 0.0f)
    {
        m_Condition_Change_State = true;
    }

    if (m_Condition_Change_State == true)
    {
        mt_Send_Message(Message_ChangeState(m_Next_State));
    }

    return LayerForward::Stop;
}

void LayerLys::mt_On_Render(void)
{
    gui::TextSettings l_Text_Settings;

    l_Text_Settings.m_Vertical_Align = gui::TextOriginMode::Centered;
    l_Text_Settings.m_Horizontal_Align = gui::TextOriginMode::Centered;
    l_Text_Settings.m_Character_Size = 30;
    l_Text_Settings.m_Fill_Color = Color::White;
    l_Text_Settings.m_Outline_Color = Color::Black;
    l_Text_Settings.m_Outline_Thickness = 0.0f;

    Renderer::smt_Get().mt_Draw_Text("Lys", Vector2f(Window::smt_Get().mt_Get_Size().x * 0.5f, Window::smt_Get().mt_Get_Size().y * 0.66f), l_Text_Settings);
}

LayerForward LayerLys::mt_On_Event_Key_Released(const KeyEvent& key_event)
{
    if (key_event.m_Key.code == sf::Keyboard::Key::Space)
    {
        m_Condition_Change_State = true;
    }

    return LayerForward::Stop;
}

}
