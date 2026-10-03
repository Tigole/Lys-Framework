#include <lys-window-inputs/lys-window-input.hpp>

namespace lys
{

/// Call at the end of the frame
void Inputs::Refresh(void)
{
    /// Nothing to do
}

bool Inputs::KeyboardIsKeyPressed(lys::KeyId key)
{
    return false;
}

bool Inputs::KeyboardIsKeyReleased(lys::KeyId key)
{
    return false;
}

bool Inputs::KeyboardIsKeyDown(lys::KeyId key)
{
    return false;
}

bool Inputs::KeyboardIsKeyUp(lys::KeyId key)
{
    return false;
}

bool Inputs::ExtractText(uint32_t unicode)
{
    return false;
}

}  // namespace lys
