#include <lys-window-inputs/lys-window-input.hpp>

namespace lys
{

void Inputs::OnSFMLText(const sf::Event::TextEntered& text)
{
    if (char_code_count < char_codes.size())
    {
        char_codes[char_code_count] = text.unicode;
        char_code_count++;
    }
}

/// Call at the end of the frame
void Inputs::Refresh(void)
{
    char_code_count    = 0;
    next_char_code_idx = 0;
    for (std::size_t ii = 0; ii < prev_key_state_down.size(); ii++)
    {
        prev_key_state_down.set(ii, sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scan>(ii)));
    }
}

bool Inputs::KeyboardIsKeyPressed(lys::KeyId key)
{
    return KeyboardIsKeyDown(key) && prev_key_state_down.test(static_cast<std::size_t>(key)) == false;
}

bool Inputs::KeyboardIsKeyReleased(lys::KeyId key)
{
    return KeyboardIsKeyUp(key) && prev_key_state_down.test(static_cast<std::size_t>(key)) == true;
}
bool Inputs::KeyboardIsKeyDown(lys::KeyId key)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(key)) == true;
}

bool Inputs::KeyboardIsKeyUp(lys::KeyId key)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(key)) == false;
}

bool Inputs::ExtractText(uint32_t unicode)
{
    if (next_char_code_idx >= char_code_count)
    {
        return false;
    }
    unicode = char_codes[next_char_code_idx];
    next_char_code_idx++;
    return true;
}

}  // namespace lys
