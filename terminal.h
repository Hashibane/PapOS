#pragma once
#include <stdint.h>

struct Terminal;
typedef struct Terminal Terminal;
//TBptr = Terminal backend function pointer
typedef void (*TBptr_moveCursor)(Terminal* t, uint16_t x, uint16_t y);
typedef void (*TBptr_getCursorPosition)(Terminal* t, uint16_t* x, uint16_t* y);
typedef void (*TBptr_clearScreen)(Terminal* t);
typedef void (*TBptr_putCharacter)(Terminal* t, uint32_t ch);
typedef void (*TBptr_getSize)(Terminal* t, uint16_t *w, uint16_t *h);

struct Terminal
{
	TBptr_moveCursor TF_moveCursor;
	TBptr_getCursorPosition TF_getCursorPosition;
	TBptr_clearScreen TF_clearScreen;
	TBptr_putCharacter TF_putCharacter;
	TBptr_getSize TF_getSize;
	void* backend_data;
};

void T_moveCursor(Terminal* terminal, uint16_t x, uint16_t y);
void T_getCursorPosition(Terminal* terminal, uint16_t* x, uint16_t* y);
void T_putText(Terminal* terminal, const char* s);
void T_clearScreen(Terminal* terminal);
void T_putCharacter(Terminal* terminal, uint32_t ch);
void T_getSize(Terminal* terminal, uint16_t* w, uint16_t* h);
