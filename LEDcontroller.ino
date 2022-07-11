#include <FastLED.h>
#define NUM_LEDS 64
#define DATA_PIN 2

CRGB leds[NUM_LEDS];
int h=0;
int s=100;
int v=1;
int i=1;

int value;
char command;

//============

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    Serial.begin(9600);
    Serial.println("Testing LEDs");
    running_dot(50);
    Serial.println("This code expects 2 pieces of data - command follow by an integer");
    Serial.println("Enter data in this style 'c100'");
    Serial.println();
    
}

//============

void loop() {
  if (Serial.available() >= 4)
  {
    command = Serial.read();
    switch (command)
    {
    case 'h': value = Serial.parseInt();
      // Set h value
      showParsedData();
      h = value;
      break;

    case 's': value = Serial.parseInt();
      // Set s value
      showParsedData();
      h = value;
      break;
      
    case 'v': value = Serial.parseInt();
      // Set v value
      showParsedData();
      v = value;
      break;

    case 'i': value = Serial.parseInt();
      // Set i value
      showParsedData();
      i = value;
      break;
      
    case 'S': value = Serial.parseInt();
      // Save settings to led
      showParsedData();
      leds[i].setHSV( h, s, v);
      break;      
      

      
    case 'o': value = Serial.parseInt();
      // Turn off selected LED
      showParsedData();
      leds[i].setHSV( 0, 0, 0);
      break;     

    case 'O': value = Serial.parseInt();
      // Turn off all LED
      showParsedData();
      for(int dot = 0; dot < NUM_LEDS; dot++) 
        { 
          leds[dot] = CRGB::Black;
        }
      break;   
      
    case 'D': value = Serial.parseInt();
      // Display saved array
      showParsedData();
      FastLED.show();
      break;  
           
//============ Built in annimations
      
    case 'd': value = Serial.parseInt();
      // moving dot
      showParsedData();
      running_dot(value);
      break;

    case 'a': value = Serial.parseInt();
      // Light all
      showParsedData();
      for(int dot = 0; dot < NUM_LEDS; dot++) 
        { 
          leds[dot].setHSV( h, s, v);
        }
       FastLED.show();
      break;

    case 'f': value = Serial.parseInt();
      // Slowly fill grid
      showParsedData();
      for(int dot = 0; dot < NUM_LEDS; dot++) 
        { 
          leds[dot].setHSV( h, s, v);
          FastLED.show();
          delay(value);
        }
      break;
      
    case 'r': value = Serial.parseInt();
      // rainbow
      showParsedData();
      rainbow(value);
      break;      
      
    default: Serial.print("Unexpected input recieved: '");
      Serial.print(command);
      serial_flush_buffer();        
      Serial.println("\'");
    }
  }
}

//============

void serial_flush_buffer()
{
  while (Serial.read() >= 0)
   Serial.print(Serial.read()); // do nothing
}

void showParsedData() {
    Serial.print("Command ");
    Serial.println(command);
    Serial.print("Integer ");
    Serial.println(value);
}

void running_dot(int wait) {
    for(int dot = 0; dot < NUM_LEDS; dot++) 
      { 
        leds[dot].setHSV( h, s, v);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot] = CRGB::Black;
        delay(wait);
      }
    FastLED.show();
}

void rainbow(int steps) {
    for(long firstPixelHue = 0; firstPixelHue < (steps-1)*255/NUM_LEDS; firstPixelHue += 255/NUM_LEDS) {
      for(int dot = 0; dot< NUM_LEDS; dot++) { // For each pixel in strip...
        int pixelHue = firstPixelHue + (dot * 255 / NUM_LEDS);
        leds[dot].setHSV( pixelHue, s, v);
        //Serial.print((String)"LED: " + dot + " Hue: " + pixelHue);
        //Serial.print("\n");
      }
      FastLED.show();
      delay(50);
  }
}
