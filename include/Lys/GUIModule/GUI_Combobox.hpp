#ifndef _LYS_GUI_COMBOBOX_HPP
#define _LYS_GUI_COMBOBOX_HPP 1

#include <string>
#include <vector>

#include "Lys/LysConfig.hpp"

namespace lys
{


class LYS_API ComboBox
{
public:
    ComboBox();

    void mt_Reset(void);

    template<typename... Rest>
    void mt_Setup(const std::string& first, Rest... rest)
    {
        m_List.push_back(first);
        mt_Setup(rest...);
    }

    void mt_Setup(const std::string& first);

    void mt_Add(const std::string& str);

    bool mt_Draw(const std::string& name);

    void mt_Init(const std::string& init_value);
    void mt_Init(std::size_t init_index);
    const std::string& mt_Get(void) const;
    std::size_t mt_Get_Index(void) const;
    const std::vector<std::string>& mt_Get_List(void) const;

private:
    std::vector<std::string> m_List;
    std::size_t m_Current_Selected;
    bool m_Reset;
};

}

#endif // _LYS_GUI_COMBOBOX_HPP
