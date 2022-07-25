#ifndef _GUI_INTERFACE_HPP
#define _GUI_INTERFACE_HPP 1

#include "GUI_Element.hpp"

#include <map>
#include <vector>
#include <string>
#include <memory>

namespace lys
{

namespace gui
{

class LYS_API Interface
{
public:
    Interface(const std::string& id);
    virtual ~Interface();

    virtual void mt_OnUpdate(float elapsed_time) = 0;

    bool mt_Is_Active(void) const;
    void mt_Set_Active(bool active);

    void mt_Set_Allocation(const Rectf& allocation);
    void mt_Set_Position(const Vector2f& position);
    const Rectf& mt_Get_Allocation(void) const;

    const std::string& mt_Get_Id(void) const;

private:
    std::string m_Id;

    bool m_Is_Active;
    Rectf m_Allocation;
};

class LYS_API Interface_Predefined : public Interface
{
public:
    Interface_Predefined(const std::string& id);
    virtual ~Interface_Predefined();

    void mt_OnUpdate(float elapsed_time) override;

    template<class El, typename... _Args>
    El* mt_Add_Element(const std::string& id, _Args&&... __args)
    {
        El* l_Ret = nullptr;
        m_Named_Elements.emplace(id, m_Elements.size());
        m_Elements.push_back(std::make_unique<El>(__args...));
        l_Ret = static_cast<El*>(m_Elements.back().get());
        l_Ret->m_Interface_Id = &mt_Get_Id();
        l_Ret->m_Element_Id = id;
        return l_Ret;
    }

    template<class El>
    El* mt_Get_Element(const std::string& element_id)
    {
        return dynamic_cast<El*>(m_Elements[mt_Get_Element_Index(element_id)].get());
    }

    void mt_Set_Element_Active(const std::string& element_id, bool active);

protected:

    std::map<std::string, std::size_t> m_Named_Elements;
    std::vector<std::unique_ptr<Element>> m_Elements;

    std::size_t mt_Get_Element_Index(const std::string& element_id);
};

}

}

#endif // !_GUI_INTERFACE_HPP
