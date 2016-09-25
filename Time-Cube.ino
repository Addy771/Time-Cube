/*
-Time Cube-
This sketch is used to create a time management device using an RGB LED.
The LED gently fades between two colors over a period of time
Refer to HSV-rainbow.jpg for color values

*/

#include <FastLED.h>
#define redPin 5
#define grnPin 6
#define bluPin 9

#define duration 3600 // Duration of the fade in seconds
#define startColor 160
#define endColor 255

#define increment ((duration * 1000ul) / 256)  // Split the total time into 256 steps

CRGB LED;
int phase = 0;
unsigned long int prevTime;


void setup() {
  // Configure the pins for each LED channel
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  
  // Start the timer by recording the current time
  prevTime = millis();
}

void loop() {

  // Compute the color to be displayed according to the phase, using 8-bit linear interpolation
  unsigned char currentHue = lerp8by8(startColor, endColor, phase);
  
  // Write the HSV values into a FastLED object so it can convert to RGB for us
  LED = CHSV(currentHue, 255, 255);
  
  // Write the outputs for each channel.
  updateLED();
 
  // Do nothing until enough time has passed
  while((millis() - prevTime) < increment);
  
  // Update the time
  prevTime = millis();
  
  // Increment phase until it reaches 255. At 255 the fading is complete
  if (phase < 255)
    phase++;
  else
  {
    // Now that fading is complete, flash the light to notify the user
    while(1)
    {
      LED = CHSV(endColor, 255, 255);
      
      updateLED();
      
      delay(500);
      
      LED = CRGB::Black;
      
      updateLED();   
    
      delay(500);  
    }
  }  
}

// Use analogWrite to generate PWM signals for each color channel. Color values come from global LED object
void updateLED(void)
{
  analogWrite(redPin, LED.r);
  analogWrite(grnPin, LED.g);
  analogWrite(bluPin, LED.b);    
}
