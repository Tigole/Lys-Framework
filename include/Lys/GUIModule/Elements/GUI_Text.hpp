#ifndef _LYS_GUI_TEXT_HPP
#define _LYS_GUI_TEXT_HPP 1
#if 0
#include "Lys/GUIModule/GUI_Element.hpp"

namespace lys
{
namespace gui
{

class LYS_API Text : public Element
{
public:
    Text(const std::string& text = std::string());

    void mt_OnUpdate(float elapsed_time) override;

    void mt_Set_Text(const std::string& text);

private:
    std::string m_Text;
};

}
}
#endif // 0
#endif // _LYS_GUI_TEXT_HPP
