#include "Lys/GUIModule/Elements/GUI_Separator.hpp"

#include "imgui.h"

namespace lys
{

namespace gui
{

Separator::Separator()
{
    //
}

void Separator::mt_OnUpdate([[maybe_unused]]float elapsed_time)
{
    ImGui::Separator();
}

}

}
