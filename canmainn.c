		   #include<lpc17xx.h>
			   #include "LCD.h"
				//#include "led1.c"
				#include"lcdpro.h"
				#include "lcdfunc.c"
				#include "canmain.c"
				#include "pll.c"
		        int main(){
		   				  unsigned int val,i;
						  unsigned int id[20]={123,432,456,678,698,456,343,546,553};
						  unsigned int data1[20]={35667249,88909795,98895874,54930874,58758907};
						   unsigned int data2[20]={35677249,88329795,98896874,549326287,58752907};
						   pll_96mhz();
						   lcd_config();
						   can_config();
						  /* while(1){
						   for(i='A';i<='Z';i++)
						{
						can_tx(i);
							 val=can_rx();
							 lcd_data(val);
							  delay(1000);
							}	*/
							while(1){
							for(i=0;i<5;i++){
							can_tx_8bytes(data1[i],data2[i],id[i]);
						//	can_tx('D');
							val=can_rx_8bytes();
							 lcd_cmd(0x01);
							 lcd_cmd(0x80);
							lcd_str("MSG ID");
								 lcd_num(MSG[0]);
							delay(1000)	;
						 lcd_cmd(0x01);
							 lcd_cmd(0x80);
							lcd_str("MSG 1");
								 lcd_num(MSG[1]);
								 lcd_cmd(0xc0);
								 lcd_str("MSG2:");
							lcd_num(MSG[2]);
							   	delay(2000);
						   }
						   
		   }
		   }
/*void delay(unsigned int t)
{ 
  int j,k;
  for(j=0;j<t;j++)
  for(k=0;k<3000;k++);
} */ 