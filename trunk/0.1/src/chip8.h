/***************************************************************************************
 chip8.h 1.0
 (C) 05/05/2010 10:12:00 by MARCOS BRITO, marbri91@gmail.com
 Description: Emulador de la computadora CHIP 8
 **************************************************************************************/

#include <SDL/SDL.h>
//#define TODEBUG
 
FILE *ptrGame;
#define SIZEMEM 4096
typedef unsigned char byte;
byte data [SIZEMEM];
byte V[16];
byte SP[32];
int VI;
int PC;
int DT;
int ST;
int FLAG;
int instrc (byte frstnib, byte secnib,byte thrdnid,byte frthnid);
int printPC();
int printReg();
int putpix(int pix,int n,int m,SDL_Surface *screen);
int putscrn (SDL_Surface *screen);
int printscrn();
int ini_milisegundos;
int fin_milisegundos;
int frametime;
int CurrentTime();
void ResetTimeBase();
byte keypressed();
byte scrn[64][32];
SDL_Event event;
SDL_Surface *screen;
Uint8 *keys;