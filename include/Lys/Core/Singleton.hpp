#ifndef _LYS_SINGLETON_HPP
#define _LYS_SINGLETON_HPP 1

namespace lys
{

template<class Derived>
class Singleton
{
protected:
    Singleton() = default;
    virtual ~Singleton() = default;

    Singleton(const Singleton<Derived>& rhs) = delete;
    operator=(const Singleton<Derived>& rhs) = delete;

public:
    static Derived& smt_Get(void)
    {
        static Derived ls_Singleton;

        return ls_Singleton;
    }
};

}

#endif // _LYS_SINGLETON_HPP
