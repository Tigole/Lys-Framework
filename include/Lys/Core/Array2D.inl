#include "Array2D.hpp"

namespace lys
{


template<typename T>
Array2D<T>::Array2D() {}

template<typename T>
void Array2D<T>::mt_Resize(std::size_t xx, std::size_t yy, const T& default_value)
{
    m_Size.xx = xx;
    m_Size.yy = yy;
    m_Array.resize(xx * yy, default_value);
}

template<typename T>
const T& Array2D<T>::operator()(std::size_t xx, std::size_t yy) const
{
    return m_Array[xx * m_Size.yy + yy];
}

template<typename T>
const T& Array2D<T>::mt_Get(std::size_t xx, std::size_t yy) const
{
    return m_Array[xx * m_Size.yy + yy];
}

template<typename T>
T& Array2D<T>::mt_Get(std::size_t xx, std::size_t yy)
{
    return m_Array[xx * m_Size.yy + yy];
}

template<typename T>
std::size_t Array2D<T>::mt_Get_Size_X(void) const
{
    return m_Size.xx;
}

template<typename T>
std::size_t Array2D<T>::mt_Get_Size_Y(void) const
{
    return m_Size.yy;
}

template<typename T>
const T& Array2D<T>::operator[](const Index2D& ii) const
{
    return m_Array.mt_Get(ii.xx, ii.yy);
}

template<typename T>
T& Array2D<T>::operator[](const Index2D& ii)
{
    return mt_Get(ii.xx, ii.yy);
}

template<typename T>
Index2D Array2D<T>::mt_Get_Length(void) const
{
    return m_Size;
}

template<typename T>
bool Array2D<T>::mt_Is_Index_Valid(const Index2D& i) const
{
    return i.xx >= 0 && i.xx < m_Size.xx && i.yy >= 0 && i.yy < m_Size.yy;
}

template<typename T>
void Array2D<T>::mt_Increment_Index(Index2D& i) const
{
    i.xx++;
    if (i.xx >= m_Size.xx)
    {
        i.xx = 0;
        i.yy++;
    }
}

template<typename T>
std::size_t Array2D<T>::mt_Get_Element_Count(void) const
{
    return m_Array.size();
}

template<typename T>
const T& Array2D<T>::operator[](std::size_t index) const
{
    return m_Array[index];
}

template<typename T>
Index2D Array2D<T>::mt_Flat_Index_To_2D(std::size_t index) const
{
    return Index2D(index % m_Size.xx, index / m_Size.xx);
}

}
