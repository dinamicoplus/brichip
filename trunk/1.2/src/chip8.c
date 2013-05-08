/***************************************************************************************
 chip8.c 2.0
 (C) 05/05/2010 10:08:00 by MARCOS BRITO, marbri91@gmail.com
 Description: Emulador del sistema CHIP 8
 **************************************************************************************/
#include <stdio.h>
#include <time.h>
#include "chip8.h"

int exec (struct chip8_state *s)
{
	word w=(s->data[s->PC])<<8|(s->data[s->PC+1])&0xFF;
	byte lowbyte=s->data[s->PC+1];
	byte frstnib=(w&0xF000)>>0x0C;
	byte secnib=(w&0x0F00)>>0x08;
	byte thrdnid=(w&0x00F0)>>0x04;
	byte frthnid=(w&0x000F);
	if(w==0x00ee){s->PC=s->stack[--(s->SP)];}//retorno de subrutina 00ee
	if(w==0x00e0){int k,l;for(k=0;k<32;k++){for(l=0;l<64;l++){s->scrn[l][k]=0;}}s->draw=1;}
	if(frstnib==0x01){s->PC=w-0x1002;}//salto incondicional 1nnn
	if(frstnib==0x02){s->stack[(s->SP)++]=s->PC; s->PC=w-0x2002;}//llamada a subrutina 2nnn
	if(frstnib==0x03){if(s->V[secnib]==lowbyte){s->PC+=2;}}//salto si r es igual que constante 3rnn
	if(frstnib==0x04){if(s->V[secnib]!=lowbyte){s->PC+=2;}}//salto ni r no es igual que constante 4rnn
	if(frstnib==0x05){if(s->V[secnib]==s->V[thrdnid]){s->PC+=2;}}//salto si r e y son iguales 5ry0
	if(frstnib==0x06){s->V[secnib]=lowbyte;}//mover constante a Vr 6rnn
	if(frstnib==0x07){s->V[secnib]+=lowbyte;}//añadir constante al registro r 7rnn
	if(frstnib==0x08)
	{
		if(frthnid==0){s->V[secnib]=s->V[thrdnid];}//mover constante de Vr a Vy 8ry0
		if(frthnid==1){s->V[secnib]|=s->V[thrdnid];}
		if(frthnid==2){s->V[secnib]&=s->V[thrdnid];}
		if(frthnid==3){s->V[secnib]^=s->V[thrdnid];}
		if(frthnid==4){s->V[15]=(s->V[secnib]+s->V[thrdnid])>>8; s->V[secnib]+=s->V[thrdnid];}
		if(frthnid==5){if(s->V[secnib]>=s->V[thrdnid]){s->V[15]=1;} else s->V[15]=0; s->V[secnib]=s->V[secnib]-s->V[thrdnid];}
		if(frthnid==6){s->V[15]=s->V[secnib]&0x01; s->V[secnib]>>=1;}
		if(frthnid==7){if(s->V[secnib]<=s->V[thrdnid]){s->V[15]=1;} else s->V[15]=0; s->V[thrdnid]=s->V[thrdnid]-s->V[secnib];}
		if(frthnid==0x0e){s->V[15]=(s->V[secnib]&0x80)>>7; s->V[secnib]<<=1;}
	}
	if(frstnib==0x09){if(s->V[secnib]!=s->V[thrdnid]){s->PC+=2;}}
	if(frstnib==0x0a){s->VI=w-0xA000;}//poner en VI una posicion Annn
	if(frstnib==0x0b){s->PC=w-0xB002+s->V[0];}
	if(frstnib==0x0c){s->V[secnib]=(int)((rand()%255)&(lowbyte));}
	if(frstnib==0x0d)
	{
		int j,k;
		int aux=0;
		s->V[15]=0;
		#ifdef TODEBUG
		for(k=0;k<frthnid;k++)
		{
			for(j=0;j<8;j++)
			{				
				printf("%d",s->scrn[(s->V[secnib]+j)%64][(s->V[thrdnid]+k)%32]);
			}
			printf("\n");
		}
		printf("\n");
		for(k=0;k<frthnid;k++)
		{
			for(j=0;j<8;j++)
			{				
				printf("%d",(s->data[s->VI+k]&(1<<(7-j)))>>7-j);
			}
			printf("\n");
		}
		printf("\n");
		for(k=0;k<frthnid;k++)
		{
			for(j=0;j<8;j++)
			{				
				printf("%d",s->scrn[(s->V[secnib]+j)%64]\
					   [(s->V[thrdnid]+k)%32]&((s->data[s->VI+k]&(1<<(7-j)))>>7-j));
			}
			printf("\n");
		}
		printf("\n");
		#endif
		for(k=0;k<frthnid;k++)
		{
			for(j=0;j<8;j++)
			{
				aux+=s->scrn[(s->V[secnib]+j)%64][(s->V[thrdnid]+k)%32]&((s->data[s->VI+k]&(1<<(7-j)))>>7-j);
				s->scrn[(s->V[secnib]+j)%64][(s->V[thrdnid]+k)%32]^=(s->data[s->VI+k]&(1<<(7-j)))>>7-j;
			}
		}
		s->draw=1;
		if(aux>0){s->V[15]=1;}
	}
	if(frstnib==0x0e)
	{
		if(lowbyte==0xa1)
		{
			#ifndef TODEBUG 
			if(s->keypress!=getkey(s->V[secnib])){s->PC+=2;}
			#else
			printf("Introduce tecla: ");
			if(getchar()!=getkey(s->V[secnib])){s->PC+=2;}
			#endif
		}
		if(lowbyte==0x9e)
		{
			#ifndef TODEBUG
			if(s->keypress==getkey(s->V[secnib])){s->PC+=2;}
			#else
			printf("Introduce tecla: ");
			if(getchar()==getkey(s->V[secnib])){s->PC+=2;}
			#endif
		}
	}
	if(frstnib==0x0f)
	{
		if(lowbyte==0x07){s->V[secnib]=s->DT;}
		if(lowbyte==0x0a)
		{
			#ifndef TODEBUG
			if(s->keypress==' '){s->PC-=2;} else{s->V[secnib]=getcode(s->keypress);}
			#else
			char a=getchar();
			if(s->keypress==a){s->PC-=2;} else{s->V[secnib]=getcode(a);}
			#endif
		} 
		if(lowbyte==0x15){s->DT=s->V[secnib];}
		if(lowbyte==0x18){s->ST=s->V[secnib];}
		if(lowbyte==0x1e){if((s->VI+=s->V[secnib])>0xfff) s->V[15]=1; else s->V[15]=0;}
		if(lowbyte==0x29){s->VI=s->V[secnib]*5;}
		if(lowbyte==0x33)
		{
			s->data[s->VI+2]=s->V[secnib]%10;
			s->data[s->VI+1]=(s->V[secnib]/10)%10;
			s->data[s->VI]=(s->V[secnib]/100);
		}
		if(lowbyte==0x55)
		{
			int i;
			for(i=0; i<=secnib; i++)
			{
				s->data[s->VI++]=s->V[i];
			}
		}
		if(lowbyte==0x65)
		{
			int i;
			for(i=0; i<=secnib; i++)
			{
				s->V[i]=s->data[s->VI++];
			}
		}
	}
	return 0;
}
char getkey(byte reg)
{
	switch(reg)
	{
		   case 0x0a : return 'z';
		   case 0x00 : return 'x';
		   case 0x0b : return 'c';
		   case 0x0f : return 'v';
		   case 0x07 : return 'a';
		   case 0x08 : return 's';
		   case 0x09 : return 'd';
		   case 0x0e : return 'z';
		   case 0x04 : return 'q';
		   case 0x05 : return 'w';
		   case 0x06 : return 'e';
		   case 0x0d : return 'r';
		   case 0x01 : return '1';
		   case 0x02 : return '2';
		   case 0x03 : return '3';
		   case 0x0c : return '4';
		   default : return ' ';
	}
}
byte getcode(char c)
{
	switch(c)
	{
		case 'z' : return 0x0a;
		case 'x' : return 0x00;
		case 'c' : return 0x0b;
		case 'v' : return 0x0f;
		case 'a' : return 0x07;
		case 's' : return 0x08;
		case 'd' : return 0x09;
		case 'f' : return 0x0e;
		case 'q' : return 0x04;
		case 'w' : return 0x05;
		case 'e' : return 0x06;
		case 'r' : return 0x0d;
		case '1' : return 0x01;
		case '2' : return 0x02;
		case '3' : return 0x03;
		case '4' : return 0x0c;
		default : return 0x10;
	}
}
int printPC(struct chip8_state *s)
{
	printf("\n");
	printf("%04X=%02X%02X; ",s->PC,s->data[s->PC],s->data[s->PC+1]);
	return 0;
}
int printReg(struct chip8_state *s)
{
	int j=0;
	for(j=0;j<8;j++){printf("V[%02x]: %02x  ",j,s->V[j]);}
	printf("\n           ");
	for(j=8;j<16;j++){printf("V[%02x]: %02x  ",j,s->V[j]);}
	printf("\n           I: %04X -> %02x\n", s->VI, s->data[s->VI]);
	return 0;
}
int printscrn(struct chip8_state *s)
{
	int k,l;
	for(k=0;k<32;k++)
	{
		for(l=0;l<64;l++)
		{
			printf("%d",s->scrn[l][k]);
		}
		printf("\n");
	}
	return 0;
}
void init(struct chip8_state *s)
{
	int i,j;
	s->PC=0x200;
	s->VI=0x200;
	s->draw=0;
	s->SP=0;
	s->keypress=' ';
	unsigned char num[80]={0x60,0x90,0x90,0x90,0x60,
		0x20,0x60,0x20,0x20,0x70,
		0x60,0x90,0x20,0x40,0xf0,
		0x60,0x90,0x20,0x90,0x60,
		0x20,0x60,0xa0,0xf0,0x20,
		0xf0,0x80,0xe0,0x10,0xe0,
		0x60,0x80,0xe0,0x90,0x60,
		0xf0,0x90,0x20,0x40,0x40,
		0x60,0x90,0x60,0x90,0x60,
		0x60,0x90,0x70,0x10,0x60,
	    0x60,0x90,0xF0,0x90,0x90,
	    0xE0,0x90,0xE0,0x90,0xE0,
		0x60,0x80,0x80,0x80,0x60,
		0xE0,0x90,0x90,0x90,0xE0,
		0xF0,0x80,0xC0,0x80,0xF0,
		0xF0,0x80,0xC0,0x80,0x80};
	srand(time(NULL));
	for(i=0;i<80;i++)
	{
		s->data[i]=num[i];
	}
	for(i=0; i<32; i++)
	{
		for(j=0; j<64; j++)
		{
			s->scrn[j][i]=0;
		}
		s->stack[i]=0;
	}
	for(i=0;i<16;i++)
	{
		s->V[i]=0;
	}
}