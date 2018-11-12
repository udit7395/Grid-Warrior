#include "sra.c"
#include<math.h>


int ledno = 0, count = 0, countl = 0, countr = 0, dir = 0, north = 1, south = -1, east = 2, west = -2;
float mpos = 0;

int l = 0, x = 0, y = 0, z = 0;

unsigned int opt = 330, control = 0;

int current_x = 0;
int current_y = 0;

int digi = 0, digi1 = 0;

void line_track()
{
	check_sensors();
	bot_forward();

	switch (sensorbyte)
	{
	case 0b0110:mpos = 0; break;

	case 0b1100:mpos = 1; break;

	case 0b0011:mpos = -1; break;

	case 0b0100:mpos = 1.25; break;

	case 0b0010:mpos = -1.25; break;

	case 0b1000:mpos = 2; break;

	case 0b0001:mpos = -2; break;

	case 0b0111:mpos = 0; break;

	case 0b1111:mpos = 0; break;

	case 0b1110:mpos = 0; break;

	case 0b0000:mpos = 0; break;

	default:break;
	}

	OCR1A = opt + 30 * mpos;
	OCR1B = opt - 30 * mpos;
	delay_microsec(500);

}


int check_digital()                                            //right digi on 6th & left on 7th
{
	digi = 0;
	for (int i = 0; i < 2; i++)                                             //for white it will give 1
	{
		if (adc_start(i + 6) < 105)
			digi += pow(2, i);
	}
	if (adc_start(4) < 105)
		l++;
	if (adc_start(5) < 105)
		l++;
	//lcd_clear();

	//lcd_write_int_xy(0,0,digi,3);
	return digi;
}

void strip_track()                                              //using digital sensors
{

	switch (check_digital())
	{

	case 2: y = 0; z = 0;
		if (sensorbyte != 0b0000 && l > 0)
		{
			x++; l = 0;
			if (x == 1)
			{
				countl++; ledno++;
				sbi(PORTC, ledno);
			}
		}
		break;

	case 1: x = 0; z = 0;
		if (sensorbyte != 0b0000 && l > 0)
		{
			y++; l = 0;
			if (y == 1)
			{
				countr++;
				ledno++;
			}
		}
		break;

	case 3: x = 0; y = 0;
		z++;
		if (z == 1)
			count = count + 1;
		break;

	case 0: x = 0; y = 0; z = 0;
		break;
	}
}

int right90()
{
	while (adc_start(2) < 100 || adc_start(1) < 100)
	{
		OCR1A = 300;
		OCR1B = 300;
		bot_spot_right();
	}

	while (1)
	{
		bot_spot_right();
		OCR1A = 300;
		OCR1B = 300;

		if (adc_start(3) < 100)
		{
			while (1)
			{
				bot_spot_right();
				OCR1A = 300;
				OCR1B = 300;
				if (adc_start(1) < 100)
				{
					bot_stop();
					return 0;
				}
			}

		}
	}

}

int left90()
{
	while (adc_start(2) < 100 || adc_start(1) < 100)
	{
		bot_spot_left();
		OCR1A = 300;
		OCR1B = 300;

	}

	while (1)
	{
		bot_spot_left();
		OCR1A = 300;
		OCR1B = 300;

		if (adc_start(0) < 100)
		{
			while (1)
			{
				bot_spot_left();
				OCR1A = 300;
				OCR1B = 300;
				if (adc_start(2) < 100)
				{
					bot_stop();
					return 0;
				}
			}

		}
	}

}

void thoda_aage()
{
	while (adc_start(6) < 100 || adc_start(7) < 100)
	{
		bot_forward();
		OCR1A = 399;
		OCR1B = 399;
	}
	bot_stop();
}

void face(int direction)                                 //makes the bot face in a particular direction
{
	int a = direction + dir;
	if (abs(dir) == 1)
	{
		if (abs(a) == 3)
			right90();
		if (abs(a) == 1)
			left90();
		if (abs(a) == 0)
		{
			left90();
			left90();
		}
	}
	if (abs(dir) == 2)
	{
		if (abs(a) == 3)
			left90();
		if (abs(a) == 1)
			right90();
		if (abs(a) == 0)
		{
			left90();
			left90();
		}
	}
}

void go_to(int abcissa, int ordinate)
{
	if (abcissa > current_x)
	{
		face(north);
		dir = north;
	}
	if (abcissa < current_x)
	{
		face(south);
		dir = south;
	}


	while (count != abs(abcissa - current_x))
	{
		strip_track();
		line_track();
		LED &= 0xF0;               //where is the increament in current co-ordinate
		LED |= sensorbyte;

	}
	lcd_clear();
	lcd_write_int_xy(0, 0, count, 3);

	bot_stop();
	//_delay_ms(2000);  
	count = 0;
	current_x = abcissa;

	if (ordinate > current_y)
	{
		face(east);
		dir = east;
	}

	if (ordinate < current_y)
	{
		face(west);
		dir = west;
	}
	while (count != abs(ordinate - current_y))
	{
		strip_track();
		line_track();
		LED &= 0xF0;
		LED |= sensorbyte;
	}
	lcd_clear();
	lcd_write_int_xy(0, 0, count, 3);

	count = 0;
	current_y = ordinate;
	bot_stop();
	// _delay_ms(2000);

}

void stage1()
{
	while (sensorbyte != 0b0000)
		line_track();
}

void stage2()
{
	while (sensorbyte != 0b0000)
	{
		line_track();
		strip_track();
	}
	PORTC = 0x00;
}

void stage3()
{
	while (sensorbyte != 0b0000)
	{
		line_track();
		strip_track();
	}
	PORTC = 0x00;
}

void stage4()
{
	while (sensorbyte != 0b0000)
	{
		line_track();
		strip_track();
	}
	PORTC = 0x00;
}

void stage5()
{
	while (digi != 3)
	{
		line_track();
		strip_track();
	}
	PORTC = 0x00;
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
	while (1)
	{



		if (pressed_switch2())              //pressing s2 pattern1 will execute
		{

			check_sensors();
			LED = sensorbyte;

		}

		if (pressed_switch3())              //pressing s2 pattern1 will execute
		{
			lcd_clear();
			sensorbyte = 1;
			// retrieve_threshold();
			while (1)
			{
				stage1();
				stage2();
				int x1 = ledno;
				ledno = 0;
				stage3();
				int y1 = ledno;
				ledno = 0;
				stage4();
				ledno = 0;
				stage5();
				ledno = 0;
				int p = countl;
				int q = countr;
				lcd_write_int_xy(0, 0, x1, 2);
				lcd_write_int_xy(4, 0, y1, 2);
				lcd_write_int_xy(8, 0, p, 2);
				lcd_write_int_xy(12, 0, q, 2);

				thoda_aage();
				count = 0;
				go_to(x1, y1);
				go_to(p, q);
				int x2 = 0;
				if (x1 > p)
					x2 = x1;
				else x2 = p;
				int y2 = 0;
				if (y1 < q)
					y2 = y1;
				else y2 = q;
				go_to(x2, y2);
				break;
			}

		}

	}

}

