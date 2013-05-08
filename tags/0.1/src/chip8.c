/***************************************************************************************
 chip8.c 1.0
 (C) 20/02/2010 21:17:00 by MARCOS BRITO, marbri91@gmail.com
 Description: Emulador de la computadora CHIP 8
 **************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "chip8.h"

int i;
int main (int argc, char *argv[])
{

	PC=0x200;
	VI=0x200;
	atexit(SDL_Quit);
	if ((ptrGame=fopen(argv[1],"rb"))==NULL)
	{
		printf("No se puede abrir el archivo\n");
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
		i=fread(&data[512],1,SIZEMEM,ptrGame)+0x200;
		printf("%d bytes loaded\n", i-0x200);
		fclose(ptrGame);
		#ifdef TODEBUG
		int j;
		for(j=200h; j<i; j++)
		{
			printf("%x ",data[j]);
		}
		printf("\n");
		#endif
		int x=0;
		while(x==0&&PC<i+1)
		{
			ResetTimeBase();
			#ifdef TODEBUG
			printPC();
			printReg();
			//printf("\n%d-%d\n",i,PC);
			//printscrn();
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

			instrc(data[PC]/0x10, data[PC]%0x10, data[PC+1]/0x10, data[PC+1]%0x10);

			PC+=2;
			
			if(DT!=0){DT--;}
			if(ST!=0){ST--;}
			
			do {
				frametime=CurrentTime();
			} while (frametime<4);
		}
	}
	return 0;
}
int printPC()
{
	printf("\n");
	printf("%d=%02x%02x; ",PC-512,data[PC],data[PC+1]);
	return 0;
}
int printReg()
{
	int j=0;
	for(j=0;j<8;j++){printf("V[%02x]: %02x  ",j,V[j]);}
	printf("\n        ");
	for(j=8;j<16;j++){printf("V[%02x]: %02x  ",j,V[j]);}
	printf("\n        I: %d\n", VI-0x200);
	return 0;
}
int printscrn()
{
	int k,l;
	for(k=0;k<32;k++)
	{
		for(l=0;l<64;l++)
		{
			printf("%d",scrn[l][k]);
		}
		printf("\n");
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
int putscrn (SDL_Surface *screen)
{
	int k,l;
	for(k=0;k<32;k++)
	{
		for(l=0;l<64;l++)
		{
			putpix(scrn[l][k],l*10,k*10,screen);
		}
	}
	SDL_Flip(screen);
	return 0;
}
void ResetTimeBase() {
	ini_milisegundos=SDL_GetTicks();
}
int CurrentTime() {
	fin_milisegundos=SDL_GetTicks();
	return fin_milisegundos-ini_milisegundos;
}