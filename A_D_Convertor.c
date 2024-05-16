#include <stdio.h> 
#define CHANNEL_0 0xFF204000
#define CHANNEL_1 0xFF204004
#define CHANNEL_2 0xFF204008
#define CHANNEL_3 0xFF20400c
#define CHANNEL_4 0xFF204010
#define CHANNEL_5 0xFF204014
#define CHANNEL_6 0xFF204018
#define CHANNEL_7 0xFF20401C
#define SW_BASE 0xFF200040
#define JP1_BASE 0xFF200060
#define DIR_CONTROL 0xFF200064 

//reading the value of the switch
volatile int* const SW_ptr = (int) SW_BASE; 

//reading from the channel. channel 1 should tell us if there is a value there (auto-update)
volatile int* const channel_0 = (int*) CHANNEL_0; 
volatile int* const channel_1 = (int*) CHANNEL_1; 

volatile int* const dir_control = (int*) DIR_CONTROL; 
volatile int* const data_reg = (int*) JP1_BASE; 


//double knob_1 = 3.3;
//double knob_2 = 5;
//double knob_used = 0;
int number_leds = 11;


//we want to put the auto-updat e value in the channel1 address


void display_LEDS(int voltage){
	
	
	
	int corresponding_LED_ON[number_leds];
	
	corresponding_LED_ON[0] = 0x0;
    corresponding_LED_ON[1] = 0x1; //one led on
    corresponding_LED_ON[2] = 0x3;
    corresponding_LED_ON[3] = 0x7; 
    corresponding_LED_ON[4] = 0xF; 
    corresponding_LED_ON[5] = 0x1F;
    corresponding_LED_ON[6] = 0x3F;
    corresponding_LED_ON[7] = 0x7F; 
    corresponding_LED_ON[8] = 0xFF; 
    corresponding_LED_ON[9] = 0x1FF;
    corresponding_LED_ON[10] = 0x3FF; 
	
	
	
	*data_reg = corresponding_LED_ON[voltage];
	
}


void reading_channels(){
	
	
	if(*SW_ptr == 0){
		*channel_0 = 0x1;//refreshing
		volatile int value_of_channel = *channel_0;
		volatile unsigned int bit_fifteen = value_of_channel;
		bit_fifteen &= 0x8000;
		
		if(bit_fifteen != 0b0){
			int value_in_channel = value_of_channel & 0xFFF; 
			display_LEDS(value_in_channel*10/4000);
		}
		
	
	}
	else if(*SW_ptr == 1){
		*channel_1 = 0x1;//refreshing
		volatile int value_of_channel = *channel_1;
		volatile unsigned int bit_fifteen = value_of_channel;
		bit_fifteen &= 0x8000;
		
		
		
		if(bit_fifteen != 0b0){
			int value_in_channel = value_of_channel & 0xFFF; 
			display_LEDS(value_in_channel*10/4000);
		}
		
	}
}


int main(void){
  	while(1){
		*dir_control = 0x3FF;
	
		reading_channels();
	}
}
