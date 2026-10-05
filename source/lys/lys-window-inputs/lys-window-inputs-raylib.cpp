#include <lys-window-inputs/lys-window-inputs.hpp>

namespace lys
{

/// Call at the end of the frame
void Inputs::Refresh(void)
{
    /// Nothing to do
}

bool Inputs::Keyboard_Is_Key_Pressed(lys::KeyId key)
{
    return false;
}

bool Inputs::Keyboard_Is_Key_Released(lys::KeyId key)
{
    return false;
}

bool Inputs::Keyboard_Is_Key_Down(lys::KeyId key)
{
    return false;
}

bool Inputs::Keyboard_Is_Key_Up(lys::KeyId key)
{
    return false;
}

bool Inputs::Extract_Text(uint32_t& unicode)
{
    unicode = 0;
    return false;
}

bool Inputs::Is_Close_Requested(void)
{
    return false;
}

}  // namespace lys
