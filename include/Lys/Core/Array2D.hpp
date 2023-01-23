#ifndef _LYS_ARRAY_2D_HPP
#define _LYS_ARRAY_2D_HPP 1

#include <vector>
#include "Lys/LysConfig.hpp"

namespace lys
{

struct LYS_API Index2D
{
    Index2D();
    Index2D(std::size_t x, std::size_t y);
    std::size_t xx = 0;
    std::size_t yy = 0;
};

inline bool operator==(const Index2D& lhs, const Index2D& rhs) {return lhs.xx == rhs.xx && lhs.yy == rhs.yy;}
inline bool operator!=(const Index2D& lhs, const Index2D& rhs) {return !(lhs == rhs);}


template<typename T>
class Array2D
{
public:
    Array2D();

    void mt_Resize(std::size_t xx, std::size_t yy, const T& default_value = T());

    const T& operator()(std::size_t xx, std::size_t yy) const;
    const T& mt_Get(std::size_t xx, std::size_t yy) const;
    T& mt_Get(std::size_t xx, std::size_t yy);

    std::size_t mt_Get_Size_X(void) const;
    std::size_t mt_Get_Size_Y(void) const;

    const T& operator[](const Index2D& ii) const;
    T& operator[](const Index2D& ii);

    Index2D mt_Get_Length(void) const;

    bool mt_Is_Index_Valid(const Index2D& i) const;

    void mt_Increment_Index(Index2D& i) const;

    std::size_t mt_Get_Element_Count(void) const;
    const T& operator[](std::size_t index) const;

    Index2D mt_Flat_Index_To_2D(std::size_t index) const;

private:
    Index2D m_Size {};
    std::vector<T> m_Array {};
};

}

#include "Array2D.inl"

#endif // _LYS_ARRAY_2D_HPP
