/* BrightDot example program by Pieter Sijmons @ Velleman NV */
/* Based on the NeoPixel Ring simple sketch by Shae Erisson */

//***DECLARATIONS
//NEOPIXEL library
//Download the Adafruit NeoPixel library @ https://github.com/adafruit/Adafruit_NeoPixel/archive/master.zip
//& put extracted files in Arduino Library (…/Arduino/Libraries)
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the BrightDots?
// On a VMW100 this is 12, on VMW101 this is 19
#define PIN            T5

// How many BrihgtDots are attached to the Arduino?à
// On a VMW100 this is 24
#define NUMPIXELS      10

//Set the brightness value (max:255, but not recommended!)
#define brightnessValue 150

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second

//***SETUP (run once)
void setup()
{
  Serial.begin(9600);       //Start Serial output & output string
  Serial.println("BrightDot example program started");

  pixels.begin();                         // This initializes the NeoPixel library.
  pixels.setBrightness(brightnessValue);  // full brightness=255 (not recommended)
  pixels.show();                          // Initialize all pixels to 'off'
  Serial.print("Brightness level= ");
  Serial.print(brightnessValue);          // Print out the brightness value to the serial port
  Serial.println("/255");

  // Some example procedures showing how to display to the pixels:
  Serial.println("Turn all LEDs to RED");
  colorWipe(pixels.Color(255, 0, 0), 50);         // Red
  Serial.println("Turn all LEDs to GREEN");
  colorWipe(pixels.Color(0, 255, 0), 50);         // Green
  Serial.println("Turn all LEDs to BLUE");
  colorWipe(pixels.Color(0, 0, 255), 50);         // Blue
  Serial.println("Turn all LEDs to WHITE");
  colorWipe(pixels.Color(255, 255, 255), 50);     // White
  Serial.println("Turn all LEDs off");
  colorWipe(pixels.Color(0, 0, 0), 5);            // Off
  //rainbow(50);
}


//***LOOP
void loop()
{
    Serial.println("Cycle color of all LEDs at the same time");
    rainbow(100);                               //cycle all BrightDots together
    colorWipe(pixels.Color(0, 0, 0), 50);       //turn off
    Serial.println("Cycle color of individual LEDs");
    rainbowCycle(100);                          //cycle each BrightDot
    Serial.println("Turn to white");
    colorWipe(pixels.Color(255, 255, 255), 50); //white
    delay(5000);                                //wait 5 seconds (5000 milliseconds)
    Serial.println("Turn all LEDs off");
    colorWipe(pixels.Color(0, 0, 0), 5);        //off
}


//***FUNCTIONS
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
  for(uint16_t i=0; i<pixels.numPixels(); i++)
  {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(wait);
  }
}

//cycle all the brightdots together
void rainbow(uint8_t wait)
{
  uint16_t i, j;

  for(j=0; j<256; j++)
  {
    for(i=0; i<pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
  if(WheelPos < 85)
  {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170)
  {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else
  {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
