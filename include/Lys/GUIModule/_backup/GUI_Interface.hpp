#ifndef _LYS_GUI_INTERFACE_HPP
#define _LYS_GUI_INTERFACE_HPP 1

#include "GUI_Element.hpp"

#include <map>
#include <memory>
#include <string>

namespace lys
{

namespace gui
{

class Interface : public Element
{
public:
    void mt_OnUpdate(float elapsed_time) override;

    void mt_Push_Child(const std::string& id, Element* child);

    void mt_Set_Position(const Vector2f& pos) override;
    void mt_Set_Size(const Vector2f& size) override;

private:
    std::map<std::string, std::unique_ptr<Element>> m_Children;
};

}


}

#endif // _LYS_GUI_INTERFACE_HPP
