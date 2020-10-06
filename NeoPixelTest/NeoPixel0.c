// NeoPixel1.C
//
// This program drives a NeoPixel connected to RD0
// The color sent to the NeoPixel changes from red
// to green to blue and repeats
//

// Global Variables

unsigned char PIXEL @ 0x000;

const unsigned char MSG0[20] = "NeoPixel1.C         ";

// Subroutine Declarationsb
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"
  
void NeoPixel_Display(unsigned char RED, 
		unsigned char GREEN, unsigned char BLUE)
{
   PIXEL = GREEN;	asm("  call Pixel_8 ");
   PIXEL = RED;		asm("  call Pixel_8 ");
   PIXEL = BLUE;	asm("  call Pixel_8 ");

   asm("    return");


#asm
Pixel_8:
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    return

Pixel_1:
	bsf		((c:3971)),0	; PORTD,0
    nop
	btfss   ((c:0000)),7
	bcf		((c:3971)),0
	rlncf   ((c:0000)),F
    nop
    nop
    bcf		((c:3971)),0
    return

#endasm
   }

void Wait(unsigned int X)
{
   unsigned int i, j;

   for (i=0; i<X; i++)
      for (j=0; j<609; j++);
   }
   
         
// Main Routine

void main(void)
{
   unsigned int i, N;
   unsigned char RED[8], GREEN[8], BLUE[8];

   TRISA = 0;
   TRISB = 0xFF;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   TRISA = 0;
   PORTB = 0;
   PORTC = 0;
   PORTD = 0;
   PORTE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD
   TRISD0 = 0;

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]); 
   Wait_ms(100); 

   N = 0;

   while(1) {   
      
      	if(RB0==1){ 
			for(int i=0;i<1;i++){
				NeoPixel_Display(255,255,255);
			}
			for(int i=1;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
   		}
		if(RB1==1){
			for(int i=0;i<2;i++){
				NeoPixel_Display(255,255,255);
			}
			for(int i=2;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(RB2==1){
			for(int i=0;i<3;i++){
				NeoPixel_Display(255,255,255);
			}
			for(int i=3;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(RB3==1){
			for(int i=0;i<4;i++){
				NeoPixel_Display(255,255,255);
			}
			for(int i=4;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}	
		if(RB4==1){
			for(int i=0;i<5;i++){
				NeoPixel_Display(255,255,255);
			}
			for(int i=5;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(RB5==1){
			for(int i=0;i<6;i++){
				NeoPixel_Display(255,255,255);
			}
			for(int i=6;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(RB6==1){
			for(int i=0;i<7;i++){
				NeoPixel_Display(255,255,255);
			}
			for(int i=7;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(RB7==1){
			for(int i=0;i<8;i++){
				NeoPixel_Display(255,255,255);
			}
		}
      Wait(20);
   }



}