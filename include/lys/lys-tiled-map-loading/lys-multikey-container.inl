#include <lys-tiled-map-loading/lys-multikey-container.hpp>

namespace lys
{

template<typename ElementType>
void MultiKeyContainer<ElementType>::Add_Element(const ElementType& element, uint32_t element_id, const std::string& element_name)
{
    elementsIdMap.emplace(element_id, elements.size());
    if (element_name.size() > 0)
    {
        elementsNameMap.emplace(element_name, elements.size());
    }
    elements.push_back(element);
}

template<typename ElementType>
void MultiKeyContainer<ElementType>::Clear(void)
{
    elements.clear();
    elementsIdMap.clear();
    elementsNameMap.clear();
}

template<typename ElementType>
const ElementType* MultiKeyContainer<ElementType>::Get_Element_By_Name(const std::string& element_name) const
{
    auto l_It = elementsNameMap.find(element_name);

    if (l_It != elementsNameMap.end())
    {
        return &elements[l_It->second];
    }

    return nullptr;
}

template<typename ElementType>
const ElementType* MultiKeyContainer<ElementType>::Get_Element_By_Id(uint32_t element_id) const
{
    auto l_It = elementsIdMap.find(element_id);

    if (l_It != elementsIdMap.end())
    {
        return &elements[l_It->second];
    }

    return nullptr;
}

template<typename ElementType>
bool MultiKeyContainer<ElementType>::Iterate_Over_Elements(std::function<bool(const ElementType&)> callback) const
{
    for (std::size_t ii = 0; ii < elements.size(); ii++)
    {
        if (callback(elements[ii]) == false)
        {
            return false;
        }
    }

    return true;
}

}  // namespace lys
