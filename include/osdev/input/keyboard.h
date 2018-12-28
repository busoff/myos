#pragma once

#include <stdint.h>

typedef uint8_t kbd_key_t;
typedef uint8_t kbd_mod_t;
typedef uint8_t kbd_act_t;

static const kbd_mod_t KEY_MOD_LCTRL = 0x1 << 0;
static const kbd_mod_t KEY_MOD_RCTRL = 0x1 << 1;
static const kbd_mod_t KEY_MOD_LALT = 0x1 << 2;
static const kbd_mod_t KEY_MOD_RALT = 0x1 << 3;
static const kbd_mod_t KEY_MOD_LSHIFT = 0x1 << 4;
static const kbd_mod_t KEY_MOD_RSHIFT = 0x1 << 5;
static const kbd_mod_t KEY_MOD_CAPSLOCK = 0x1 << 6;
static const kbd_mod_t KEY_MOD_NUMLOCK = 0x1 << 7;

static const kbd_act_t KEY_ACT_DOWN = 1;
static const kbd_act_t KEY_ACT_UP = 2;
typedef struct
{
    kbd_key_t keycode; /* key code */
    kbd_mod_t modifiers; /* modifiers */
    kbd_act_t action; /* 1 for UP and 2 for DOWN */
} key_event_t;
