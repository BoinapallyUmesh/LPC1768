#include<lpc17xx.h>
#include<string.h>
#include "pll.c"
#include "LCD.h"
#include "lcdname.c"
void tx(unsigned char a);
void tx_str(unsigned char str[20]);
void rx();
void delay(unsigned int t);

int main(){

pll_96mhz();//pll@96 Mhz
lcd_config();

 //UART Configuration

 LPC_SC->PCONP|=(1<<3); //	Enable power UART 0
 LPC_PINCON->PINSEL0|=(1<<4)|(1<<6);//Config P0.2,P0.3 as Tx and Rx
 LPC_UART0->LCR=(1<<0)|(1<<1)|(1<<7);//8 Bit mode,No parity,enable DLAB Bit
 LPC_UART0->DLL=146;//load the baud rate for 9600
 LPC_UART0->DLM=0;
 LPC_UART0->FDR=(15<<4)|(1<<0);	//fractional divider reg  mul=15,div=1
 LPC_UART0->LCR&=~(1<<7);//	Disable bit DLAB BIT
 //LPC_UART0->FCR=(1<<0)|(1<<1)|(1<<2);
while(1){
// rx();
 tx('v');
 delay(100); }}


	 
void tx(unsigned char a){
while(!(LPC_UART0->LSR&(1<<5))); //Check THR empty r not using polling method
LPC_UART0->THR=a; //load the data to be transmitted to THR reg
delay(100);
}

void tx_str(unsigned char str[20]){
int i;
for(i=0;str[i]!='\0';i++){
tx(str[i]);
delay(100);	 
}
}
void rx(){
unsigned char val;
while(!(LPC_UART0->LSR&(1<<0))); //Check THR empty r not using polling method
val=LPC_UART0->RBR; //Load the data to be txed to THR reg
lcd_data(val);
delay(100);} 

void delay(unsigned int t)
{ 
  int j,k;
  for(j=0;j<t;j++)
  for(k=0;k<3000;k++);
}



