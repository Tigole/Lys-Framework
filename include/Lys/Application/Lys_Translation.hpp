#ifndef _LYS_TRANSLATION_HPP
#define _LYS_TRANSLATION_HPP 1

#include <unordered_map>
#include <memory>
#include <string>
#include <any>

namespace lys
{

class LYS_API StringHandlerHelper
{
public:
    virtual ~StringHandlerHelper(){}

    virtual std::string mt_Get_String(const std::any& index) = 0;

    virtual void mt_Add_String(const std::any& index, const std::string& str) = 0;
};

template<typename IndexType>
class LYS_API StringHandlerHelperT : public StringHandlerHelper
{
public:

    std::string mt_Get_String(const std::any& index) override
    {
        IndexType l_Index = std::any_cast<IndexType>(index);
        std::string l_Return = std::to_string(static_cast<int>(l_Index));
        auto l_it = m_Strings.find(l_Index);

        if (l_it != m_Strings.end())
        {
            l_Return = l_it->second;
        }

        return l_Return;
    }

    void mt_Add_String(const std::any& index, const std::string& str) override
    {
        m_Strings[std::any_cast<IndexType>(index)] = str;
    }

private:
    std::unordered_map<IndexType, std::string> m_Strings;
};

class LYS_API StringHandler
{
public:
    StringHandler()
    {}

    template<typename T>
    std::string mt_Get_String(const std::string& category_id, const T& index)
    {
        std::string l_Return = std::to_string(static_cast<int>(index));
        auto l_Category = m_String_Handlers.find(category_id);

        if (l_Category != m_String_Handlers.end())
        {
            l_Return = l_Category->second->mt_Get_String(index);
        }

        return l_Return;
    }

    template<typename T>
    void mt_Add_String(const std::string& category_id, const T& index, const std::string& str)
    {
        auto l_Category = m_String_Handlers.find(category_id);

        if (l_Category == m_String_Handlers.end())
        {
            l_Category = m_String_Handlers.emplace(category_id, std::make_unique<StringHandlerHelperT<T>>()).first;
        }

        l_Category->second->mt_Add_String(index, str);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<StringHandlerHelper>> m_String_Handlers;
};

class LYS_API Translator
{
public:

    template<typename T>
    void mt_Add_String(const std::string& language, const std::string& category, const T& index, const std::string& str)
    {
        m_Handlers[language].mt_Add_String(category, index, str);
    }

    template<typename T>
    std::string mt_Get_String(const std::string& category, const T& index)
    {
        return m_Handlers[m_Language].mt_Get_String(category, index);
    }

    void mt_Set_Language(const std::string& language)
    {
        m_Language = language;
    }

    const std::string& mt_Get_Language(void) const
    {
        return m_Language;
    }

private:
    std::string m_Language;
    std::unordered_map<std::string, StringHandler> m_Handlers;
};

}

#endif // _LYS_TRANSLATION_HPP
