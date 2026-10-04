#ifndef _LYS_ARRAY_2D_HPP
#define _LYS_ARRAY_2D_HPP 1

#include <vector>

namespace lys
{

struct Index2D
{
    Index2D() = default;
    Index2D(std::size_t xx, std::size_t yy) : x(xx), y(yy) {}
    std::size_t x = 0;
    std::size_t y = 0;
};

inline bool operator==(const Index2D& lhs, const Index2D& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const Index2D& lhs, const Index2D& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
class Array2D
{
public:
    Array2D();

    void Resize(std::size_t xx, std::size_t yy, const T& default_value = T());

    const T& operator()(std::size_t xx, std::size_t yy) const;
    T& operator()(std::size_t xx, std::size_t yy);
    const T& Get(std::size_t xx, std::size_t yy) const;
    T& Get(std::size_t xx, std::size_t yy);

    std::size_t Get_Size_X(void) const;
    std::size_t Get_Size_Y(void) const;

    const T& operator[](const Index2D& ii) const;
    T& operator[](const Index2D& ii);

    Index2D Get_Length(void) const;

    bool Is_Index_Valid(const Index2D& i) const;

    void Increment_Index(Index2D& i) const;

    std::size_t Get_Element_Count(void) const;
    const T& operator[](std::size_t index) const;

    Index2D Flat_Index_To_2D(std::size_t index) const;

private:
    Index2D size         = {};
    std::vector<T> array = {};
};

}  // namespace lys

#include <lys-types/lys-array-2d.inl>

#endif  // _LYS_ARRAY_2D_HPP
