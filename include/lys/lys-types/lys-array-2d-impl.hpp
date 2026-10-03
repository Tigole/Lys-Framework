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
std::size_t Array2D<T>::GetSizeX(void) const
{
    return size.x;
}

template<typename T>
std::size_t Array2D<T>::GetSizeY(void) const
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
Index2D Array2D<T>::GetLength(void) const
{
    return size;
}

template<typename T>
bool Array2D<T>::IsIndexValid(const Index2D& i) const
{
    return i.x >= 0 && i.x < size.x && i.y >= 0 && i.y < size.y;
}

template<typename T>
void Array2D<T>::IncrementIndex(Index2D& i) const
{
    i.x++;
    if (i.x >= size.x)
    {
        i.x = 0;
        i.y++;
    }
}

template<typename T>
std::size_t Array2D<T>::GetElementCount(void) const
{
    return array.size();
}

template<typename T>
const T& Array2D<T>::operator[](std::size_t index) const
{
    return array[index];
}

template<typename T>
Index2D Array2D<T>::FlatIndexTo2D(std::size_t index) const
{
    return Index2D(index % size.x, index / size.x);
}

}  // namespace lys
