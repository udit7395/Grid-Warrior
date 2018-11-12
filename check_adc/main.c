#include"sra.c"

void main()
{
port_init();
adc_init();
lcd_init(underline);
lcd_clear();

while(1)
{
lcd_write_int_xy( 0,0,adc_start(0),3);
lcd_write_int_xy( 4,0,adc_start(1),3);
lcd_write_int_xy( 8,0,adc_start(2),3);
lcd_write_int_xy( 12,0,adc_start(3),3);

lcd_write_int_xy( 0,1,adc_start(4),3);
lcd_write_int_xy( 4,1,adc_start(5),3);
lcd_write_int_xy( 8,1,adc_start(6),3);
lcd_write_int_xy( 12,1,adc_start(7),3);

/*lcd_write_int_xy( 8,1,b,3);  

lcd_write_int_xy( 1,2,c,3);

lcd_write_int_xy( 8,2,d,3);
*/

_delay_ms(500);


}


}
