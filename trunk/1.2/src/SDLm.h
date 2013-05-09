/***************************************************************************************
  SDLm.h 1.0
  (C) 09/05/2013 11:12:21 by MARCOS BRITO, marbri91@gmail.com
Description: Encabezado de SDLm.c
 **************************************************************************************/
#ifndef SDLM_H
#define SDLM_H

int InitSDL(SDL_Surface **screen);
int OpenGame(struct chip8_state *s, char *argv);
int MainSDL(struct chip8_state *s, SDL_Surface **screen);
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

#endif
