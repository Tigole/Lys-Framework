#include "GUI_Interface.hpp"

namespace lys
{

namespace gui
{

void Interface::mt_OnUpdate(float elapsed_time)
{
    for (auto& child : m_Children)
    {
        child.second->mt_OnUpdate(elapsed_time);
    }
}

void Interface::mt_Push_Child(const std::string& id, Element* child)
{
    Rectf l_Area;

    child->mt_Set_Parent(this);
    m_Children.emplace(id, std::unique_ptr<Element>(child));

    l_Area.m_Top_Left = Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    l_Area.m_Width_Height = Vector2f(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

    for (auto& c : m_Children)
    {
        Rectf l_Child = c.second->mt_Get_Area();

        l_Area.m_Top_Left.x = std::min(l_Area.m_Top_Left.x, l_Child.m_Top_Left.x);
        l_Area.m_Top_Left.y = std::min(l_Area.m_Top_Left.y, l_Child.m_Top_Left.y);

        if (l_Area.m_Top_Left.x + l_Area.m_Width_Height.x < l_Child.m_Top_Left.x + l_Child.m_Width_Height.x)
        {
            l_Area.m_Width_Height.x = l_Child.m_Width_Height.x;
        }
        if (l_Area.m_Top_Left.y + l_Area.m_Width_Height.y < l_Child.m_Top_Left.y + l_Child.m_Width_Height.y)
        {
            l_Area.m_Width_Height.y = l_Child.m_Width_Height.y;
        }
    }

    m_Position = l_Area.m_Top_Left;
    m_Size = l_Area.m_Width_Height;
}

void Interface::mt_Set_Position(const Vector2f& pos)
{
    m_Position = pos;
    for (auto& c : m_Children)
    {
        c.second->mt_Set_Position(pos);
    }
}

void Interface::mt_Set_Size(const Vector2f& size)
{
    m_Size = size;
    for (auto& c : m_Children)
    {
        c.second->mt_Set_Size(size);
    }
}

}

}
