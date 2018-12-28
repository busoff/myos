#pragma once

#include <stdint.h>

static const uint16_t KEY_MOD_LCTRL = 0x1 << 0;
static const uint16_t KEY_MOD_RCTRL = 0x1 << 1;
static const uint16_t KEY_MOD_LALT = 0x1 << 2;
static const uint16_t KEY_MOD_RALT = 0x1 << 3;
static const uint16_t KEY_MOD_LSHIFT = 0x1 << 4;
static const uint16_t KEY_MOD_RSHIFT = 0x1 << 5;
static const uint16_t KEY_MOD_CAPSLOCK = 0x1 << 6;
static const uint16_t KEY_MOD_NUMLOCK = 0x1 << 7;

static const uint8_t KEY_ACT_DOWN = 1;
static const uint8_t KEY_ACT_UP = 2;
typedef struct
{
    uint16_t keycode; /* key code */
    uint16_t modifiers; /* modifiers */
    uint8_t action; /* 1 for UP and 2 for DOWN */
} key_event_t;
