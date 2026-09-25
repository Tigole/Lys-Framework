#include "A.hpp"

#include <stdarg.h>

#define PRINT(fmt, ...) printf("\t" fmt "\n", ##__VA_ARGS__)

LayerA::LayerA() : lys::ApplicationLayer("LayerA")
{
    PRINT("LayerA::LayerA");
}

void LayerA::On_Activate(void)
{
    PRINT("LayerA::On_Activate");
}

void LayerA::On_Deactivate(void)
{
    PRINT("LayerA::On_Deactivate");
}

lys::ApplicationLayerForward LayerA::On_Update(void)
{
    PRINT("LayerA::On_Update");
    return lys::ApplicationLayerForward::Continue;
}

void LayerA::On_Render(void)
{
    PRINT("LayerA::On_Render");
}

lys::ApplicationLayerForward LayerA::Get_Rendering_Forward_Strategy(void) const
{
    PRINT("LayerA::Get_Rendering_Forward_Strategy");
    return lys::ApplicationLayerForward::Continue;
}

StateA::StateA()
{
    PRINT("StateA::StateA");
}

void StateA::On_Create(void)
{
    PRINT("StateA::On_Create");
}

void StateA::On_Destroy(void)
{
    PRINT("StateA::On_Destroy");
}

void StateA::On_Entry(void)
{
    PRINT("StateA::On_Entry");
    Push_Layer(&layerA);
}

void StateA::On_Exit(void)
{
    PRINT("StateA::On_Exit");
    Pop_Layer(&layerA);
}
