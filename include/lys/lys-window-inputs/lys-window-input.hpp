#ifndef _LYS_WINDOW_INPUT_HPP
#define _LYS_WINDOW_INPUT_HPP 1

#include <lys-config.hpp>

#if LYS_WINDOW_BACKEND_SFML
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <bitset>
#include <cstdint>
#elif LYS_WINDOW_BACKEND_RAYLIB
#else
#error "No backend defined"
#endif

namespace lys
{

/// Unmapped layout -> physical position rather than meaning (Q or A depending of the layout)
enum class KeyId
{
#if LYS_WINDOW_BACKEND == LYS_WINDOW_BACKEND_SFML
    A              = (int)sf::Keyboard::Scan::A,               //!< Keyboard a and A key
    B              = (int)sf::Keyboard::Scan::B,               //!< Keyboard b and B key
    C              = (int)sf::Keyboard::Scan::C,               //!< Keyboard c and C key
    D              = (int)sf::Keyboard::Scan::D,               //!< Keyboard d and D key
    E              = (int)sf::Keyboard::Scan::E,               //!< Keyboard e and E key
    F              = (int)sf::Keyboard::Scan::F,               //!< Keyboard f and F key
    G              = (int)sf::Keyboard::Scan::G,               //!< Keyboard g and G key
    H              = (int)sf::Keyboard::Scan::H,               //!< Keyboard h and H key
    I              = (int)sf::Keyboard::Scan::I,               //!< Keyboard i and I key
    J              = (int)sf::Keyboard::Scan::J,               //!< Keyboard j and J key
    K              = (int)sf::Keyboard::Scan::K,               //!< Keyboard k and K key
    L              = (int)sf::Keyboard::Scan::L,               //!< Keyboard l and L key
    M              = (int)sf::Keyboard::Scan::M,               //!< Keyboard m and M key
    N              = (int)sf::Keyboard::Scan::N,               //!< Keyboard n and N key
    O              = (int)sf::Keyboard::Scan::O,               //!< Keyboard o and O key
    P              = (int)sf::Keyboard::Scan::P,               //!< Keyboard p and P key
    Q              = (int)sf::Keyboard::Scan::Q,               //!< Keyboard q and Q key
    R              = (int)sf::Keyboard::Scan::R,               //!< Keyboard r and R key
    S              = (int)sf::Keyboard::Scan::S,               //!< Keyboard s and S key
    T              = (int)sf::Keyboard::Scan::T,               //!< Keyboard t and T key
    U              = (int)sf::Keyboard::Scan::U,               //!< Keyboard u and U key
    V              = (int)sf::Keyboard::Scan::V,               //!< Keyboard v and V key
    W              = (int)sf::Keyboard::Scan::W,               //!< Keyboard w and W key
    X              = (int)sf::Keyboard::Scan::X,               //!< Keyboard x and X key
    Y              = (int)sf::Keyboard::Scan::Y,               //!< Keyboard y and Y key
    Z              = (int)sf::Keyboard::Scan::Z,               //!< Keyboard z and Z key
    Num1           = (int)sf::Keyboard::Scan::Num1,            //!< Keyboard 1 and ! key
    Num2           = (int)sf::Keyboard::Scan::Num2,            //!< Keyboard 2 and @ key
    Num3           = (int)sf::Keyboard::Scan::Num3,            //!< Keyboard 3 and # key
    Num4           = (int)sf::Keyboard::Scan::Num4,            //!< Keyboard 4 and $ key
    Num5           = (int)sf::Keyboard::Scan::Num5,            //!< Keyboard 5 and % key
    Num6           = (int)sf::Keyboard::Scan::Num6,            //!< Keyboard 6 and ^ key
    Num7           = (int)sf::Keyboard::Scan::Num7,            //!< Keyboard 7 and & key
    Num8           = (int)sf::Keyboard::Scan::Num8,            //!< Keyboard 8 and * key
    Num9           = (int)sf::Keyboard::Scan::Num9,            //!< Keyboard 9 and ) key
    Num0           = (int)sf::Keyboard::Scan::Num0,            //!< Keyboard 0 and ) key
    Enter          = (int)sf::Keyboard::Scan::Enter,           //!< Keyboard Enter/Return key
    Escape         = (int)sf::Keyboard::Scan::Escape,          //!< Keyboard Escape key
    Backspace      = (int)sf::Keyboard::Scan::Backspace,       //!< Keyboard Backspace key
    Tab            = (int)sf::Keyboard::Scan::Tab,             //!< Keyboard Tab key
    Space          = (int)sf::Keyboard::Scan::Space,           //!< Keyboard Space key
    Hyphen         = (int)sf::Keyboard::Scan::Hyphen,          //!< Keyboard - and _ key
    Equal          = (int)sf::Keyboard::Scan::Equal,           //!< Keyboard = and +
    LBracket       = (int)sf::Keyboard::Scan::LBracket,        //!< Keyboard [ and { key
    RBracket       = (int)sf::Keyboard::Scan::RBracket,        //!< Keyboard ] and } key
    Backslash      = (int)sf::Keyboard::Scan::Backslash,       //!< Keyboard \ and | key OR various keys for Non-US keyboards
    Semicolon      = (int)sf::Keyboard::Scan::Semicolon,       //!< Keyboard ; and : key
    Apostrophe     = (int)sf::Keyboard::Scan::Apostrophe,      //!< Keyboard ' and " key
    Grave          = (int)sf::Keyboard::Scan::Grave,           //!< Keyboard ` and ~ key
    Comma          = (int)sf::Keyboard::Scan::Comma,           //!< Keyboard , and < key
    Period         = (int)sf::Keyboard::Scan::Period,          //!< Keyboard . and > key
    Slash          = (int)sf::Keyboard::Scan::Slash,           //!< Keyboard / and ? key
    F1             = (int)sf::Keyboard::Scan::F1,              //!< Keyboard F1 key
    F2             = (int)sf::Keyboard::Scan::F2,              //!< Keyboard F2 key
    F3             = (int)sf::Keyboard::Scan::F3,              //!< Keyboard F3 key
    F4             = (int)sf::Keyboard::Scan::F4,              //!< Keyboard F4 key
    F5             = (int)sf::Keyboard::Scan::F5,              //!< Keyboard F5 key
    F6             = (int)sf::Keyboard::Scan::F6,              //!< Keyboard F6 key
    F7             = (int)sf::Keyboard::Scan::F7,              //!< Keyboard F7 key
    F8             = (int)sf::Keyboard::Scan::F8,              //!< Keyboard F8 key
    F9             = (int)sf::Keyboard::Scan::F9,              //!< Keyboard F9 key
    F10            = (int)sf::Keyboard::Scan::F10,             //!< Keyboard F10 key
    F11            = (int)sf::Keyboard::Scan::F11,             //!< Keyboard F11 key
    F12            = (int)sf::Keyboard::Scan::F12,             //!< Keyboard F12 key
    F13            = (int)sf::Keyboard::Scan::F13,             //!< Keyboard F13 key
    F14            = (int)sf::Keyboard::Scan::F14,             //!< Keyboard F14 key
    F15            = (int)sf::Keyboard::Scan::F15,             //!< Keyboard F15 key
    F16            = (int)sf::Keyboard::Scan::F16,             //!< Keyboard F16 key
    F17            = (int)sf::Keyboard::Scan::F17,             //!< Keyboard F17 key
    F18            = (int)sf::Keyboard::Scan::F18,             //!< Keyboard F18 key
    F19            = (int)sf::Keyboard::Scan::F19,             //!< Keyboard F19 key
    F20            = (int)sf::Keyboard::Scan::F20,             //!< Keyboard F20 key
    F21            = (int)sf::Keyboard::Scan::F21,             //!< Keyboard F21 key
    F22            = (int)sf::Keyboard::Scan::F22,             //!< Keyboard F22 key
    F23            = (int)sf::Keyboard::Scan::F23,             //!< Keyboard F23 key
    F24            = (int)sf::Keyboard::Scan::F24,             //!< Keyboard F24 key
    CapsLock       = (int)sf::Keyboard::Scan::CapsLock,        //!< Keyboard Caps %Lock key
    PrintScreen    = (int)sf::Keyboard::Scan::PrintScreen,     //!< Keyboard Print Screen key
    ScrollLock     = (int)sf::Keyboard::Scan::ScrollLock,      //!< Keyboard Scroll %Lock key
    Pause          = (int)sf::Keyboard::Scan::Pause,           //!< Keyboard Pause key
    Insert         = (int)sf::Keyboard::Scan::Insert,          //!< Keyboard Insert key
    Home           = (int)sf::Keyboard::Scan::Home,            //!< Keyboard Home key
    PageUp         = (int)sf::Keyboard::Scan::PageUp,          //!< Keyboard Page Up key
    Delete         = (int)sf::Keyboard::Scan::Delete,          //!< Keyboard Delete Forward key
    End            = (int)sf::Keyboard::Scan::End,             //!< Keyboard End key
    PageDown       = (int)sf::Keyboard::Scan::PageDown,        //!< Keyboard Page Down key
    Right          = (int)sf::Keyboard::Scan::Right,           //!< Keyboard Right Arrow key
    Left           = (int)sf::Keyboard::Scan::Left,            //!< Keyboard Left Arrow key
    Down           = (int)sf::Keyboard::Scan::Down,            //!< Keyboard Down Arrow key
    Up             = (int)sf::Keyboard::Scan::Up,              //!< Keyboard Up Arrow key
    NumLock        = (int)sf::Keyboard::Scan::NumLock,         //!< Keypad Num %Lock and Clear key
    NumpadDivide   = (int)sf::Keyboard::Scan::NumpadDivide,    //!< Keypad / key
    NumpadMultiply = (int)sf::Keyboard::Scan::NumpadMultiply,  //!< Keypad * key
    NumpadMinus    = (int)sf::Keyboard::Scan::NumpadMinus,     //!< Keypad - key
    NumpadPlus     = (int)sf::Keyboard::Scan::NumpadPlus,      //!< Keypad + key
    NumpadEqual    = (int)sf::Keyboard::Scan::NumpadEqual,     //!< keypad = key
    NumpadEnter    = (int)sf::Keyboard::Scan::NumpadEnter,     //!< Keypad Enter/Return key
    NumpadDecimal  = (int)sf::Keyboard::Scan::NumpadDecimal,   //!< Keypad . and Delete key
    Numpad1        = (int)sf::Keyboard::Scan::Numpad1,         //!< Keypad 1 and End key
    Numpad2        = (int)sf::Keyboard::Scan::Numpad2,         //!< Keypad 2 and Down Arrow key
    Numpad3        = (int)sf::Keyboard::Scan::Numpad3,         //!< Keypad 3 and Page Down key
    Numpad4        = (int)sf::Keyboard::Scan::Numpad4,         //!< Keypad 4 and Left Arrow key
    Numpad5        = (int)sf::Keyboard::Scan::Numpad5,         //!< Keypad 5 key
    Numpad6        = (int)sf::Keyboard::Scan::Numpad6,         //!< Keypad 6 and Right Arrow key
    Numpad7        = (int)sf::Keyboard::Scan::Numpad7,         //!< Keypad 7 and Home key
    Numpad8        = (int)sf::Keyboard::Scan::Numpad8,         //!< Keypad 8 and Up Arrow key
    Numpad9        = (int)sf::Keyboard::Scan::Numpad9,         //!< Keypad 9 and Page Up key
    Numpad0        = (int)sf::Keyboard::Scan::Numpad0,         //!< Keypad 0 and Insert key
#elif LYS_WINDOW_BACKEND == LYS_WINDOW_BACKEND_RAYLIB
    A =

#endif
};

class Inputs
{
public:
#if 1
    static void OnSFMLText(const sf::Event::TextEntered& text)
    {
        if (char_code_count < char_codes.size())
        {
            char_codes[char_code_count] = text.unicode;
            char_code_count++;
        }
    }
#endif
    /// Call at the end of the frame
    static void Refresh(void)
    {
#if 1
        char_code_count    = 0;
        next_char_code_idx = 0;
        for (std::size_t ii = 0; ii < prev_key_state_down.size(); ii++)
        {
            prev_key_state_down.set(ii, sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scan>(ii)));
        }
#else
#endif
    }

    static bool KeyboardIsKeyPressed(lys::KeyId key)
    {
#if 1
        return KeyboardIsKeyDown(key) && prev_key_state_down.test(static_cast<std::size_t>(key)) == false;
#else
#endif
    }
    static bool KeyboardIsKeyReleased(lys::KeyId key)
    {
#if 1
        return KeyboardIsKeyUp(key) && prev_key_state_down.test(static_cast<std::size_t>(key)) == true;
#else
#endif
    }
    static bool KeyboardIsKeyDown(lys::KeyId key)
    {
#if 1
        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(key)) == true;
#else
#endif
    }
    static bool KeyboardIsKeyUp(lys::KeyId key)
    {
#if 1
        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Scancode>(key)) == false;
#else
#endif
    }

    static bool ExtractText(uint32_t unicode)
    {
        if (next_char_code_idx >= char_code_count)
        {
            return false;
        }
        unicode = char_codes[next_char_code_idx];
        next_char_code_idx++;
        return true;
    }

private:
#if 1
    /// 16 * uint32_t
    static std::array<uint32_t, 15> char_codes;
    static uint8_t char_code_count;
    static uint8_t next_char_code_idx;

    ///
    static std::bitset<sf::Keyboard::ScancodeCount> prev_key_state_down;
#endif
};

}  // namespace lys

#endif  // _LYS_WINDOW_INPUT_HPP
