#include <lys-window-inputs/lys-window-inputs.hpp>

namespace lys
{

void Inputs::On_SFML_Text(const sf::Event::TextEntered& text)
{
    if (char_code_count < char_codes.size())
    {
        char_codes[char_code_count] = text.unicode;
        char_code_count++;
    }
}

void Inputs::On_SFML_Close_Request(void)
{
    close_requested = true;
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

    close_requested = false;
}

bool Inputs::Keyboard_Is_Key_Pressed(lys::KeyId key)
{
    return Keyboard_Is_Key_Down(key) && prev_key_state_down.test(static_cast<std::size_t>(key)) == false;
}

bool Inputs::Keyboard_Is_Key_Released(lys::KeyId key)
{
    return Keyboard_Is_Key_Up(key) && prev_key_state_down.test(static_cast<std::size_t>(key)) == true;
}
bool Inputs::Keyboard_Is_Key_Down(lys::KeyId key)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(key)) == true;
}

bool Inputs::Keyboard_Is_Key_Up(lys::KeyId key)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(key)) == false;
}

bool Inputs::Extract_Text(uint32_t& unicode)
{
    if (next_char_code_idx >= char_code_count)
    {
        return false;
    }
    unicode = char_codes[next_char_code_idx];
    next_char_code_idx++;
    return true;
}

bool Inputs::Is_Close_Requested(void)
{
    return close_requested;
}

}  // namespace lys
