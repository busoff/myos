#pragma once

#include "osdev/input/keyboard.h"

void keyboard_init();

typedef void (*kbd_handler_func) (key_event_t);
void keyboard_register(kbd_handler_func func);
