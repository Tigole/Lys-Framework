#ifndef _LYS_MULTIKEY_CONTAINER_HPP
#define _LYS_MULTIKEY_CONTAINER_HPP 1

#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace lys
{

template<typename ElementType>
class MultiKeyContainer
{
public:
    void Add_Element(const ElementType& element, uint32_t element_id, const std::string& element_name);
    void Clear(void);

    const ElementType* Get_Element_By_Name(const std::string& element_name) const;
    const ElementType* Get_Element_By_Id(uint32_t element_id) const;

    bool Iterate_Over_Elements(std::function<bool(const ElementType&)> callback) const;

private:
    std::vector<ElementType> elements {};
    std::map<uint32_t, std::size_t> elementsIdMap {};
    std::map<std::string, std::size_t> elementsNameMap {};
};

}  // namespace lys

#include <lys-tiled-map-loading/lys-multikey-container.inl>

#endif  // _LYS_MULTIKEY_CONTAINER_HPP
