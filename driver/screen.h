#pragma once

#include <stdint.h>

void scr_char_at(char ch, uint8_t x, uint8_t y);

void scr_str_at(const char* str, uint8_t x, uint8_t y);

void scr_size(uint8_t* width, uint8_t* height);

void scr_print(const char* str);
