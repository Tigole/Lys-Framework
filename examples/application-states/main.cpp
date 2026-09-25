#include <cstdio>
#include <lys-module-application-states.hpp>

#include "A.hpp"

int main(int argc, char** argv)
{
    lys::ApplicationStateManager stateManager;

    printf("Register_State\n");
    stateManager.Register_State<StateA>(0);

    printf("Set_Initial_State\n");
    stateManager.Set_Initial_State<StateA>(0, nullptr);

    printf("On_Update_Logic\n");
    stateManager.On_Update_Logic();
    printf("On_Update_Render\n");
    stateManager.On_Update_Render();
    printf("Clear\n");
    stateManager.Clear();

    return 0;
}
