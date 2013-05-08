/***************************************************************************************
 chip8.h 1.0
 (C) 05/05/2010 10:12:00 by MARCOS BRITO, marbri91@gmail.com
 Description: Emulador de la computadora CHIP 8
 **************************************************************************************/

//#define TODEBUG
#define SIZEMEM 4096
typedef unsigned char byte;
typedef unsigned int word;
struct chip8_state
{
	byte data [SIZEMEM];
	byte scrn[64][32];
	byte V[16];
	byte SP;
	word stack[32];
	word VI;
	word PC;
	word DT;
	word ST;
	word draw;
	char keypress;
};
int exec (struct chip8_state *s);
int printPC(struct chip8_state *s);
int printReg(struct chip8_state *s);
int printscrn(struct chip8_state *s);
char getkey(byte reg);
byte getcode(char c);
void init(struct chip8_state *s);