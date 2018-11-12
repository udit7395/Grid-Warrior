#include"sra.c"

void init_devices()
{
     port_init();
     pwmservo_init();  
    
	 
}

//-------------------------------------------------//

void main()
{ 

init_devices();

while(1)
{

 if(pressed_switch0())
{
   bot_forward();
   OCR1B=1200;
   _delay_ms(3000);
   bot_stop();
}
	
 if(pressed_switch1())  
  
//-----------Bot fullway into slot-------------------------------//
 {
   bot_backward();
   OCR1B=1200;
   _delay_ms(3000);
   bot_stop();

  }
    
  if(pressed_switch2())
  {
	
	OCR1A=132;
    _delay_ms(1000);
	flick();
	OCR1B=590;
    _delay_ms(1000);

  }
 

}
}