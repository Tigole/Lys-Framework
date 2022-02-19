#include "Lys/ECSModule/Entity.hpp"

namespace lys
{



Entity::Entity(IdType id, EntityManager& mngr) :
    m_Id(id),
    m_Components(),
    m_Manager(mngr)
{}

EntityManager::EntityManager() : m_Entities(), m_Next_Entity_Id(0)
{}

Entity* EntityManager::mt_Create_Entity(Entity::IdType entity_id)
{
    Entity* l_Ret = m_Entities.emplace(entity_id, std::unique_ptr<Entity>(new Entity(entity_id, *this))).first->second.get();

    if (m_Next_Entity_Id <= entity_id)
    {
        m_Next_Entity_Id = entity_id + 1;
    }

    return l_Ret;
}

void EntityManager::mt_Clear(void)
{
    m_Entities.clear();
    m_Next_Entity_Id = 0;
}

Entity::IdType EntityManager::mt_Get_Next_Entity_Id(void) const
{
    return m_Next_Entity_Id;
}

Entity* EntityManager::mt_Get_Entity(Entity::IdType entity_id)
{
    auto l_it = m_Entities.find(entity_id);

    return (l_it != m_Entities.end()) ? l_it->second.get() : nullptr;
}

std::vector<Entity*> EntityManager::mt_Get_Entities(std::function<bool(const Entity&)> select_entity)
{
    std::vector<Entity*> l_Entities;

    for (auto& e : m_Entities)
    {
        if (select_entity(*e.second) == true)
        {
            l_Entities.push_back(e.second.get());
        }
    }

    return l_Entities;
}

}
