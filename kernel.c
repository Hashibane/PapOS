//#include "terminal.h"
//#include "terminal_backend.h"
void _start(void) {
 //byobu 
 //Terminal* terminal = getTerminalInstance();
 //T_clearScreen(terminal);
 //T_putText(terminal, "Hello World!\nHello World2!\tHello World3\rh");
 
 short* addr = (short*)0xB8000;
 unsigned char attribute = 0x0F;
 char* string = "Hello World!";
 for (int i = 0 ; i < 12 ; ++i)
 {
	 *addr = (attribute << 8) | string[i];
	 ++addr;
 }
 
 for (;;) {}

}
