#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Makes an array that holds the bytes that turn the lights on or off
byte leds[4] = {B10001000, B01000100, B00100010, B00010001};

//Sets the LCD screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Sets the bool that makes sure you can't reset the loop once started
bool fuckMilan = false;

//Sets all the pin numbers 
int dataPin = 2;
int latchPin = 3;
int clockPin = 4;
int keyPin = 5;
int buttonLightPin = 6;
int buttonPin = 7;

//Takes an input number that switchs the LEDs to whatever number in the array
void SwitchLights(byte lights)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds[lights]);
  digitalWrite(latchPin, HIGH);
}

//Resets the LEDs
void LightsOff()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  digitalWrite(latchPin, HIGH);
}

//Runs on bootup
void setup() 
{
  //Sets all the pins
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(keyPin, INPUT_PULLUP);
  pinMode(buttonLightPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  //Starts and resets LCD
  lcd.begin();

  //Resets lights
  LightsOff();
}

//Runs every tick
void loop() 
{
  //Turns button light on or off based on key
  if(digitalRead(keyPin) == LOW)
  {
    digitalWrite(buttonLightPin, HIGH); 
  }
  else
  {
    digitalWrite(buttonLightPin, LOW);
  }

  //Turns on LEDs and tells Milan to go fuck himself
  if(digitalRead(buttonPin) == LOW && digitalRead(keyPin) == LOW && !fuckMilan)
  {
    fuckMilan = true;
    lcd.print("FUCK YOU MILAN");
    for(int j = 0; j < 30; j++)
    {
      for(int i = 0; i < 4; i++)
      {
        delay(125);
        SwitchLights(i);
      }
    }
    //Resets everything
    lcd.clear();
    fuckMilan = false;
    LightsOff();
  }
}
