#ifndef _LYS_SINGLETON_HPP
#define _LYS_SINGLETON_HPP 1

#include "Lys/Core/Log.hpp"

namespace lys
{

namespace _priv_singleton
{

void fn_Log_Singleton_Creation(const char* singleton_name);

void fn_Log_Singleton_Destroy(const char* singleton_name);

}

template<class Derived>
class Singleton
{
protected:
    Singleton(const char* name) : m_Name(name)
    {
        _priv_singleton::fn_Log_Singleton_Creation(m_Name);
    }
    virtual ~Singleton()
    {
        _priv_singleton::fn_Log_Singleton_Destroy(m_Name);
    }

    Singleton(const Singleton<Derived>& rhs) = delete;
    operator=(const Singleton<Derived>& rhs) = delete;

public:
    static Derived& smt_Get(void)
    {
        static Derived ls_Singleton;

        return ls_Singleton;
    }

private:
    const char* m_Name;
};

}

#endif // _LYS_SINGLETON_HPP
