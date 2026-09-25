#ifndef _LYS_SYSTEM_HPP
#define _LYS_SYSTEM_HPP 1

#include <vector>

#include "Lys/Core/Core.hpp"
#include "Lys/LysConfig.hpp"

namespace lys
{

class EntityManager;

class LYS_API System
{
    LYS_CLASS_NO_COPY(System)
public:
    System(EntityManager* entity_manager);
    virtual ~System();

    virtual void mt_On_Update(float elapsed_time) = 0;

protected:
    EntityManager* m_Entity_Manager;
};

class LYS_API SystemContainer
{
public:
    SystemContainer();

    void mt_Add_System(System* s);

    void mt_On_Update(float elapsed_time);

private:
    std::vector<System*> m_Systems;
};

}  // namespace lys

#endif  // _LYS_SYSTEM_HPP
