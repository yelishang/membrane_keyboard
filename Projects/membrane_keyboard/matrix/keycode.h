/*
 * Keycodes based on HID Keyboard/Keypad Usage Page (0x07) plus media keys from Generic Desktop Page (0x01) and Consumer Page (0x0C)
 *
 * See https://web.archive.org/web/20060218214400/http://www.usb.org/developers/devclass_docs/Hut1_12.pdf
 * or http://www.usb.org/developers/hidpage/Hut1_12v2.pdf (older)
 */

#pragma once
#include "mono.h"
#include "main.h"
#define QK_MOMENTARY             0x5100

/* FIXME: Add doxygen comments here */

#define IS_ERROR(code)           (KC_ROLL_OVER <= (code) && (code) <= KC_UNDEFINED)
#define IS_ANY(code)             (KC_A <= (code) && (code) <= 0xFF)
#define IS_KEY(code)             (KC_A <= (code) && (code) <= KC_EXSEL)
#define IS_MOD(code)             (KC_LEFT_CTRL <= (code) && (code) <= KC_RIGHT_GUI)
#define IS_RGB(code)             (RGB_TOG <= (code) && (code) <= RGB_M_T)
#define IS_BLE(code)             (BLE_DEV1 <= (code) && (code) <= BLE_DEV3)
#define IS_WIRELESS(code)        (WIL_DEV == (code))
#define IS_SYSTEM(code)          ((code) >= KC_SYSTEM_POWER && (code) <= KC_SYSTEM_WAKE)
#define IS_CUSTOMER(code)        (KC_AUDIO_MUTE <= (code) && (code) <= KC_BRIGHTNESS_DOWN)
#define IS_FN(code)              (((code)&QK_MOMENTARY) == QK_MOMENTARY)

#define IS_SPECIAL(code)         ((0xA5 <= (code) && (code) <= 0xDF) || (0xE8 <= (code) && (code) <= 0xFF))
#define IS_CONSUMER(code)        (KC_MUTE <= (code) && (code) <= KC_BRID)

#define IS_MOUSEKEY(code)        (KC_MS_UP <= (code) && (code) <= KC_MS_ACCEL2)
#define IS_MOUSEKEY_MOVE(code)   (KC_MS_UP <= (code) && (code) <= KC_MS_RIGHT)
#define IS_MOUSEKEY_BUTTON(code) (KC_MS_BTN1 <= (code) && (code) <= KC_MS_BTN8)
#define IS_MOUSEKEY_WHEEL(code)  (KC_MS_WH_UP <= (code) && (code) <= KC_MS_WH_RIGHT)
#define IS_MOUSEKEY_ACCEL(code)  (KC_MS_ACCEL0 <= (code) && (code) <= KC_MS_ACCEL2)

#define MOD_BIT(code)            (1 << MOD_INDEX(code))
#define MOD_INDEX(code)          ((code)&0x07)

#define MOD_MASK_CTRL            (MOD_BIT(KC_LEFT_CTRL) | MOD_BIT(KC_RIGHT_CTRL))
#define MOD_MASK_SHIFT           (MOD_BIT(KC_LEFT_SHIFT) | MOD_BIT(KC_RIGHT_SHIFT))
#define MOD_MASK_ALT             (MOD_BIT(KC_LEFT_ALT) | MOD_BIT(KC_RIGHT_ALT))
#define MOD_MASK_GUI             (MOD_BIT(KC_LEFT_GUI) | MOD_BIT(KC_RIGHT_GUI))
#define MOD_MASK_CS              (MOD_MASK_CTRL | MOD_MASK_SHIFT)
#define MOD_MASK_CA              (MOD_MASK_CTRL | MOD_MASK_ALT)
#define MOD_MASK_CG              (MOD_MASK_CTRL | MOD_MASK_GUI)
#define MOD_MASK_SA              (MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_SG              (MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_AG              (MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSA             (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT)
#define MOD_MASK_CSG             (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_GUI)
#define MOD_MASK_CAG             (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_SAG             (MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)
#define MOD_MASK_CSAG            (MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)

// Momentary switch layer - 256 layer max
#define MO(layer)                (QK_MOMENTARY | ((layer)&0xFF))

// clang-format off

/*
 * Short names for ease of definition of keymap
 */
/* Transparent */
#define KC_TRANSPARENT 0x01
#define KC_TRNS KC_TRANSPARENT

/* Punctuation */
#define ___ KC_NO
#define _______ KC_NO
#define KC_ENT  KC_ENTER
#define KC_ESC  KC_ESCAPE
#define KC_BSPC KC_BACKSPACE
#define KC_SPC  KC_SPACE
#define KC_MINS KC_MINUS
#define KC_EQL  KC_EQUAL
#define KC_LBRC KC_LEFT_BRACKET
#define KC_RBRC KC_RIGHT_BRACKET
#define KC_BSLS KC_BACKSLASH
#define KC_NUHS KC_NONUS_HASH
#define KC_SCLN KC_SEMICOLON
#define KC_QUOT KC_QUOTE
#define KC_GRV  KC_GRAVE
#define KC_COMM KC_COMMA
#define KC_SLSH KC_SLASH
#define KC_NUBS KC_NONUS_BACKSLASH

/* Lock Keys */
#define KC_CAPS KC_CAPS_LOCK
#define KC_SCRL KC_SCROLL_LOCK
#define KC_NUM  KC_NUM_LOCK
#define KC_LCAP KC_LOCKING_CAPS_LOCK
#define KC_LNUM KC_LOCKING_NUM_LOCK
#define KC_LSCR KC_LOCKING_SCROLL_LOCK

/* Commands */
#define KC_PSCR KC_PRINT_SCREEN
#define KC_PAUS KC_PAUSE
#define KC_BRK  KC_PAUSE
#define KC_INS  KC_INSERT
#define KC_PGUP KC_PAGE_UP
#define KC_DEL  KC_DELETE
#define KC_PGDN KC_PAGE_DOWN
#define KC_RGHT KC_RIGHT
#define KC_APP  KC_APPLICATION
#define KC_EXEC KC_EXECUTE
#define KC_SLCT KC_SELECT
#define KC_AGIN KC_AGAIN
#define KC_PSTE KC_PASTE
#define KC_ERAS KC_ALTERNATE_ERASE
#define KC_SYRQ KC_SYSTEM_REQUEST
#define KC_CNCL KC_CANCEL
#define KC_CLR  KC_CLEAR
#define KC_PRIR KC_PRIOR
#define KC_RETN KC_RETURN
#define KC_SEPR KC_SEPARATOR
#define KC_CLAG KC_CLEAR_AGAIN
#define KC_CRSL KC_CRSEL
#define KC_EXSL KC_EXSEL

/* Keypad */
#define KC_PSLS KC_KP_SLASH
#define KC_PAST KC_KP_ASTERISK
#define KC_PMNS KC_KP_MINUS
#define KC_PPLS KC_KP_PLUS
#define KC_PENT KC_KP_ENTER
#define KC_P1   KC_KP_1
#define KC_P2   KC_KP_2
#define KC_P3   KC_KP_3
#define KC_P4   KC_KP_4
#define KC_P5   KC_KP_5
#define KC_P6   KC_KP_6
#define KC_P7   KC_KP_7
#define KC_P8   KC_KP_8
#define KC_P9   KC_KP_9
#define KC_P0   KC_KP_0
#define KC_PDOT KC_KP_DOT
#define KC_PEQL KC_KP_EQUAL
#define KC_PCMM KC_KP_COMMA

/* Language Specific */
#define KC_INT1 KC_INTERNATIONAL_1
#define KC_INT2 KC_INTERNATIONAL_2
#define KC_INT3 KC_INTERNATIONAL_3
#define KC_INT4 KC_INTERNATIONAL_4
#define KC_INT5 KC_INTERNATIONAL_5
#define KC_INT6 KC_INTERNATIONAL_6
#define KC_INT7 KC_INTERNATIONAL_7
#define KC_INT8 KC_INTERNATIONAL_8
#define KC_INT9 KC_INTERNATIONAL_9
#define KC_LNG1 KC_LANGUAGE_1
#define KC_LNG2 KC_LANGUAGE_2
#define KC_LNG3 KC_LANGUAGE_3
#define KC_LNG4 KC_LANGUAGE_4
#define KC_LNG5 KC_LANGUAGE_5
#define KC_LNG6 KC_LANGUAGE_6
#define KC_LNG7 KC_LANGUAGE_7
#define KC_LNG8 KC_LANGUAGE_8
#define KC_LNG9 KC_LANGUAGE_9

/* Modifiers */
#define KC_LCTL KC_LEFT_CTRL
#define KC_LSFT KC_LEFT_SHIFT
#define KC_LALT KC_LEFT_ALT
#define KC_LOPT KC_LEFT_ALT
#define KC_LGUI KC_LEFT_GUI
#define KC_LCMD KC_LEFT_GUI
#define KC_LWIN KC_LEFT_GUI
#define KC_RCTL KC_RIGHT_CTRL
#define KC_RSFT KC_RIGHT_SHIFT
#define KC_RALT KC_RIGHT_ALT
#define KC_ALGR KC_RIGHT_ALT
#define KC_ROPT KC_RIGHT_ALT
#define KC_RGUI KC_RIGHT_GUI
#define KC_RCMD KC_RIGHT_GUI
#define KC_RWIN KC_RIGHT_GUI

/* Generic Desktop Page (0x01) */
#define KC_PWR  KC_SYSTEM_POWER
#define KC_SLEP KC_SYSTEM_SLEEP
#define KC_WAKE KC_SYSTEM_WAKE

/* Consumer Page (0x0C) */
#define KC_MUTE KC_AUDIO_MUTE
#define KC_VOLU KC_AUDIO_VOL_UP
#define KC_VOLD KC_AUDIO_VOL_DOWN
#define KC_MNXT KC_MEDIA_NEXT_TRACK
#define KC_MPRV KC_MEDIA_PREV_TRACK
#define KC_MSTP KC_MEDIA_STOP
#define KC_MPLY KC_MEDIA_PLAY_PAUSE
#define KC_MSEL KC_MEDIA_SELECT
#define KC_EJCT KC_MEDIA_EJECT
#define KC_CALC KC_CALCULATOR
#define KC_MYCM KC_MY_COMPUTER
#define KC_WSCH KC_WWW_SEARCH
#define KC_WHOM KC_WWW_HOME
#define KC_WBAK KC_WWW_BACK
#define KC_WFWD KC_WWW_FORWARD
#define KC_WSTP KC_WWW_STOP
#define KC_WREF KC_WWW_REFRESH
#define KC_WFAV KC_WWW_FAVORITES
#define KC_MFFD KC_MEDIA_FAST_FORWARD
#define KC_MRWD KC_MEDIA_REWIND
#define KC_BRIU KC_BRIGHTNESS_UP
#define KC_BRID KC_BRIGHTNESS_DOWN

/* System Specific */
#define KC_BRMU KC_PAUSE
#define KC_BRMD KC_SCROLL_LOCK

/* Mouse Keys */
#define KC_MS_U KC_MS_UP
#define KC_MS_D KC_MS_DOWN
#define KC_MS_L KC_MS_LEFT
#define KC_MS_R KC_MS_RIGHT
#define KC_BTN1 KC_MS_BTN1
#define KC_BTN2 KC_MS_BTN2
#define KC_BTN3 KC_MS_BTN3
#define KC_BTN4 KC_MS_BTN4
#define KC_BTN5 KC_MS_BTN5
#define KC_BTN6 KC_MS_BTN6
#define KC_BTN7 KC_MS_BTN7
#define KC_BTN8 KC_MS_BTN8
#define KC_WH_U KC_MS_WH_UP
#define KC_WH_D KC_MS_WH_DOWN
#define KC_WH_L KC_MS_WH_LEFT
#define KC_WH_R KC_MS_WH_RIGHT
#define KC_ACL0 KC_MS_ACCEL0
#define KC_ACL1 KC_MS_ACCEL1
#define KC_ACL2 KC_MS_ACCEL2

/* RGB keys */
#define RGB_TOG 0x5CC3
#define RGB_MOD 0x5CC4
#define RGB_RMOD 0x5CC5
#define RGB_M_P 0x5CCE
#define RGB_M_B 0x5CCF
#define RGB_M_R 0x5CD0
#define RGB_M_SW 0x5CD1
#define RGB_M_SN 0x5CD2
#define RGB_M_K 0x5CD3
#define RGB_M_X 0x5CD4
#define RGB_M_G 0x5CD5
#define RGB_M_T 0x5CD6

/* BLE keys */
#define BLE_DEV1 0x6001
#define BLE_DEV2 0x6002
#define BLE_DEV3 0x6003

/* BLE keys */
#define WIL_DEV 0x60FF
// clang-format on

/* Keyboard/Keypad Page (0x07) */
enum hid_keyboard_keypad_usage
{
  KC_NO = 0x00,
  KC_ROLL_OVER,
  KC_POST_FAIL,
  KC_UNDEFINED,
  KC_A,
  KC_B,
  KC_C,
  KC_D,
  KC_E,
  KC_F,
  KC_G,
  KC_H,
  KC_I,
  KC_J,
  KC_K,
  KC_L,
  KC_M, // 0x10
  KC_N,
  KC_O,
  KC_P,
  KC_Q,
  KC_R,
  KC_S,
  KC_T,
  KC_U,
  KC_V,
  KC_W,
  KC_X,
  KC_Y,
  KC_Z,
  KC_1,
  KC_2,
  KC_3, // 0x20
  KC_4,
  KC_5,
  KC_6,
  KC_7,
  KC_8,
  KC_9,
  KC_0,
  KC_ENTER,
  KC_ESCAPE,
  KC_BACKSPACE,
  KC_TAB,
  KC_SPACE,
  KC_MINUS,
  KC_EQUAL,
  KC_LEFT_BRACKET,
  KC_RIGHT_BRACKET, // 0x30
  KC_BACKSLASH,
  KC_NONUS_HASH,
  KC_SEMICOLON,
  KC_QUOTE,
  KC_GRAVE,
  KC_COMMA,
  KC_DOT,
  KC_SLASH,
  KC_CAPS_LOCK,
  KC_F1,
  KC_F2,
  KC_F3,
  KC_F4,
  KC_F5,
  KC_F6,
  KC_F7, // 0x40
  KC_F8,
  KC_F9,
  KC_F10,
  KC_F11,
  KC_F12,
  KC_PRINT_SCREEN,
  KC_SCROLL_LOCK,
  KC_PAUSE,
  KC_INSERT,
  KC_HOME,
  KC_PAGE_UP,
  KC_DELETE,
  KC_END,
  KC_PAGE_DOWN,
  KC_RIGHT,
  KC_LEFT, // 0x50
  KC_DOWN,
  KC_UP,
  KC_NUM_LOCK,
  KC_KP_SLASH,
  KC_KP_ASTERISK,
  KC_KP_MINUS,
  KC_KP_PLUS,
  KC_KP_ENTER,
  KC_KP_1,
  KC_KP_2,
  KC_KP_3,
  KC_KP_4,
  KC_KP_5,
  KC_KP_6,
  KC_KP_7,
  KC_KP_8, // 0x60
  KC_KP_9,
  KC_KP_0,
  KC_KP_DOT,
  KC_NONUS_BACKSLASH,
  KC_APPLICATION,
  KC_KB_POWER,
  KC_KP_EQUAL,
  KC_F13,
  KC_F14,
  KC_F15,
  KC_F16,
  KC_F17,
  KC_F18,
  KC_F19,
  KC_F20,
  KC_F21, // 0x70
  KC_F22,
  KC_F23,
  KC_F24,
  KC_EXECUTE,
  KC_HELP,
  KC_MENU,
  KC_SELECT,
  KC_STOP,
  KC_AGAIN,
  KC_UNDO,
  KC_CUT,
  KC_COPY,
  KC_PASTE,
  KC_FIND,
  KC_KB_MUTE,
  KC_KB_VOLUME_UP, // 0x80
  KC_KB_VOLUME_DOWN,
  KC_LOCKING_CAPS_LOCK,
  KC_LOCKING_NUM_LOCK,
  KC_LOCKING_SCROLL_LOCK,
  KC_KP_COMMA,
  KC_KP_EQUAL_AS400,
  KC_INTERNATIONAL_1,
  KC_INTERNATIONAL_2,
  KC_INTERNATIONAL_3,
  KC_INTERNATIONAL_4,
  KC_INTERNATIONAL_5,
  KC_INTERNATIONAL_6,
  KC_INTERNATIONAL_7,
  KC_INTERNATIONAL_8,
  KC_INTERNATIONAL_9,
  KC_LANGUAGE_1, // 0x90
  KC_LANGUAGE_2,
  KC_LANGUAGE_3,
  KC_LANGUAGE_4,
  KC_LANGUAGE_5,
  KC_LANGUAGE_6,
  KC_LANGUAGE_7,
  KC_LANGUAGE_8,
  KC_LANGUAGE_9,
  KC_ALTERNATE_ERASE,
  KC_SYSTEM_REQUEST,
  KC_CANCEL,
  KC_CLEAR,
  KC_PRIOR,
  KC_RETURN,
  KC_SEPARATOR,
  KC_OUT, // 0xA0
  KC_OPER,
  KC_CLEAR_AGAIN,
  KC_CRSEL,
  KC_EXSEL,

#if 0
  // ***************************************************************
  // These keycodes are present in the HID spec, but are           *
  // nonfunctional on modern OSes. QMK uses this range (0xA5-0xDF) *
  // for the media and function keys instead - see below.          *
  // ***************************************************************

  KC_KP_00                = 0xB0,
  KC_KP_000,
  KC_THOUSANDS_SEPARATOR,
  KC_DECIMAL_SEPARATOR,
  KC_CURRENCY_UNIT,
  KC_CURRENCY_SUB_UNIT,
  KC_KP_LEFT_PARENTHESIS,
  KC_KP_RIGHT_PARENTHESIS,
  KC_KP_LEFT_BRACE,
  KC_KP_RIGHT_BRACE,
  KC_KP_TAB,
  KC_KP_BACKSPACE,
  KC_KP_A,
  KC_KP_B,
  KC_KP_C,
  KC_KP_D,
  KC_KP_E,                //0xC0
  KC_KP_F,
  KC_KP_XOR,
  KC_KP_HAT,
  KC_KP_PERCENT,
  KC_KP_LESS_THAN,
  KC_KP_GREATER_THAN,
  KC_KP_AND,
  KC_KP_LAZY_AND,
  KC_KP_OR,
  KC_KP_LAZY_OR,
  KC_KP_COLON,
  KC_KP_HASH,
  KC_KP_SPACE,
  KC_KP_AT,
  KC_KP_EXCLAMATION,
  KC_KP_MEM_STORE,        //0xD0
  KC_KP_MEM_RECALL,
  KC_KP_MEM_CLEAR,
  KC_KP_MEM_ADD,
  KC_KP_MEM_SUB,
  KC_KP_MEM_MUL,
  KC_KP_MEM_DIV,
  KC_KP_PLUS_MINUS,
  KC_KP_CLEAR,
  KC_KP_CLEAR_ENTRY,
  KC_KP_BINARY,
  KC_KP_OCTAL,
  KC_KP_DECIMAL,
  KC_KP_HEXADECIMAL,
#endif

  /* Modifiers */
  KC_LEFT_CTRL = 0xE0,
  KC_LEFT_SHIFT,
  KC_LEFT_ALT,
  KC_LEFT_GUI,
  KC_RIGHT_CTRL,
  KC_RIGHT_SHIFT,
  KC_RIGHT_ALT,
  KC_RIGHT_GUI,
  
  QK_KB_0 = 0x7E00,
  QK_KB_1 = 0x7E01,
  QK_KB_2 = 0x7E02,
  QK_KB_3 = 0x7E03,
  QK_KB_4 = 0x7E04,
  QK_KB_5 = 0x7E05,
  QK_KB_6 = 0x7E06,
  QK_KB_7 = 0x7E07,
  QK_KB_8 = 0x7E08,
  QK_KB_9 = 0x7E09,
  QK_KB_10 = 0x7E0A,
  QK_KB_11 = 0x7E0B,
  QK_KB_12 = 0x7E0C,
  QK_KB_13 = 0x7E0D,
  QK_KB_14 = 0x7E0E,
  QK_KB_15 = 0x7E0F,
  QK_KB_16 = 0x7E10,
  QK_KB_17 = 0x7E11,
  QK_KB_18 = 0x7E12,
  QK_KB_19 = 0x7E13,
  QK_KB_20 = 0x7E14,
  QK_KB_21 = 0x7E15,
  QK_KB_22 = 0x7E16,
  QK_KB_23 = 0x7E17,
  QK_KB_24 = 0x7E18,
  QK_KB_25 = 0x7E19,
  QK_KB_26 = 0x7E1A,
  QK_KB_27 = 0x7E1B,
  QK_KB_28 = 0x7E1C,
  QK_KB_29 = 0x7E1D,
  QK_KB_30 = 0x7E1E,
  QK_KB_31 = 0x7E1F
  // **********************************************
  // * 0xF0-0xFF are unallocated in the HID spec. *
  // * QMK uses these for Mouse Keys - see below. *
  // **********************************************
};

/* Media and Function keys */
enum internal_special_keycodes
{
  /* Generic Desktop Page (0x01) */
  KC_SYSTEM_POWER = 0xA5,
  KC_SYSTEM_SLEEP,
  KC_SYSTEM_WAKE,

  /* Consumer Page (0x0C) */
  KC_AUDIO_MUTE,
  KC_AUDIO_VOL_UP,
  KC_AUDIO_VOL_DOWN,
  KC_MEDIA_NEXT_TRACK,
  KC_MEDIA_PREV_TRACK,
  KC_MEDIA_STOP,
  KC_MEDIA_PLAY_PAUSE,
  KC_MEDIA_SELECT,
  KC_MEDIA_EJECT, // 0xB0
  KC_MAIL,
  KC_CALCULATOR,
  KC_MY_COMPUTER,
  KC_WWW_SEARCH,
  KC_WWW_HOME,
  KC_WWW_BACK,
  KC_WWW_FORWARD,
  KC_WWW_STOP,
  KC_WWW_REFRESH,
  KC_WWW_FAVORITES,
  KC_MEDIA_FAST_FORWARD,
  KC_MEDIA_REWIND,
  KC_BRIGHTNESS_UP,
  KC_BRIGHTNESS_DOWN
};

enum desktop_usages {
    // 4.5.1 System Controls - Power Controls
    SYSTEM_POWER_DOWN             = 0x81,
    SYSTEM_SLEEP                  = 0x82,
    SYSTEM_WAKE_UP                = 0x83,
    SYSTEM_RESTART                = 0x8F,
    // 4.10 System Display Controls
    SYSTEM_DISPLAY_TOGGLE_INT_EXT = 0xB5
};

enum mouse_keys
{
/* Mouse Buttons */
#ifdef VIA_ENABLE
  KC_MS_UP = 0xF0,
#else
  KC_MS_UP = 0xED,
#endif
  KC_MS_DOWN,
  KC_MS_LEFT,
  KC_MS_RIGHT, // 0xF0
  KC_MS_BTN1,
  KC_MS_BTN2,
  KC_MS_BTN3,
  KC_MS_BTN4,
  KC_MS_BTN5,
#ifdef VIA_ENABLE
  KC_MS_BTN6 = KC_MS_BTN5,
  KC_MS_BTN7 = KC_MS_BTN5,
  KC_MS_BTN8 = KC_MS_BTN5,
#else
  KC_MS_BTN6,
  KC_MS_BTN7,
  KC_MS_BTN8,
#endif

  /* Mouse Wheel */
  KC_MS_WH_UP,
  KC_MS_WH_DOWN,
  KC_MS_WH_LEFT,
  KC_MS_WH_RIGHT,

  /* Acceleration */
  KC_MS_ACCEL0,
  KC_MS_ACCEL1,
  KC_MS_ACCEL2 // 0xFF
};

/* Consumer Page (0x0C)
 *
 * See https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf#page=75
 */
enum consumer_usages
{
  // 15.5 Display Controls
  SNAPSHOT = 0x065,
  BRIGHTNESS_UP = 0x06F, // https://www.usb.org/sites/default/files/hutrr41_0.pdf
  BRIGHTNESS_DOWN = 0x070,
  // 15.7 Transport Controls
  TRANSPORT_RECORD = 0x0B2,
  TRANSPORT_FAST_FORWARD = 0x0B3,
  TRANSPORT_REWIND = 0x0B4,
  TRANSPORT_NEXT_TRACK = 0x0B5,
  TRANSPORT_PREV_TRACK = 0x0B6,
  TRANSPORT_STOP = 0x0B7,
  TRANSPORT_EJECT = 0x0B8,
  TRANSPORT_RANDOM_PLAY = 0x0B9,
  TRANSPORT_STOP_EJECT = 0x0CC,
  TRANSPORT_PLAY_PAUSE = 0x0CD,
  // 15.9.1 Audio Controls - Volume
  AUDIO_MUTE = 0x0E2,
  AUDIO_VOL_UP = 0x0E9,
  AUDIO_VOL_DOWN = 0x0EA,
  // 15.15 Application Launch Buttons
  AL_CC_CONFIG = 0x183,
  AL_EMAIL = 0x18A,
  AL_CALCULATOR = 0x192,
  AL_LOCAL_BROWSER = 0x194,
  AL_LOCK = 0x19E,
  AL_CONTROL_PANEL = 0x19F,
  AL_ASSISTANT = 0x1CB,
  AL_KEYBOARD_LAYOUT = 0x1AE,
  // 15.16 Generic GUI Application Controls
  AC_NEW = 0x201,
  AC_OPEN = 0x202,
  AC_CLOSE = 0x203,
  AC_EXIT = 0x204,
  AC_MAXIMIZE = 0x205,
  AC_MINIMIZE = 0x206,
  AC_SAVE = 0x207,
  AC_PRINT = 0x208,
  AC_PROPERTIES = 0x209,
  AC_UNDO = 0x21A,
  AC_COPY = 0x21B,
  AC_CUT = 0x21C,
  AC_PASTE = 0x21D,
  AC_SELECT_ALL = 0x21E,
  AC_FIND = 0x21F,
  AC_SEARCH = 0x221,
  AC_HOME = 0x223,
  AC_BACK = 0x224,
  AC_FORWARD = 0x225,
  AC_STOP = 0x226,
  AC_REFRESH = 0x227,
  AC_BOOKMARKS = 0x22A
};

/* keycode to consumer usage */
static inline uint16_t KEYCODE2CONSUMER(uint8_t key)
{
  switch (key)
  {
    case KC_AUDIO_MUTE:
      return AUDIO_MUTE;
    case KC_AUDIO_VOL_UP:
      return AUDIO_VOL_UP;
    case KC_AUDIO_VOL_DOWN:
      return AUDIO_VOL_DOWN;
    case KC_MEDIA_NEXT_TRACK:
      return TRANSPORT_NEXT_TRACK;
    case KC_MEDIA_PREV_TRACK:
      return TRANSPORT_PREV_TRACK;
    case KC_MEDIA_FAST_FORWARD:
      return TRANSPORT_FAST_FORWARD;
    case KC_MEDIA_REWIND:
      return TRANSPORT_REWIND;
    case KC_MEDIA_STOP:
      return TRANSPORT_STOP;
    case KC_MEDIA_EJECT:
      return TRANSPORT_STOP_EJECT;
    case KC_MEDIA_PLAY_PAUSE:
      return TRANSPORT_PLAY_PAUSE;
    case KC_MEDIA_SELECT:
      return AL_CC_CONFIG;
    case KC_MAIL:
      return AL_EMAIL;
    case KC_CALCULATOR:
      return AL_CALCULATOR;
    case KC_MY_COMPUTER:
      return AL_LOCAL_BROWSER;
    case KC_WWW_SEARCH:
      return AC_SEARCH;
    case KC_WWW_HOME:
      return AC_HOME;
    case KC_WWW_BACK:
      return AC_BACK;
    case KC_WWW_FORWARD:
      return AC_FORWARD;
    case KC_WWW_STOP:
      return AC_STOP;
    case KC_WWW_REFRESH:
      return AC_REFRESH;
    case KC_BRIGHTNESS_UP:
      return BRIGHTNESS_UP;
    case KC_BRIGHTNESS_DOWN:
      return BRIGHTNESS_DOWN;
    case KC_WWW_FAVORITES:
      return AC_BOOKMARKS;
    default:
      return 0;
  }
}

static inline uint16_t KEYCODE2SYSTEM(uint8_t key) {
    switch (key) {
        case KC_SYSTEM_POWER:
            return SYSTEM_POWER_DOWN;
        case KC_SYSTEM_SLEEP:
            return SYSTEM_SLEEP;
        case KC_SYSTEM_WAKE:
            return SYSTEM_WAKE_UP;
        default:
            return 0;
    }
}
