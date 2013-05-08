/***************************************************************************************
 SDLm.c 1.0
 (C) 20/02/2010 21:17:00 by MARCOS BRITO, marbri91@gmail.com
 Description: Emulador de la computadora CHIP 8
 **************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"
#include <SDL/SDL.h>

int putpix(int pix,int n,int m,SDL_Surface *screen);
int drawscrn (struct chip8_state *s,SDL_Surface *screen);
char keypressed();
Uint8 *keys;
int ini_milisegundos;
int fin_milisegundos;
int frametime;
int CurrentTime();
void ResetTimeBase();
FILE *ptrGame;

int main (int argc, char *argv[])
{
	int i;
	SDL_Event event;
	SDL_Surface *screen;
	struct chip8_state s;
	
	init(&s);
	atexit(SDL_Quit);
	if ((ptrGame=fopen(argv[1],"rb"))==NULL)
	{
		printf("Can't open the file\n");
		printf("Usage %s <rom file> ",argv[0]);
		getchar();
	}
	else
	{
		if (SDL_Init(SDL_INIT_VIDEO)<0)
		{
			printf("No se pudo iniciar SDL: %s\n", SDL_GetError());
			exit(1);
		}
		screen=SDL_SetVideoMode(640,320, 8, SDL_HWSURFACE);
		if (screen == NULL) 
		{
			printf("No se puede inicializar el modo gráfico: %s\n",SDL_GetError());
			exit(1);
		}
		i=fread(&(s.data[512]),1,SIZEMEM,ptrGame)+0x200;
		printf("%d bytes loaded\n", i-0x200);
		fclose(ptrGame);
		#ifdef TODEBUG
		int j;
		for(j=0x200; j<i; j++)
		{
			printf("%02X ",s.data[j]);
		}
		printf("\n");
		#endif
		int x=0;
		while(x==0&&s.PC<i+1)
		{
			ResetTimeBase();
			#ifdef TODEBUG
			printPC(&s);
			printReg(&s);
			if(getchar()==27){x=1;}
			#else
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) {x=1;}
				if (event.type == SDL_KEYDOWN) 
				{
					if (event.key.keysym.sym == SDLK_ESCAPE) 
					{
						x=1;
					} 
				}
			}
			#endif
			exec(&s);
			if(s.draw) drawscrn(&s,screen);
			s.keypress=keypressed();
			s.draw=0;
			s.PC+=2;
			
			if(s.DT!=0){s.DT--;}
			if(s.ST!=0){s.ST--;}
			
			do {
				frametime=CurrentTime();
			} while (frametime<4);
		}
	}
	return 0;
}
int putpix(int pix,int n,int m,SDL_Surface *screen)
{
	SDL_Rect bwpix;
	if(pix==1)
	{
		bwpix.x=n;
		bwpix.y=m;
		bwpix.w=10;
		bwpix.h=10;
		SDL_FillRect(screen	, &bwpix, SDL_MapRGB(screen->format, 255, 255, 255));
	}
	if(pix==0)
	{
		bwpix.x=n;
		bwpix.y=m;
		bwpix.w=10;
		bwpix.h=10;
		SDL_FillRect(screen	, &bwpix, SDL_MapRGB(screen->format, 0, 0, 0));
	}
	return 0;
}
int drawscrn (struct chip8_state *s,SDL_Surface *screen)
{
	int k,l;
	for(k=0;k<32;k++)
	{
		for(l=0;l<64;l++)
		{
			putpix(s->scrn[l][k],l*10,k*10,screen);
		}
	}
	SDL_Flip(screen);
	return 0;
}
char keypressed()
{
	char x;
	x=' ';
	Uint8 *keys;
	keys=SDL_GetKeyState(NULL);
	if(keys[SDLK_z]==1){ x='z';}
	if(keys[SDLK_x]==1){ x='x';}
	if(keys[SDLK_c]==1){ x='c';}
	if(keys[SDLK_v]==1){ x='v';}
	if(keys[SDLK_a]==1){ x='a';}
	if(keys[SDLK_s]==1){ x='s';}
	if(keys[SDLK_d]==1){ x='d';}
	if(keys[SDLK_f]==1){ x='f';}
	if(keys[SDLK_q]==1){ x='q';}
	if(keys[SDLK_w]==1){ x='w';}
	if(keys[SDLK_e]==1){ x='e';}
	if(keys[SDLK_r]==1){ x='r';}
	if(keys[SDLK_1]==1){ x='1';}
	if(keys[SDLK_2]==1){ x='2';}
	if(keys[SDLK_3]==1){ x='3';}
	if(keys[SDLK_4]==1){ x='4';}
	return x;
}
void ResetTimeBase() {
	ini_milisegundos=SDL_GetTicks();
}
int CurrentTime() {
	fin_milisegundos=SDL_GetTicks();
	return fin_milisegundos-ini_milisegundos;
}