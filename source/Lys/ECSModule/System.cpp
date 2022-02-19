#include "Lys/ECSModule/System.hpp"


namespace lys
{


System::System(EntityManager* entity_manager) : m_Entity_Manager(entity_manager) {}
System::~System() {}


SystemContainer::SystemContainer() : m_Systems() {}

void SystemContainer::mt_Add_System(System* s)
{
    m_Systems.push_back(s);
}

void SystemContainer::mt_OnUpdate(float elapsed_time)
{
    for (std::size_t ii = 0; ii < m_Systems.size(); ii++)
    {
        m_Systems[ii]->mt_OnUpdate(elapsed_time);
    }
}


}
