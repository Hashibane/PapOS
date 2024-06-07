#include "terminal.h"

void T_moveCursor(Terminal* terminal, uint16_t x, uint16_t y)
{
	terminal->TF_moveCursor(terminal, x, y);
}
void T_getCursorPosition(Terminal* terminal, uint16_t* x, uint16_t* y)
{
	terminal->TF_getCursorPosition(terminal, x, y);
}
void T_putText(Terminal* terminal, const char* s)
{
        for (; *s != '\0' ; ++s)
        {
                switch (*s)
                {
                        case '\n':
                        {
				uint16_t x, y;
				T_getCursorPosition(terminal, &x, &y);
                                T_moveCursor(terminal, 0, y+1);
                                break;
                        }
                        case '\r':
                        {
				uint16_t x, y;
				T_getCursorPosition(terminal, &x, &y);
                                T_moveCursor(terminal, 0, y);
                                break;
                        }
                        case '\t':
                        {
				uint16_t x, y;
				uint16_t bx, by; //begin x, begin y
				T_getCursorPosition(terminal, &bx, &by);
				x = bx;
				y = by;

				uint16_t width, height;
				T_getSize(terminal, &width, &height);

                                x += 8 - x % 8;

                                if (x >= width)
                                {
                                        x = 0;
                                        y += 1;
                                        T_moveCursor(terminal, x, y);
                                }
                                else
                                {
                                        for (uint16_t i = bx ; i < x ; ++i)
                                        {
                                                T_putCharacter(terminal, ' ');
                                        }
                                }

                                break;
                        }
                        default:
				T_putCharacter(terminal, (unsigned char)*s);

                }
        }	
}

void T_clearScreen(Terminal* terminal)
{
	terminal->TF_clearScreen(terminal);
}

void T_putCharacter(Terminal* terminal, uint32_t ch)
{
	terminal->TF_putCharacter(terminal, ch);
}

void T_getSize(Terminal* terminal, uint16_t *w, uint16_t *h)
{
	terminal->TF_getSize(terminal, w, h);
}
