/***************************************************************************************
 opcode.c 1.0
 (C) 05/05/2010 10:08:00 by MARCOS BRITO, marbri91@gmail.com
 Description: instrucciones de CHIP 8
 **************************************************************************************/
#include <stdio.h>
#include "chip8.h"
#include <math.h>

int SP_displace()
{
	int i=0;
	for(i=0;i<32;i++)
	{
		SP[32-i]=SP[31-i];
	}
	return 0;
}
int instrc (byte frstnib, byte secnib,byte thrdnid,byte frthnid)
{
	byte lowbyte=thrdnid*0x10 +frthnid;
	if(frstnib==0x00){
		if(frthnid==0x0e){PC=SP[1]*0x100 +SP[0]%0x100;}//retorno de subrutina 00ee
		if(lowbyte==0xe0){int k,l;for(k=0;k<32;k++){for(l=0;l<64;l++){scrn[l][k]=0;}}putscrn(screen);}
	}
	if(frstnib==0x01){PC=secnib*0x100 +lowbyte-2;}//salto incondicional 1nnn
	if(frstnib==0x02){SP_displace();SP[0]=PC/0x100;SP_displace();SP[0]=PC%0x100;
					PC=secnib*0x100+lowbyte-2;}//llamada a subrutina 2nnn
	if(frstnib==0x03){if(V[secnib]==lowbyte){PC+=2;}}//salto si r es igual que constante 3rnn
	if(frstnib==0x04){if(V[secnib]!=lowbyte){PC+=2;}}//salto ni r no es igual que constante 4rnn
	if(frstnib==0x05){if(V[secnib]==V[thrdnid]){PC+=2;}}//salto si r e y son iguales 5ry0
	if(frstnib==0x06){V[secnib]=lowbyte;}//mover constante a Vr 6rnn
	if(frstnib==0x07){V[secnib]+=lowbyte;}//añadir constante al registro r 7rnn
	if(frstnib==0x08)
	{
		if(frthnid==0){V[secnib]=V[thrdnid];}//mover constante de Vr a Vy 8ry0
		if(frthnid==1){V[secnib]|=V[thrdnid];}
		if(frthnid==2){V[secnib]&=V[thrdnid];}
		if(frthnid==3){V[secnib]^=V[thrdnid];}
		if(frthnid==4){int num; num=V[secnib]+V[thrdnid]; V[15]=num/0x100; V[secnib]+=V[thrdnid];}
		if(frthnid==5){if(V[secnib]<=V[thrdnid]){V[15]=1;}V[secnib]=V[secnib]-V[thrdnid];}
		if(frthnid==6){V[15]=V[secnib]&0x01; V[secnib]>>=1;}
		if(frthnid==7){if(V[secnib]>=V[thrdnid]){V[15]=1;}V[thrdnid]=V[thrdnid]-V[secnib];}
		if(frthnid==0x0e){V[15]=V[secnib]&0x80; V[secnib]<<=1;}
	}
	if(frstnib==0x09){if(V[secnib]!=V[thrdnid]){PC+=2;}}
	if(frstnib==0x0a){VI=secnib*0x100+lowbyte;}//poner en VI una posicion Annn
	if(frstnib==0x0b){PC=secnib*0x100+lowbyte-2+V[0];}
	if(frstnib==0x0c){V[secnib]=(rand()%255)&lowbyte;}
	if(frstnib==0x0d)
	{
		int j,k;
		for(k=0;k<frthnid;k++)
		{
			for(j=0;j<8;j++)
			{
				V[15]=0;
				scrn[(V[secnib]+j)%64][(V[thrdnid]+k)%32]^=(data[VI+k]&(int)pow(2,7-j))>>7-j;
			}
		}
		putscrn(screen);
	}
	if(frstnib==0x0e){if(lowbyte==0xa1){if(keypressed()!=V[secnib]){PC+=2;}}
					if(lowbyte==0x9e){if(keypressed()==V[secnib]){PC+=2;}}
	}
	if(frstnib==0x0f){if(lowbyte==0x07){V[secnib]=DT;}
					 if(lowbyte==0x15){DT=V[secnib];}
					 if(lowbyte==0x55){data[VI]=V[secnib];}
					 if(lowbyte==0x65){V[secnib]=data[VI];}
					 if(lowbyte==0x1e){VI+=V[secnib];}
					 if(lowbyte==0x0a){if(keypressed()!=V[secnib]){PC-=2;}} 
	}
				
	return 0;
}
byte keypressed()
{
	byte x;
	x=0x10;
	
	Uint8 *keys;
	keys=SDL_GetKeyState(NULL);
	if(keys[SDLK_z]==1){ x=0x0a;}
	if(keys[SDLK_x]==1){ x=0x00;}
	if(keys[SDLK_c]==1){ x=0x0b;}
	if(keys[SDLK_v]==1){ x=0x0f;}
	if(keys[SDLK_a]==1){ x=0x07;}
	if(keys[SDLK_s]==1){ x=0x08;}
	if(keys[SDLK_d]==1){ x=0x09;}
	if(keys[SDLK_f]==1){ x=0x0e;}
	if(keys[SDLK_q]==1){ x=0x04;}
	if(keys[SDLK_w]==1){ x=0x05;}
	if(keys[SDLK_e]==1){ x=0x06;}
	if(keys[SDLK_r]==1){ x=0x0d;}
	if(keys[SDLK_1]==1){ x=0x01;}
	if(keys[SDLK_2]==1){ x=0x02;}
	if(keys[SDLK_3]==1){ x=0x03;}
	if(keys[SDLK_4]==1){ x=0x0c;}
	return x;
}