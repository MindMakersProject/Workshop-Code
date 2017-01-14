//Hello Mind Makers, to add your own comments and notes start a line with "//"
// The #include means that your arduino will use the prebuilt NeoPixel Library. This library contains lots of prewritten commands that make controlling your neopixel easy! Google or search on Adafruit.com the Neopixel library for help and ideas
#include <Adafruit_NeoPixel.h>

//This is the pin your Arduino will use to communicate with the NeoPixels.
#define PIN 6

//these commands define where your switches are plugged into the arudino, tells your arduino the number of switches you have, and sets their initial value to 0. 
int swLocs[] = {7, 8, 9};
int swVals[] = {0, 0, 0};
int numSw = 3;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(36, PIN, NEO_GRB + NEO_KHZ800);


// void setup() is a section of code where commands and variables can be initialized. For example in this code we use the NeoPixel library function "strip.begin()" to start communicating with the LED rings     
void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  for (int i = 0; i < numSw; i++)
  {
    pinMode(swLocs[i], INPUT);
  }
}

// void loop() is what your arduino will running over and over once it gets through the initialization and void setup()
// in this loop we have a condition where we call a function called "anyTrue" that checks to see if any of the tactile switches are pressed, and if so which one
// if the switches are pressed, our main loop continues into a "while" loop that changes the behavior of the LED rings
// To play on your own and add functionality, it is possible to change how the "anyTrue function works and what data it sends to the main loop, it is possible to change the behavior of the tastebud when switches are pressed
// and its possible to add your own ideas and behaviors! 
void loop()
{

  int pressed = anyTrue();
  while (pressed > 0)
  {
    if (pressed == 1) {
      // if button one is pressed
      if (swVals[0] == 1) {
        for (int i = 0; i < 36; i++)
        {
          strip.setPixelColor(i, 250, 0, 170); // pink
          strip.show();
        }
        // if button two is pressed
      } else if (swVals[1] == 1) {
        for (int i = 0; i < 36; i++)
        {
          strip.setPixelColor(i, 32, 178, 170); // light green
          strip.show();
        }
        // if button three is pressed
      } else if (swVals[2] == 1) {
        for (int i = 0; i < 36; i++)
        {
          strip.setPixelColor(i, 255, 233, 0); // yellow
          strip.show();
        }
      }
    } else if (pressed == 2) {
      for (int i = 0; i < 36; i++)
      {
        strip.setPixelColor(i, 255, 0, 0);
        strip.show();
      }

    } else if (pressed == 3) {
      for (int i = 0; i < 36; i++)
      {
        strip.setPixelColor(i, random(0, 255), random(0, 255), random(0, 255)); // picks a random RGB value
        strip.show();
      } 
      delay(500); // wait 500 milliseconds
    }


    pressed = anyTrue();
  }
  for (int m = 0; m < 36; m++)
  {
    strip.setPixelColor(m, 80, 0, 110);
    strip.show();
  }
}

//Here is the function "anyTrue"
int anyTrue() {
  int count = 0;
  for (int k = 0; k < numSw; k++)
  {
    swVals[k] = digitalRead(swLocs[k]);
  }
  for (int i = 0; i < numSw; i++)
  {
    if (swVals[i] != 0)
    {
      count += 1;
    }
  }
  Serial.println(count);
  return count;
}

