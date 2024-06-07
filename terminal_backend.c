#include "terminal_backend.h"
#include "hal.h"

//VGA ENUMS
enum {
        VGAControlRegisterIndex_CursorLocationHigh = 0xE,
        VGAControlRegisterIndex_CursorLocationLow = 0xF
};

enum {                                                                  
	VGAControlRegisterIndexPort = 0x3D4,
	VGAControlDataRegisterIndexPort = 0x3D5
};


static struct CursorObject 
{
	uint16_t x;
	uint16_t y;
} Cursor;


static void primitiveMoveCursor(Terminal* terminal, uint16_t x, uint16_t y)
{
	unsigned int offset = 80*y + x;

	HAL_PortOutByte(VGAControlRegisterIndexPort, VGAControlRegisterIndex_CursorLocationLow);
	HAL_PortOutByte(VGAControlDataRegisterIndexPort, offset & 0xff);

	HAL_PortOutByte(VGAControlRegisterIndexPort, VGAControlRegisterIndex_CursorLocationHigh);
	HAL_PortOutByte(VGAControlDataRegisterIndexPort, offset >> 8);

	Cursor.x = x;
	Cursor.y = y;
}


static void primitiveClearScreen(Terminal* terminal)
{
	unsigned char* addr = (unsigned char*)0xB8000;
	short length = 80*25*2;
	for (int i = 0 ; i < length ; i+=2) 
	{
		addr[i] = ' ';
		addr[i+1] = 0x0A;
	}
 	primitiveMoveCursor(terminal, 0, 0);	
}
static void primitivePutCharacter(Terminal* terminal, uint32_t ch)
{
	unsigned char* addr = (unsigned char*)0xB8000;

	uint16_t offset = (Cursor.y * 80 + Cursor.x) << 1;
	addr[offset] = (unsigned char)ch;
	addr[offset + 1] = 0x0A;

	if (Cursor.x + 1 == 80)
	{
		primitiveMoveCursor(terminal, 0, Cursor.y + 1);
		return;
	}
	primitiveMoveCursor(terminal, Cursor.x + 1, Cursor.y);
}


static void primitiveGetCursorPosition(Terminal* terminal, uint16_t* x, uint16_t* y)
{
	*x = Cursor.x;
	*y = Cursor.y;
}
static void primitiveGetSize(Terminal* terminal, uint16_t* w, uint16_t* h)
{
	*w = 80;
	*h = 25;
}
static Terminal functionTable = { 
	.TF_moveCursor = primitiveMoveCursor,
        .TF_getCursorPosition = primitiveGetCursorPosition, 
        .TF_clearScreen = primitiveClearScreen,
        .TF_putCharacter = primitivePutCharacter,
        .TF_getSize = primitiveGetSize
};

Terminal* getTerminalInstance(void) 
{
	return &functionTable;
}
