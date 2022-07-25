#ifndef _LYS_ENTITY_HPP
#define _LYS_ENTITY_HPP 1

#include "Lys/MathModule/Rand.hpp"

#include <map>
#include <memory>
#include <any>
#include <functional>

namespace lys
{

namespace priv
{

using ComponentContainer = std::map<std::size_t, std::any>;

template<class...>
struct ComponentChecker;

template<class ComponentType, class... OtherComponentsTypes>
struct ComponentChecker<ComponentType, OtherComponentsTypes...>
{
    static bool mt_Has_Component(const ComponentContainer& components)
    {
        return (components.find(typeid(ComponentType).hash_code()) != components.end()) && ComponentChecker<OtherComponentsTypes...>::mt_Has_Component(components);
    }
};

template<>
struct ComponentChecker<>
{
    static bool mt_Has_Component([[maybe_unused]]const ComponentContainer& components)
    {
        return true;
    }
};

}

class EntityManager;

class LYS_API Entity
{
    friend EntityManager;

public:

    using IdType = uint32_t;

    template<class ComponentType>
    ComponentType* mt_Get_Component(bool create_if_not_present)
    {
        ComponentType* l_Ret = nullptr;
        std::size_t l_Hash_Code = typeid(ComponentType).hash_code();
        auto l_it = m_Components.find(l_Hash_Code);

        if (l_it == m_Components.end())
        {
            if (create_if_not_present == true)
            {
                m_Components.emplace(l_Hash_Code, ComponentType());
                l_Ret = std::any_cast<ComponentType>(&m_Components[l_Hash_Code]);
            }
        }
        else
        {
            std::any* l_Any = &l_it->second;
            l_Ret = std::any_cast<ComponentType>(l_Any);
        }

        return l_Ret;
    }

    template<class... Components>
    bool mt_Has_Component(void) const
    {
        return priv::ComponentChecker<Components...>::mt_Has_Component(m_Components);
    }

    IdType mt_Get_Id(void) const
    {
        return m_Id;
    }

    EntityManager& mt_Get_Manager(void)
    {
        return m_Manager;
    }

private:
    Entity(IdType id, EntityManager& mngr);

    IdType m_Id;
    priv::ComponentContainer m_Components;
    EntityManager& m_Manager;
};


class LYS_API EntityManager
{
public:

    static constexpr const Entity::IdType sm_Not_An_Entity = -1;

    EntityManager();

    Entity* mt_Create_Entity(Entity::IdType entity_id);
    void mt_Clear(void);

    Entity::IdType mt_Get_Next_Entity_Id(void) const;

    Entity* mt_Get_Entity(Entity::IdType entity_id);

    std::vector<Entity*> mt_Get_Entities(std::function<bool(const Entity&)> select_entity);
    template<class... Components>
    std::vector<Entity*> mt_Get_Entities(void)
    {
        std::vector<Entity*> l_Ret;

        for (auto& e : m_Entities)
        {
            if (e.second->mt_Has_Component<Components...>())
            {
                l_Ret.push_back(e.second.get());
            }
        }

        return l_Ret;
    }

    template<typename T>
    std::vector<T*> mt_Get_Components(void)
    {
        std::vector<T*> l_Ret;

        for (auto& e : m_Entities)
        {
            T* l_Tmp = e.second->mt_Get_Component<T>(false);

            if (l_Tmp != nullptr)
            {
                l_Ret.push_back(l_Tmp);
            }
        }

        return l_Ret;
    }

private:

    std::map<Entity::IdType, std::unique_ptr<Entity>> m_Entities;

    Entity::IdType m_Next_Entity_Id = 0;
};


}

#endif // _LYS_ENTITY_HPP
