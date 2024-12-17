//#SPI Protocol

#include<lpc17xx.h>
#include"pll.c"
void spi_data(unsigned int d);
void delay(unsigned int i);
int main(){
pll_96mhz();//cpuclk
LPC_SC->PCONP|=(1<<10);//Enable power for SSP1
LPC_SC->PCLKSEL0|=(1<<20)|(1<<21);//Enable clk to SSP1
LPC_PINCON->PINSEL0|=(1<<15)|(1<<17)|(1<<19);//	 Config P0.7 to P0.9 as SPI pins
LPC_GPIO0->FIODIR|=(1<<6);//p0.6--SS line //config SS pin P0.6 as GPIO output
//SPI Configuration
LPC_SSP1->CR0=(0xF<<0)|(1<<6)|(1<<7);//SPI in 16 bit mode,CPOL=1,CPHASE=2
LPC_SSP1->CR1=(1<<1);  //Enable the SSP11 for Comm
LPC_SSP1->CPSR=24;  	//Prescalr Reg Value=24Mhz//pclk
//Slave Config MX7219(7 Segment)
//Command Transmission
             spi_data(0x090F); //Decode Mode
			 spi_data(0x0A0F); //Intensity Ctrl Reg
			 spi_data(0x0B03); //Scan Limit
			 spi_data(0x0C01); //shutdown Reg,Normal Operation
			 spi_data(0x0F01);//Display Test
			 delay(1000);
			 spi_data(0x0F00); 	 //Dummy Values //Normal; Operation
  //Actual Data Transmission
  while(1){
         spi_data(0x0101);
		 spi_data(0x0207);
		 spi_data(0x0308); 	
		 spi_data(0x0408); 	
		 delay(2000);
//		 spi_data(0x010C);
//		 spi_data(0x020B);
//		 spi_data(0x03D8); 
//Turn Off All Segments
           spi_data(0x02FF); 	
		   spi_data(0x03FF); 	
		   spi_data(0x040FF); 
		   delay(2000);	}}
 void spi_data(unsigned int d){
 LPC_SSP1->DR=d; //Load the Data Reg
 LPC_GPIO0->FIOCLR=(1<<6);     //Pull SS line to low(Gnd)
 while(!(LPC_SSP1->SR&(1<<0))); //check Tx Buffer Empty r not Uisng Polling Method 
 LPC_GPIO0->FIOSET=(1<<6);}
 
 void delay(unsigned int t)
{ 
  int j,k;
  for(j=0;j<t;j++)
  for(k=0;k<3000;k++);
} 
  
 