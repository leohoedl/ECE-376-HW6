// Ohm_Meter.C
//
// This program reads the A/D on RA0
// Computes the voltage

// Global Variables
unsigned char PIXEL @ 0x000;
const unsigned char MSG0[21] = "HW6.C           "; 
 

// Subroutines
#include <pic18.h>
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
   
unsigned int A2D_Read(unsigned char c)
{
   unsigned int result;
   unsigned char i;
   c = c & 0x0F;
   ADCON0 = (c << 2) + 0x01; // set Channel Select
   for (i=0; i<20; i++); // wait 2.4us (approx)
   GODONE = 1; // start the A/D conversion
   while(GODONE); // wait until complete (approx 8us)
   return(ADRES);
   }   



// Main Routine

void main(void)
{
	unsigned int RED[8], GREEN[8], BLUE[8];
   int A2D;     // raw A/D readings
   int VOLT;    // Volts*100 (500 means 5.00V)

   unsigned int i, j, DIE;

   TRISA = 0;
   TRISB = 0x0F;
   TRISC = 0x0F;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD
	TRISD0=0;

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
   Wait_ms(1000);

   LCD_Inst(0x01);

// Initialize the A/D port
   TRISA = 0xFF;
   TRISE = 0x0F;
   ADCON2 = 0x85;
   ADCON1 = 0x07;
   ADCON0 = 0x01;
   i = 0;
//

   while(1) {

      A2D = A2D_Read(0);

      VOLT = 0.488 * A2D;

      //LCD_Move(0,0);  LCD_Out(A2D, 5, 0);
      LCD_Move(0,0);  LCD_Out(VOLT, 5, 2);
		if(VOLT==0){
			for(int i=0;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(A2D>0 && A2D<127){
			for(int i=0;i<1;i++){
				NeoPixel_Display(50,50,50);
			}
			for(int i=1;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}	
		if(A2D>127 && A2D<255){
			for(int i=0;i<2;i++){
				NeoPixel_Display(50,50,50);
			}
			for(int i=2;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(A2D>255 && A2D<383){
			for(int i=0;i<3;i++){
				NeoPixel_Display(50,50,50);
			}
			for(int i=3;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(A2D>383 && A2D<511){
			for(int i=0;i<4;i++){
				NeoPixel_Display(50,50,50);
			}
			for(int i=4;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(A2D>511 && A2D <639){
			for(int i=0;i<5;i++){
				NeoPixel_Display(50,50,50);
			}
			for(int i=5;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(A2D<639 && A2D>767){
			for(int i=0;i<6;i++){
				NeoPixel_Display(50,50,50);
			}
			for(int i=6;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(A2D<767 && A2D<950){
			for(int i=0;i<7;i++){
				NeoPixel_Display(50,50,50);
			}
			for(int i=7;i<8;i++){
				NeoPixel_Display(0,0,0);
			}
		}
		if(A2D<950 && A2D<=1023){
			for(int i=0;i<8;i++){
				NeoPixel_Display(50,50,50);
			}
		}
  
      Wait_ms(20);

      }      
   }

