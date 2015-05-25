/*
  ESP_SerialLCD.cpp - Serial LCD driver Library for the ESP8266

  This library has been adapted to work with the ESP8266 board 
  from the original Serial LCD driver library developed for Arduino 
  by Seeed Technology Inc.

  Follows text from original SerialLCD.h
  ---------------

  SerialLCD.cpp - Serial LCD driver Library
  2011 Copyright (c) Seeed Technology Inc.  All right reserved.

  Original Author: Jimbo.We
  Contribution: Visweswara R
  
  Modified by Peter Gamache (KC0TFB) to support Arduino IDE 1.0 and unify
  support for all firmware (Grove SLCD firmware 0.9b, 1.0b, 1.1b)

  Note that not all firmware supports all features.  Power and Backlight
  commands may be ignored by earlier firmware.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include <inttypes.h>
#include "ESP_SerialLCD.h"

#define SERIAL_LIB Serial
#define SLCD_SEND(x) SERIAL_LIB.write(x)


ESP_SerialLCD::ESP_SerialLCD() {

}


/********** High level commands, for the user! **********/

// Initialize the Serial LCD Driver. ESP_SerialLCD Module initiates the communication.
void ESP_SerialLCD::begin()
{
    SERIAL_LIB.begin(9600);     //LCD va a 9600 sinó no funciona
    delay(2);
    noPower();
    delay(1);
    power();
    backlight();
    delay(1); 
    SLCD_SEND(SLCD_INIT_ACK);
// beginning of code that makes ESP8266 to reset 
    
	while(1)
    {
        if (SERIAL_LIB.available() > 0 && SERIAL_LIB.read()==SLCD_INIT_DONE)
            break;
    }
    
// end of code that makes ESP8266 to reset 
	delay(2);
}

//Turn off the back light
void ESP_SerialLCD::noBacklight()
{
    SLCD_SEND(SLCD_CONTROL_HEADER);   
    SLCD_SEND(SLCD_BACKLIGHT_OFF);   
}

//Turn on the back light
void ESP_SerialLCD::backlight()
{
    SLCD_SEND(SLCD_CONTROL_HEADER);   
    SLCD_SEND(SLCD_BACKLIGHT_ON);   
}

//Turn off the LCD
void ESP_SerialLCD::power()
{
    SLCD_SEND(SLCD_CONTROL_HEADER);   
    SLCD_SEND(SLCD_POWER_ON);   
}

//Turn on the LCD
void ESP_SerialLCD::noPower()
{
    SLCD_SEND(SLCD_CONTROL_HEADER);   
    SLCD_SEND(SLCD_POWER_OFF);   
}

// Clear the display
void ESP_SerialLCD::clear()
{
    SLCD_SEND(SLCD_CONTROL_HEADER);   
    SLCD_SEND(SLCD_CLEAR_DISPLAY);
    delay(2);//this command needs more time;  
}

// Return to home(top-left corner of LCD)
void ESP_SerialLCD::home()
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_RETURN_HOME);  
    delay(2);//this command needs more time;  
}

// Set Cursor to (Column,Row) Position
void ESP_SerialLCD::setCursor(uint8_t column, uint8_t row)
{
    delay(2);//this command needs more time;  
    SLCD_SEND(SLCD_CONTROL_HEADER); 
    SLCD_SEND(SLCD_CURSOR_HEADER); //cursor header command
    while(1)
    {
        if (SERIAL_LIB.available() > 0 && SERIAL_LIB.read()==SLCD_CURSOR_ACK)
            break;
    }
    SLCD_SEND(column);
    SLCD_SEND(row);
//one more to make sure the cursor is right
    delay(2);//this command needs more time;  
    SLCD_SEND(SLCD_CONTROL_HEADER); 
    SLCD_SEND(SLCD_CURSOR_HEADER); //cursor header command
    while(1)
    {
        if (SERIAL_LIB.available() > 0 && SERIAL_LIB.read()==SLCD_CURSOR_ACK)
            break;
    }
    SLCD_SEND(column);
    SLCD_SEND(row);
}

// Switch the display off without clearing RAM
void ESP_SerialLCD::noDisplay() 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_DISPLAY_OFF);    
}

// Switch the display on
void ESP_SerialLCD::display() 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_DISPLAY_ON);    
}

// Switch the underline cursor off
void ESP_SerialLCD::noCursor() 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_CURSOR_OFF);     
}

// Switch the underline cursor on
void ESP_SerialLCD::cursor() 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_CURSOR_ON);     
}

// Switch off the blinking cursor
void ESP_SerialLCD::noBlink() 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_BLINK_OFF);     
}

// Switch on the blinking cursor
void ESP_SerialLCD::blink() 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_BLINK_ON);     
}

// Scroll the display left without changing the RAM
void ESP_SerialLCD::scrollDisplayLeft(void) 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_SCROLL_LEFT);
}

// Scroll the display right without changing the RAM
void ESP_SerialLCD::scrollDisplayRight(void) 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_SCROLL_RIGHT);
}

// Set the text flow "Left to Right"
void ESP_SerialLCD::leftToRight(void) 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_LEFT_TO_RIGHT);
}

// Set the text flow "Right to Left"
void ESP_SerialLCD::rightToLeft(void) 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_RIGHT_TO_LEFT);
}

// This will 'right justify' text from the cursor
void ESP_SerialLCD::autoscroll(void) 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_AUTO_SCROLL);
}

// This will 'left justify' text from the cursor
void ESP_SerialLCD::noAutoscroll(void) 
{
    SLCD_SEND(SLCD_CONTROL_HEADER);
    SLCD_SEND(SLCD_NO_AUTO_SCROLL);
}

// Print Commands

void ESP_SerialLCD::print(const char b[])
{
    SLCD_SEND(SLCD_CHAR_HEADER);
    SLCD_SEND(b);
}


void ESP_SerialLCD::print(uint8_t b)
{
    SLCD_SEND(SLCD_CHAR_HEADER);
    SLCD_SEND(b);
}

void ESP_SerialLCD::print(unsigned long n, uint8_t base)
{
    unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
    unsigned long i = 0;

    if (base == 0) print(n);

    else if(base!=0)
    {
        if (n == 0) {
            print('0');
            return;
        }

        while (n > 0) {
            buf[i++] = n % base;
            n /= base;
        }

        for (; i > 0; i--)
            print((char) (buf[i - 1] < 10 ?
                          '0' + buf[i - 1] :
                          'A' + buf[i - 1] - 10));
    }
    //delay(1);
}

