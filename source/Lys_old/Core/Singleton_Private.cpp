#include "Lys/Core/Log.hpp"
#include "Lys/Core/Singleton.hpp"

namespace lys
{

namespace _priv_singleton
{

void fn_Log_Singleton_Creation(const char* singleton_name)
{
    LYS_LOG_CORE_DEBUG("Creating singleton: '%s'", singleton_name);
}

void fn_Log_Singleton_Destroy(const char* singleton_name)
{
    LYS_LOG_CORE_DEBUG("Deleting singleton: '%s'", singleton_name);
}

}

}
