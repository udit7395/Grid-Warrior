#include "sra.c"
#include<math.h>


int count=0,countl=0,countr=0,dir=0,north=1,south=-1,east=2,west=-2;
float mpos=0;

int x=0,y=0,z=0,l=0,r=0;

unsigned int opt = 330, control = 0;

int current_x=0;
int current_y=0;

int digi=0;

void line_track()
{
    check_sensors();
	bot_forward();
	
	switch(sensorbyte)
	{ 
		case 0b0110:mpos=0;break;

		case 0b1100:mpos=1.25;break;

		case 0b0011:mpos=-1.25;break;
        
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
	 
	 if(mpos==0)
	 {
	 OCR1A=399;
	 OCR1B=399;
	 }
	 
     else
	 {
	 OCR1A=opt+30*mpos;
	 OCR1B=opt-30*mpos;
	 }
	 
     delay_microsec(500);

}


int check_side()                                            //right digi on 6th & left on 7th
{
int	side=0;
	
	for(int i=0;i<2;i++)                                             //for white it will give 1
	{
	if(adc_start(i+6)<105)
    side+=pow(2,i);
	}
	
	/*if(adc_start(4)<105)
	l++;
	if(adc_start(5)<105)
	l++;  */
	
	return side;	
}     

void strip_track()                                              //using digital sensors
{ 
	

	
	switch(check_side())
	{
	
	case 2: y=0;z=0; 	
               if(sensorbyte!=0b0000&&l>0)
               {  
			   x++;l=0;
               if(x==1) 
               countl++;
               }  
               break;   
         
   case 1: x=0;z=0;
              if(sensorbyte!=0b0000&&r>0)
              {
			  y++;r=0;
              if(y==1)
              countr++;
              }
              break;
			  
   case 3: x=0;y=0;
              z++;
              if(z==1)
              count=count+1;
              break;
             
   case 0: x=0;y=0;z=0;
              break;
   } 
}  

int right90()
{ thoda_aage();
while(adc_start(2)<100||adc_start(1)<100)
{
bot_spot_right();
OCR1A=350;
OCR1B=350;

}

while(1)
{
bot_spot_right();
OCR1A=350;
OCR1B=350;

if(adc_start(0)<100)
 {
   while(1)
   {
	bot_spot_right();
    OCR1A=350;
    OCR1B=350;
	
   if(adc_start(2)<100)
   {
   bot_stop();
  	 return 0;
   }
   }

}
}

}

int left90()
{thoda_aage(); 

while(adc_start(2)<100||adc_start(1)<100)
{
bot_spot_left();
OCR1A=350;
OCR1B=350;
}

while(1)
{
bot_spot_left();
OCR1A=350;
OCR1B=350;
if(adc_start(3)<100)
{
while(1)
{
	bot_spot_left();
    OCR1A=350;
    OCR1B=350;
   if(adc_start(1)<100)
   {
   bot_stop();
   return 0;
   } 
}

}
}

}

void thoda_aage()
{while(adc_start(6)<100||adc_start(7)<100)
      {bot_forward();
	   OCR1A=320;
       OCR1B=320;
	  }
 bot_stop();
}

void face(int direction)                                 //makes the bot face in a particular direction
{ 
	int a=direction+dir;
	if(abs(dir)==1)
    {
	if(abs(a)==3)
	right90();
	if(abs(a)==1)
	left90();
	if(abs(a)==0)
    {
	left90();
	while(adc_start(0)<110)
    {
     bot_spot_left();
     OCR1A=300;
     OCR1B=300;
    }
    left90(); 
	}
    }
  if(abs(dir)==2)
     {
	 if(abs(a)==3)
     left90();
     if(abs(a)==1)
     right90();
	 if(abs(a)==0)
	 {
	 left90();
 while(adc_start(0)<110)
   {
     bot_spot_left();
     OCR1A=300;
     OCR1B=300;
    }
     
   left90(); 
	 }
     }
}        		

void go_to(int abcissa,int ordinate)
{ 
	if(abcissa>current_x)    
    {
	face(north);
    dir=north;
	}
    if(abcissa<current_x)
    {
	face(south);
    dir=south;
    }
    
	
    while(count!=abs(abcissa-current_x))
    {
	strip_track(); 
    line_track(); 
	}  
	bot_stop();
     
    count=0;    
    current_x=abcissa;
	
    if(ordinate>current_y)
    {
	face(east);
    dir=east;
	}
	
    if(ordinate<current_y) 
	{
	face(west);
    dir=west;    
    }
	while(count!=abs(ordinate-current_y))
    {
	strip_track(); 
    line_track();
	
	} 
	
 count=0;
 current_y=ordinate;
 bot_stop();
 
}

	  
void init_devices(void)
{ 

 port_init();
 adc_init();
 bot_motion_init();
  switch_init();
 pwm1_init();
 
}

void init_led()
{

DDRC=0xFF;
PORTC=0x00;

DDRD=0xF0;
PORTD=0x0F;
}

void main()
{

init_devices();
init_led();
 while(1)
 {
 
 
				
  if(pressed_switch2())              //pressing s2 pattern1 will execute
  {
  
   check_sensors();
   LED&=0xF0;
   LED|=sensorbyte;
    }
		
  if(pressed_switch3())              //pressing s2 pattern1 will execute
  {
    
	
	 
  
   while(1)
   {
   
   
   go_to(1,0);
    sbi(PORTC,0);
    go_to(1,1);
    sbi(PORTC,1);
	go_to(2,1);
	sbi(PORTC,2);
	go_to(2,0);
	sbi(PORTC,3);
	PORTC=0x00;
	go_to(3,0);
	sbi(PORTC,0);
	go_to(3,1);
	sbi(PORTC,1);
	go_to(2,1);
	sbi(PORTC,2);
	go_to(2,0);
	sbi(PORTC,3);
	go_to(1,0);
	sbi(PORTC,3);
	
	
	break;
 
	
   }
   
}

}

}

