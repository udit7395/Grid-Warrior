#include"sra.c"

void main()
{
port_init();
while(1)
{

nt check_digital()                                            //right digi on 6th & left on 7th
{digi=0;
	for(int i=0;i<2;i++)                                             //for white it will give 1
	{
	if(adc_start(i+4)<100)
       digi+=pow(2,i);
	}
	
	 //lcd_clear();
	
	//lcd_write_int_xy(0,0,digi,3);
 return digi;	
}     

void strip_track()                                              //using digital sensors
{ 
	

	
	switch(check_digital())
	{
	
	case 2: y=0;z=0; 	
               if(sensorbyte!=0b0000)
               {  
			   x++;
               if(x==1) 
               countl++;
               }  
               break;   
         
   case 1: x=0;z=0;
              if(sensorbyte!=0b0000)
              {
			  y++;
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


}


}
