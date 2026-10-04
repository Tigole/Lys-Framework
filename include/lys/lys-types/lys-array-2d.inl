#include <lys-types/lys-array-2d.hpp>

namespace lys
{

template<typename T>
Array2D<T>::Array2D()
{}

template<typename T>
void Array2D<T>::Resize(std::size_t xx, std::size_t yy, const T& default_value)
{
    size.x = xx;
    size.y = yy;
    array.clear();
    array.resize(xx * yy, default_value);
}

template<typename T>
const T& Array2D<T>::operator()(std::size_t xx, std::size_t yy) const
{
    return array[xx * size.y + yy];
}

template<typename T>
T& Array2D<T>::operator()(std::size_t xx, std::size_t yy)
{
    return array[xx * size.y + yy];
}

template<typename T>
const T& Array2D<T>::Get(std::size_t xx, std::size_t yy) const
{
    return array[xx * size.y + yy];
}

template<typename T>
T& Array2D<T>::Get(std::size_t xx, std::size_t yy)
{
    return array[xx * size.y + yy];
}

template<typename T>
std::size_t Array2D<T>::Get_Size_X(void) const
{
    return size.x;
}

template<typename T>
std::size_t Array2D<T>::Get_Size_Y(void) const
{
    return size.y;
}

template<typename T>
const T& Array2D<T>::operator[](const Index2D& ii) const
{
    return Get(ii.x, ii.y);
}

template<typename T>
T& Array2D<T>::operator[](const Index2D& ii)
{
    return Get(ii.x, ii.y);
}

template<typename T>
Index2D Array2D<T>::Get_Length(void) const
{
    return size;
}

template<typename T>
bool Array2D<T>::Is_Index_Valid(const Index2D& i) const
{
    return i.x >= 0 && i.x < size.x && i.y >= 0 && i.y < size.y;
}

template<typename T>
void Array2D<T>::Increment_Index(Index2D& i) const
{
    i.x++;
    if (i.x >= size.x)
    {
        i.x = 0;
        i.y++;
    }
}

template<typename T>
std::size_t Array2D<T>::Get_Element_Count(void) const
{
    return array.size();
}

template<typename T>
const T& Array2D<T>::operator[](std::size_t index) const
{
    return array[index];
}

template<typename T>
Index2D Array2D<T>::Flat_Index_To_2D(std::size_t index) const
{
    return Index2D(index % size.x, index / size.x);
}

}  // namespace lys
