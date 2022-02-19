#ifndef _LYS_GUI_BUTTON_HPP
#define _LYS_GUI_BUTTON_HPP 1

#include "GUI_Element.hpp"

#include <string>

namespace lys
{

namespace gui
{

class Button : public Element
{
public:
    Button(const std::string& text);

    void mt_Update_String(const std::string& str);

    void mt_OnUpdate(float elapsed_time) override;

private:
    std::string m_Text;
};

}

}

#endif // _LYS_GUI_BUTTON_HPP
