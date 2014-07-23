#include <LiquidCrystal.h>
#include <Wire.h>
#include "types.h"

/*******************************************************

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
keys_t lcd_key = NONE;

// read the buttons
keys_t read_LCD_buttons()
{
	int adc_key_in = analogRead(0);      // read the value from the sensor 
	// my buttons when read are centered at these valies: 0, 144, 329, 504, 741
	// we add approx 50 to those values and check to see if we are close
	if (adc_key_in > 1000) return NONE; // We make this the 1st option for speed reasons since it will be the most likely result
	// For V1.1 us this threshold
	if (adc_key_in < 50)   return RIGHT;  
	if (adc_key_in < 250)  return UP; 
	if (adc_key_in < 450)  return DOWN; 
	if (adc_key_in < 650)  return LEFT; 
	if (adc_key_in < 850)  return SELECT;  

	// For V1.0 comment the other threshold and use the one below:
	/*
	if (adc_key_in < 50)   return btnRIGHT;  
	if (adc_key_in < 195)  return btnUP; 
	if (adc_key_in < 380)  return btnDOWN; 
	if (adc_key_in < 555)  return btnLEFT; 
	if (adc_key_in < 790)  return btnSELECT;   
	*/


	return NONE;  // when all others fail, return this...
}

void setup()
{
	//Wire.begin();
	lcd.begin(16, 2);              // start the library
	lcd.setCursor(0,0);
	lcd.print("FM Radio: 000.00"); // print a simple message
}
 
void loop()
{
	lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
	lcd.print(millis()/1000);      // display seconds elapsed since power-up


	lcd.setCursor(0,1);            // move to the begining of the second line
	lcd_key = read_LCD_buttons();  // read the buttons

	switch (lcd_key) {             // depending on which button was pushed, we perform an action
	case RIGHT:
		lcd.print("RIGHT ");
		break;
	case LEFT:
		lcd.print("LEFT   ");
		break;
	case UP:
		lcd.print("UP    ");
		break;
	case DOWN:
		lcd.print("DOWN  ");
		break;
	case SELECT:
		lcd.print("SELECT");
		break;
	case NONE:
		lcd.print("NONE  ");
		break;
	}
}

