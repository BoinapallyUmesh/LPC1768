		/*unsigned int MSG[30];
		void can_config(void){
		LPC_SC->PCONP|=(1<<13)|(1<<14);
		 	LPC_SC->PCLKSEL0&= ~((1<<26)|(1<<27)|(1<<28)|(1<<29));
				LPC_PINCON->PINSEL0|=(1<<0)|(1<<2);
				LPC_PINCON->PINSEL4|=(1<<14)|(1<<16);
				LPC_CAN1->MOD=(1<<0);
				 LPC_CAN1->BTR=(23<<0)|(15<<16)|(3<<20);
					  LPC_CAN1->MOD=0;
					  LPC_CAN2->MOD=(1<<0);
					 LPC_CAN2->BTR=(23<<0)|(15<<16)|(3<<20);
					 LPC_CAN2->MOD=0;
		}

		void can_tx(unsigned int d){
		while(!(LPC_CAN2->GSR&(1<<2)));
		   LPC_CAN2->TID1=147;
		   LPC_CAN2->TFI1=(1<<18);
			LPC_CAN2->TDA1=d;
			LPC_CAN2->CMR=(1<<0)|(1<<5);
			while(!(LPC_CAN2->GSR&(1<<3)));
		}

		unsigned int can_rx(){
			   while((LPC_CAN1->GSR&(1<<0)));
			   MSG[0]= LPC_CAN1->RID;
			   	   MSG[1]= LPC_CAN1->RDA;
				 LPC_CAN1->CMR=(1<<2);
				 return MSG[1];
				 return MSG[0];
				  }

				 void can_tx_id(unsigned int d,unsigned int id){
				  	while(!(LPC_CAN2->GSR&(1<<2)));
		   LPC_CAN2->TID1=id;
		   LPC_CAN2->TFI1=(1<<18);
			LPC_CAN2->TDA1=d;
			LPC_CAN2->CMR=(1<<0)|(1<<5);
			while(!(LPC_CAN2->GSR&(1<<3)));
		}
		
		void can_str(unsigned char *ptr){
		while(*ptr!='\0')
		{
		can_tx(*ptr);
		lcd_data(can_rx());
		ptr++;
		}}	  */
		   //8  Bytes Using Can
	unsigned int MSG[30];
		void can_config(void){
		LPC_SC->PCONP|=(1<<13)|(1<<14);
		 	LPC_SC->PCLKSEL0&= ~((1<<26)|(1<<27)|(1<<28)|(1<<29));
				LPC_PINCON->PINSEL0|=(1<<0)|(1<<2);
				LPC_PINCON->PINSEL4|=(1<<14)|(1<<16);
				LPC_CAN1->MOD=(1<<0);
				 LPC_CAN1->BTR=(23<<0)|(15<<16)|(3<<20);
					  LPC_CAN1->MOD=0;
					  LPC_CAN2->MOD=(1<<0);
					 LPC_CAN2->BTR=(23<<0)|(15<<16)|(3<<20);
					 LPC_CAN2->MOD=0;
		}
		void can_tx_8bytes(unsigned int d1,unsigned int d2,unsigned int id)
		{
		  	while(!(LPC_CAN2->GSR&(1<<2)));
		   LPC_CAN2->TID1=id;	  //Load Id
		   LPC_CAN2->TFI1=(1<<19);	 //Load Frame info,DLC=1000,RTR=0,IDE=0
			LPC_CAN2->TDA1=d1;				//Load the Data LSB 
			 LPC_CAN2->TDB1=d2;				//Load the Data MSB 
			LPC_CAN2->CMR=(1<<0)|(1<<5);	   //Select TB1,Enable Queued Tx
			while(!(LPC_CAN2->GSR&(1<<3)));		  //Check Tx Bit
		}
		unsigned int can_rx_8bytes(){ //CAN1 as Rx
	   while((LPC_CAN1->GSR&(1<<0)));
	   MSG[0]=LPC_CAN1->RID;
	       MSG[1]=LPC_CAN1->RDA;						//Load data to Variable
	       MSG[2]=LPC_CAN1->RDB;
		   LPC_CAN1->CMR=(1<<2);	 //Release to buffer
		   return MSG[1];
		 return MSG[2];
		  return MSG[0];}