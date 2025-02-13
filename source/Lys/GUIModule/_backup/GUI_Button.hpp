#ifndef _LYS_GUI_BUTTON_HPP
#define _LYS_GUI_BUTTON_HPP 1

#include <string>

#include "GUI_Element.hpp"

namespace lys
{

namespace gui
{

class Button: public Element
{
public:
    Button(const std::string& text);

    void mt_Update_String(const std::string& str);

    void mt_On_Update(float elapsed_time) override;

private:
    std::string m_Text;
};

}  // namespace gui

}  // namespace lys

#endif  // _LYS_GUI_BUTTON_HPP
