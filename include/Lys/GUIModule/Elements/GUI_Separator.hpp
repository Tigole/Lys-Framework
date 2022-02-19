#ifndef _LYS_GUI_SEPARATOR_HPP
#define _LYS_GUI_SEPARATOR_HPP 1

#include "Lys/GUIModule/GUI_Element.hpp"

namespace lys
{

namespace gui
{


class Separator : public Element
{
public:
    Separator();

    void mt_OnUpdate(float elapsed_time) override;
};


}

}

#endif // _LYS_GUI_SEPARATOR_HPP
