/***************************************************************************************
 SDLm.c 1.0
 (C) 20/02/2010 21:17:00 by MARCOS BRITO, marbri91@gmail.com
 Description: Emulador de la computadora CHIP 8
 **************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <chip8.h>
#include <SDLm.h>
#include <config.h>


int main (int argc, char **argv) //<-- Esta funcion luego la cambian de nombre por SDL_main
{
	SDL_Surface *screen;
	struct chip8_state s;
	init(&s);										// Inicializa el estado del emulador
	InitSDL(&screen);								// Inicia la pantalla
	SDL_WM_SetCaption(PACKAGE_STRING, "");
	if(OpenGame(&s,argv)) MainSDL(&s,&screen);	// Si lo lee ejecuta el juego
	return 0;
}

int OpenGame(struct chip8_state *s, char **argv)
{
	if ((ptrGame=fopen(argv[1],"rb"))==NULL)
	{
		printf("Can't open the file\nUsage: %s <rom file>\n",argv[0]);
		return 0;
	}
	else
	{
		s->sizerom=fread(&(s->data[0x200]),1,SIZEMEM,ptrGame);
		printf("%d bytes loaded\n", s->sizerom);
		fclose(ptrGame);
#ifdef TODEBUG
		int j;
		for(j=0; j<s->sizerom; j++)
		{
			printf("%02X ",s->data[j+0x200]);
		}
		printf("\n");
#endif
		return 1;
	}
}

int InitSDL(SDL_Surface **screen)
{
	if (SDL_Init(SDL_INIT_VIDEO)<0)
	{
		printf("No se pudo iniciar SDL: %s\n", SDL_GetError());
		exit(0);
	}
	*screen=SDL_SetVideoMode(640,320, 8, SDL_HWSURFACE);
	if (*screen == NULL) 
	{
		printf("No se puede inicializar el modo gráfico: %s\n",SDL_GetError());
		exit(0);
	}
	return 0;
}	

int MainSDL(struct chip8_state *s, SDL_Surface **screen)
{
	SDL_Event event;
	int x=0;
	while(x==0&&s->PC<s->sizerom+0x201)
	{
		ResetTimeBase();
#ifdef TODEBUG
		printPC(s);
		printReg(s);
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
		exec(s);
		if(s->draw) drawscrn(s,*screen);
		s->keypress=keypressed();
		s->draw=0;
		s->PC+=2;
		
		if(s->DT!=0){s->DT--;}
		if(s->ST!=0){s->ST--;}
		
		do {
			frametime=CurrentTime();
		} while (frametime<4);
	}
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