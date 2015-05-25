/*
 ********************** Demo_ESP_SerialLCD *****************
 * Demo for using ESP_SerialLCD library to communicate
 * a SerialLCD display with the ESP8266 board 
 *
 *********** This code is for the ESP8266***********
 *
 *  0.1  25/05/15 
 *
 *  Version:           0.1
 *  Design:            Somhi  
 *  Implementation:    Somhi
 */

// Import required libraries
#include <ESP_SerialLCD.h>

// Default values
int DELAY = 10000;        // check BTC price each x seconds (1000 = 1 s)

#define SERIAL_LIB slcd     // slcd - uses the ESP_SerialLCD library
//#define SERIAL_LIB Serial   // Serial - uses standard arduino Serial library
// To test output to serial interface, just comment all the lines with "slcd" 
// Also comment the #include <ESP_SerialLCD.h>  so don't need for this library to test serial output
// and uncomment #define SERIAL_LIB Serial    and   Serial.begin(9600);


// initialize the LCD library
ESP_SerialLCD slcd;          // should be same name as defined above in SERIAL_LIB

void setup(void)
{ 
  // Start Serial in case SERIAL_LIB is defined as Serial
//  Serial.begin(9600);

  slcd.begin();         // set up LCD
  slcd.noBacklight();	  // switch off backlight LCD  
  
  // Print a message to the LCD.
  SERIAL_LIB.print("Hello world");    
  delay(2000); 
  slcd.clear();
 
}

 
void loop() {
  
  slcd.clear();              // clear the display
  slcd.setCursor(1, 1);      // column 1, row 1 
  SERIAL_LIB.print("Test");
  
  delay(DELAY);

}
