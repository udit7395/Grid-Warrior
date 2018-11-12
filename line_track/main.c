#include "sra.c"
#include<math.h>



unsigned int opt = 330, control = 0,mpos=0;


void line_track()
{
    check_sensors();
	bot_forward();
	
	switch(sensorbyte)
	{ 
		case 0b0110:mpos=0;break;

		case 0b1100:mpos=1;break;

		case 0b0011:mpos=-1;break;
        
		case 0b0100:mpos=1.25;break;
		
		case 0b0010:mpos=-1.25;break;
		
		case 0b1000:mpos=2;break;

		case 0b0001:mpos=-2;break;

		case 0b0111:mpos=0;break;
		
        case 0b1111:mpos=0;break;
		
		case 0b1110:mpos=0;break;
        
		case 0b0000:mpos=0;break;
		
        default    :break;
	 }
	 
     OCR1A=opt+30*mpos;
	 OCR1B=opt-30*mpos;
     delay_microsec(500);

}



void right90()
{  
while(adc_start(2)<100||adc_start(1)<100)
{
OCR1A=300;
OCR1B=300;
bot_spot_right();
}

while(1)
{
bot_spot_right();
OCR1A=300;
OCR1B=300;

if(adc_start(3)<100)
 {
   while(1)
    {bot_spot_right();
     OCR1A=300;
     OCR1B=300;
   if(adc_start(1)<100)
     break;
   }
break;

}
}

bot_stop();
//flick();
}

void left90()
{ 
while(adc_start(2)<100||adc_start(1)<100)
{
OCR1A=300;
OCR1B=300;
bot_spot_left();
}

while(1)
{
bot_spot_left();
OCR1A=300;
OCR1B=300;

if(adc_start(0)<100)
 {
   while(1)
    {bot_spot_left();
     OCR1A=300;
     OCR1B=300;
   if(adc_start(2)<100)
     break;
   }
break;

}
}

bot_stop();
//flick();
}

void thoda_aage()
{while(bit_is_clear(PIND,6)||bit_is_clear(PIND,7))
      {bot_forward();
	   OCR1A=320;
       OCR1B=320;
	  }
 bot_stop();
}

	  
void init_devices(void)
{ 

 port_init();
 adc_init();
 bot_motion_init();
 lcd_init(underline);
 switch_init();
 pwm1_init();
 
}

void main()
{
init_devices();
 while(1)
 {
 
 /* if(pressed_switch0())              //pressing s1 blink1portpin will execute
  {
  
   calibrate_white();
   set_threshold();
   lcd_clear();
   lcd_write_int_xy(0,0,adc_start(0),3);
   lcd_write_int_xy(5,0,adc_start(1),3);
   lcd_write_int_xy(9,0,adc_start(2),3);
   lcd_write_int_xy(0,1,adc_start(3),3);		
   flick();
   lcd_clear();
   lcd_write_string_xy(0,0,"white calibrated");
   
  }

  if(pressed_switch1())
  {
  
   calibrate_black();
   set_threshold();
   lcd_clear();
   lcd_write_int_xy(0,0,adc_start(0),3);
   lcd_write_int_xy(5,0,adc_start(1),3);
   lcd_write_int_xy(9,0,adc_start(2),3);
   lcd_write_int_xy(0,1,adc_start(3),3);
   flick();
   lcd_clear();
   lcd_write_string_xy(0,0,"black calibrated");
  }*/
				
  if(pressed_switch2())              //pressing s2 pattern1 will execute
  {
  
   check_sensors();
   LED=sensorbyte;
   
  }
		
  if(pressed_switch3())              //pressing s2 pattern1 will execute
  {
    
	
	lcd_clear();
  
  // retrieve_threshold();
   while(1)
   {line_track();
   LED&=0xFF;
   LED=sensorbyte;
   }
   
}

}

}

