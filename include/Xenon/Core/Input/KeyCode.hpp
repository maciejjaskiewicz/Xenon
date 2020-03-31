#pragma once

#include <cstdint>

// Printable keys
constexpr uint16_t XN_KEY_SPACE = 32;
constexpr uint16_t XN_KEY_APOSTROPHE = 39;  /* ' */
constexpr uint16_t XN_KEY_COMMA = 44;  /* , */
constexpr uint16_t XN_KEY_MINUS = 45;  /* - */
constexpr uint16_t XN_KEY_PERIOD = 46;  /* . */
constexpr uint16_t XN_KEY_SLASH = 47;  /* / */

constexpr uint16_t XN_KEY_0 = 48;
constexpr uint16_t XN_KEY_1 = 49;
constexpr uint16_t XN_KEY_2 = 50;
constexpr uint16_t XN_KEY_3 = 51;
constexpr uint16_t XN_KEY_4 = 52;
constexpr uint16_t XN_KEY_5 = 53;
constexpr uint16_t XN_KEY_6 = 54;
constexpr uint16_t XN_KEY_7 = 55;
constexpr uint16_t XN_KEY_8 = 56;
constexpr uint16_t XN_KEY_9 = 57;

constexpr uint16_t XN_KEY_SEMICOLON = 59;  /* ; */
constexpr uint16_t XN_KEY_EQUAL = 61;  /* = */

constexpr uint16_t XN_KEY_A = 65;
constexpr uint16_t XN_KEY_B = 66;
constexpr uint16_t XN_KEY_C = 67;
constexpr uint16_t XN_KEY_D = 68;
constexpr uint16_t XN_KEY_E = 69;
constexpr uint16_t XN_KEY_F = 70;
constexpr uint16_t XN_KEY_G = 71;
constexpr uint16_t XN_KEY_H = 72;
constexpr uint16_t XN_KEY_I = 73;
constexpr uint16_t XN_KEY_J = 74;
constexpr uint16_t XN_KEY_K = 75;
constexpr uint16_t XN_KEY_L = 76;
constexpr uint16_t XN_KEY_M = 77;
constexpr uint16_t XN_KEY_N = 78;
constexpr uint16_t XN_KEY_O = 79;
constexpr uint16_t XN_KEY_P = 80;
constexpr uint16_t XN_KEY_Q = 81;
constexpr uint16_t XN_KEY_R = 82;
constexpr uint16_t XN_KEY_S = 83;
constexpr uint16_t XN_KEY_T = 84;
constexpr uint16_t XN_KEY_U = 85;
constexpr uint16_t XN_KEY_V = 86;
constexpr uint16_t XN_KEY_W = 87;
constexpr uint16_t XN_KEY_X = 88;
constexpr uint16_t XN_KEY_Y = 89;
constexpr uint16_t XN_KEY_Z = 90;

constexpr uint16_t XN_KEY_LEFT_BRACKET = 91;  /* [ */
constexpr uint16_t XN_KEY_BACKSLASH = 92;  /* \ */
constexpr uint16_t XN_KEY_RIGHT_BRACKET = 93;  /* ] */
constexpr uint16_t XN_KEY_GRAVE_ACCENT = 96;  /* ` */
constexpr uint16_t XN_KEY_WORLD_1 = 161; /* non-US #1 */
constexpr uint16_t XN_KEY_WORLD_2 = 162; /* non-US #2 */

// Function keys
constexpr uint16_t XN_KEY_ESCAPE = 256;
constexpr uint16_t XN_KEY_ENTER = 257;
constexpr uint16_t XN_KEY_TAB = 258;
constexpr uint16_t XN_KEY_BACKSPACE = 259;
constexpr uint16_t XN_KEY_INSERT = 260;
constexpr uint16_t XN_KEY_DELETE = 261;
constexpr uint16_t XN_KEY_RIGHT = 262;
constexpr uint16_t XN_KEY_LEFT = 263;
constexpr uint16_t XN_KEY_DOWN = 264;
constexpr uint16_t XN_KEY_UP = 265;
constexpr uint16_t XN_KEY_PAGE_UP = 266;
constexpr uint16_t XN_KEY_PAGE_DOWN = 267;
constexpr uint16_t XN_KEY_HOME = 268;
constexpr uint16_t XN_KEY_END = 269;
constexpr uint16_t XN_KEY_CAPS_LOCK = 280;
constexpr uint16_t XN_KEY_SCROLL_LOCK = 281;
constexpr uint16_t XN_KEY_NUM_LOCK = 282;
constexpr uint16_t XN_KEY_PRINT_SCREEN = 283;
constexpr uint16_t XN_KEY_PAUSE = 284;

constexpr uint16_t XN_KEY_F1 = 290;
constexpr uint16_t XN_KEY_F2 = 291;
constexpr uint16_t XN_KEY_F3 = 292;
constexpr uint16_t XN_KEY_F4 = 293;
constexpr uint16_t XN_KEY_F5 = 294;
constexpr uint16_t XN_KEY_F6 = 295;
constexpr uint16_t XN_KEY_F7 = 296;
constexpr uint16_t XN_KEY_F8 = 297;
constexpr uint16_t XN_KEY_F9 = 298;
constexpr uint16_t XN_KEY_F10 = 299;
constexpr uint16_t XN_KEY_F11 = 300;
constexpr uint16_t XN_KEY_F12 = 301;
constexpr uint16_t XN_KEY_F13 = 302;
constexpr uint16_t XN_KEY_F14 = 303;
constexpr uint16_t XN_KEY_F15 = 304;
constexpr uint16_t XN_KEY_F16 = 305;
constexpr uint16_t XN_KEY_F17 = 306;
constexpr uint16_t XN_KEY_F18 = 307;
constexpr uint16_t XN_KEY_F19 = 308;
constexpr uint16_t XN_KEY_F20 = 309;
constexpr uint16_t XN_KEY_F21 = 310;
constexpr uint16_t XN_KEY_F22 = 311;
constexpr uint16_t XN_KEY_F23 = 312;
constexpr uint16_t XN_KEY_F24 = 313;
constexpr uint16_t XN_KEY_F25 = 314;

constexpr uint16_t XN_KEY_KP_0 = 320;
constexpr uint16_t XN_KEY_KP_1 = 321;
constexpr uint16_t XN_KEY_KP_2 = 322;
constexpr uint16_t XN_KEY_KP_3 = 323;
constexpr uint16_t XN_KEY_KP_4 = 324;
constexpr uint16_t XN_KEY_KP_5 = 325;
constexpr uint16_t XN_KEY_KP_6 = 326;
constexpr uint16_t XN_KEY_KP_7 = 327;
constexpr uint16_t XN_KEY_KP_8 = 328;
constexpr uint16_t XN_KEY_KP_9 = 329;

constexpr uint16_t XN_KEY_KP_DECIMAL = 330;
constexpr uint16_t XN_KEY_KP_DIVIDE = 331;
constexpr uint16_t XN_KEY_KP_MULTIPLY = 332;
constexpr uint16_t XN_KEY_KP_SUBTRACT = 333;
constexpr uint16_t XN_KEY_KP_ADD = 334;
constexpr uint16_t XN_KEY_KP_ENTER = 335;
constexpr uint16_t XN_KEY_KP_EQUAL = 336;

constexpr uint16_t XN_KEY_LEFT_SHIFT = 340;
constexpr uint16_t XN_KEY_LEFT_CONTROL = 341;
constexpr uint16_t XN_KEY_LEFT_ALT = 342;
constexpr uint16_t XN_KEY_LEFT_SUPER = 343;
constexpr uint16_t XN_KEY_RIGHT_SHIFT = 344;
constexpr uint16_t XN_KEY_RIGHT_CONTROL = 345;
constexpr uint16_t XN_KEY_RIGHT_ALT = 346;
constexpr uint16_t XN_KEY_RIGHT_SUPER = 347;
constexpr uint16_t XN_KEY_MENU = 348;

namespace Xenon
{
    enum class KeyCode : uint16_t
    {
        Space = XN_KEY_SPACE,
        Apostrophe = XN_KEY_APOSTROPHE,
        Comma = XN_KEY_COMMA,
        Minus = XN_KEY_MINUS,
        Period = XN_KEY_PERIOD,
        Slash = XN_KEY_SLASH,

        D0 = XN_KEY_0,
        D1 = XN_KEY_1,
        D2 = XN_KEY_2,
        D3 = XN_KEY_3,
        D4 = XN_KEY_4,
        D5 = XN_KEY_5,
        D6 = XN_KEY_6,
        D7 = XN_KEY_7,
        D8 = XN_KEY_8,
        D9 = XN_KEY_9,

        Semicolon = XN_KEY_SEMICOLON,
        Equal = XN_KEY_EQUAL,

        A = XN_KEY_A,
        B = XN_KEY_B,
        C = XN_KEY_C,
        D = XN_KEY_D,
        E = XN_KEY_E,
        F = XN_KEY_F,
        G = XN_KEY_G,
        H = XN_KEY_H,
        I = XN_KEY_I,
        J = XN_KEY_J,
        K = XN_KEY_K,
        L = XN_KEY_L,
        M = XN_KEY_M,
        N = XN_KEY_N,
        O = XN_KEY_O,
        P = XN_KEY_P,
        Q = XN_KEY_Q,
        R = XN_KEY_R,
        S = XN_KEY_S,
        T = XN_KEY_T,
        U = XN_KEY_U,
        V = XN_KEY_V,
        W = XN_KEY_W,
        X = XN_KEY_X,
        Y = XN_KEY_Y,
        Z = XN_KEY_Z,

        LeftBracket = XN_KEY_LEFT_BRACKET,
        Backslash = XN_KEY_BACKSLASH,
        RightBracket = XN_KEY_RIGHT_BRACKET,
        GraveAccent = XN_KEY_GRAVE_ACCENT,

        World1 = XN_KEY_WORLD_1,
        World2 = XN_KEY_WORLD_2,

        //Function keys
        Escape = XN_KEY_ESCAPE,
        Enter = XN_KEY_ENTER,
        Tab = XN_KEY_TAB,
        Backspace = XN_KEY_BACKSPACE,
        Insert = XN_KEY_INSERT,
        Delete = XN_KEY_DELETE,
        Right = XN_KEY_RIGHT,
        Left = XN_KEY_LEFT,
        Down = XN_KEY_DOWN,
        Up = XN_KEY_UP,
        PageUp = XN_KEY_PAGE_UP,
        PageDown = XN_KEY_PAGE_DOWN,
        Home = XN_KEY_HOME,
        End = XN_KEY_END,
        CapsLock = XN_KEY_CAPS_LOCK,
        ScrollLock = XN_KEY_SCROLL_LOCK,
        NumLock = XN_KEY_NUM_LOCK,
        PrintScreen = XN_KEY_PRINT_SCREEN,
        Pause = XN_KEY_PAUSE,
        F1 = XN_KEY_F1,
        F2 = XN_KEY_F2,
        F3 = XN_KEY_F3,
        F4 = XN_KEY_F4,
        F5 = XN_KEY_F5,
        F6 = XN_KEY_F6,
        F7 = XN_KEY_F7,
        F8 = XN_KEY_F8,
        F9 = XN_KEY_F9,
        F10 = XN_KEY_F10,
        F11 = XN_KEY_F11,
        F12 = XN_KEY_F12,
        F13 = XN_KEY_F13,
        F14 = XN_KEY_F14,
        F15 = XN_KEY_F15,
        F16 = XN_KEY_F16,
        F17 = XN_KEY_F17,
        F18 = XN_KEY_F18,
        F19 = XN_KEY_F19,
        F20 = XN_KEY_F20,
        F21 = XN_KEY_F21,
        F22 = XN_KEY_F22,
        F23 = XN_KEY_F23,
        F24 = XN_KEY_F24,
        F25 = XN_KEY_F25,

        // Keypad 
        Kp0 = XN_KEY_KP_0,
        Kp1 = XN_KEY_KP_1,
        Kp2 = XN_KEY_KP_2,
        Kp3 = XN_KEY_KP_3,
        Kp4 = XN_KEY_KP_4,
        Kp5 = XN_KEY_KP_5,
        Kp6 = XN_KEY_KP_6,
        Kp7 = XN_KEY_KP_7,
        Kp8 = XN_KEY_KP_8,
        Kp9 = XN_KEY_KP_9,
        KpDecimal = XN_KEY_KP_DECIMAL,
        KpDivide = XN_KEY_KP_DIVIDE,
        KpMultiply = XN_KEY_KP_MULTIPLY,
        KpSubtract = XN_KEY_KP_SUBTRACT,
        KpAdd = XN_KEY_KP_ADD,
        KpEnter = XN_KEY_KP_ENTER,
        KpEqual = XN_KEY_KP_EQUAL,

        LeftShift = XN_KEY_LEFT_SHIFT,
        LeftControl = XN_KEY_LEFT_CONTROL,
        LeftAlt = XN_KEY_LEFT_ALT,
        LeftSuper = XN_KEY_LEFT_SUPER,
        RightShift = XN_KEY_RIGHT_SHIFT,
        RightControl = XN_KEY_RIGHT_CONTROL,
        RightAlt = XN_KEY_RIGHT_ALT,
        RightSuper = XN_KEY_RIGHT_SUPER,
        Menu = XN_KEY_MENU
    };

    inline bool operator==(const KeyCode keyCode, const uint16_t keyCodeInt)
    {
        return static_cast<uint16_t>(keyCode) == keyCodeInt;
    }
}