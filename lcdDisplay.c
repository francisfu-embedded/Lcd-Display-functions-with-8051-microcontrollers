#include <reg52.h>
#include <intrins.h>
#include <stdio.h>

sbit RS=P1^0;
sbit RW=P1^1;
sbit LCDEN=P2^5;
sbit DU=P2^0;
sbit WE=P2^1;

#define uchar unsigned char
#define GPIO_LCD P0;



void delayms(uchar xms){
	uchar i,j;
  for(i=0;i<xms;i++)
	  for(j=0;j<112;j++);

}

bit LcdCheckBusy(){
  P0=0xff;
	RS=0;
	RW=1;
	LCDEN=0;
	_nop_();
	LCDEN=1;
	return (bit)(P0&0x80);
}
void LcdWriteCom(uchar com){
	while(LcdCheckBusy());
  RS=0;
	RW=0;
	P0=com;
	delayms(10);
  LCDEN=1;
	delayms(10);
	LCDEN=0;
}

void LcdWriteData(uchar dat){
		while(LcdCheckBusy());
  RS=1;
	RW=0;
	P0=dat;
	delayms(10);
  LCDEN=1;
	delayms(10);
	LCDEN=0;
}
void LcdInit(){
 LcdWriteCom(0x38);
	delayms(5);
	LcdWriteCom(0x38);
	delayms(5);
	LcdWriteCom(0x38);
	delayms(5);
	LcdWriteCom(0x38);//init
	LcdWriteCom(0x08);//shut down display
	LcdWriteCom(0x01);//clear the screen
	LcdWriteCom(0x06);//move to the next position on the right after a character input 
	delayms(5);
	LcdWriteCom(0x0c);
}



void clear(){
  LcdWriteCom(0x01);
	delayms(6);
}

void LcdWriteString(uchar x, uchar y,uchar *s){
   if(y==0){
	   LcdWriteCom(0x80+x);
	 } 
	 if(y==1){
	   LcdWriteCom(0xc0+x);
	 }
	 while(*s){
	   LcdWriteData(*s);
		 s++;
	 }
 
}

void LcdWriteChar(uchar x, uchar y,uchar c){
	if(c!='\0'){
   if(y==0){
	   LcdWriteCom(0x80+x);
	 } 
	 if(y==1){
	   LcdWriteCom(0xc0+x);
	 }
  LcdWriteData(c);
 }
}
/*this is a test case */
void main(){
	//just to turn off the digital tube on the dev board to avoid confilicts
  DU=1;
	P0=0x00;
	DU=0;
  LcdInit();
	clear();
	while(1){
	  LcdWriteChar(9,0,'a');
		 LcdWriteChar(10,0,'b');
		LcdWriteString(1,1,"die temperatur");
		while(1);
	}
}

