#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


const int sensorPin = 0;
const int sensorPin2 = 1;
const int ledPin = 9;
const int ledPin2 = 10;
int from = 0;
int to = 8;
int readBinary(char*);
String finalResult = "";
int counter = 345;

int lightVal;
int lightVal2;

String result = "";
void setup()
{
  // We'll set up the LED pin to be an output.
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  //we will take a single reading from the light sensor and store it in the lightCal
  //variable. This will give us a prelinary value to compare against in the loop
}


void loop()
{
  //Take a reading using analogRead() on sensor pin and store it in lightVal
  lightVal = analogRead(sensorPin); 
  lightVal2 = analogRead(sensorPin2);


  if (lightVal < 450) // if '1' LED is off
  {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
  }

  else if(lightVal >= 450 && lightVal2 < 450) // if '1' LED is on
  {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    if(analogRead(sensorPin)>450 && digitalRead(9)) {

      result = result + "0";
      counter = 355;
      digitalWrite(9, LOW);

        
    }else{

      result = result + "1";
      counter = 345;
    }
    
  }
  if (lightVal2 < 450) // if '0' LED is off
  {
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
  }
  else if(lightVal2 >= 450 && lightVal < 450) // if '0' LED is on
  {
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);  
    if(analogRead(sensorPin2)>450 && digitalRead(10)) {

      digitalWrite(10, LOW);
      counter = 355;
      result = result + "1";
        
    }else{

      result = result + "0";
      counter = 345;
    }
  }
  if(lightVal < 450 && lightVal2 < 450) { // standby

    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    
  }
  if(result.length()%8 == 0 && result.length() > 0) {
    
    result = result.substring(from,to);
    if(result.length()>0) {

      int decimal = readBinaryString(result.c_str());
      result = "";
      char c = (char) decimal;
      if(decimal == 8) {

        finalResult = finalResult.substring(0,finalResult.length()-1);
        
      } else if((decimal >= 48 && decimal <= 57) || 
      (decimal >= 65 && decimal <= 90) || 
      (decimal >= 97 && decimal <= 122)|| 
      decimal == 32 ) {

        finalResult = finalResult + c;
        
      }
      result = "";
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println(finalResult);
      display.display();
    }
  }
  delay(counter);
  //lightVal = analogRead(sensorPin); 
  //lightVal2 = analogRead(sensorPin2);
}

int readBinaryString(char* s) {
  int result = 0;
  while(*s) {
    result <<= 1;
    if(*s++ == '1') result |= 1;
  }
  return result;
}
