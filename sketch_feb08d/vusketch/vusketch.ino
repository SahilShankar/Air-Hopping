/*
  SparkFun Inventor's Kit
  Example sketch 07

  PHOTORESISTOR

  Read a photoresistor (light sensor) to detect "darkness" and turn on an LED when it
  is "dark" and turn back off again when it is "bright.

  This sketch was written by SparkFun Electronics,
  with lots of help from the Arduino community.
  This code is completely free for any use.
  Visit http://learn.sparkfun.com/products/2 for SIK information.
  Visit http://www.arduino.cc to learn about the Arduino.
*/


// As usual, we'll create constants to name the pins we're using.
// This will make it easier to follow the code below.

const int sensorPin = 0;
const int sensorPin2 = 1;
const int ledPin = 9;
const int ledPin2 = 10;

// We'll also set up some global variables for the light level a calibration value and
//and a raw light value
int lightCal;
int lightVal;
int lightCal2;
int lightVal2;

char result[]={'0','0','0','0','0','0','0','0'};
int count=0;
void setup()
{
  // We'll set up the LED pin to be an output.
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  lightCal = analogRead(sensorPin);
  lightCal2 = analogRead(sensorPin2);
  //we will take a single reading from the light sensor and store it in the lightCal
  //variable. This will give us a prelinary value to compare against in the loop
}


void loop()
{
  delay(50);
  for(int i=0;i<8;i++){
     result[i]='0';
    }
  //Take a reading using analogRead() on sensor pin and store it in lightVal
  lightVal = analogRead(sensorPin);  
  lightVal2 = analogRead(sensorPin2);

  //if lightVal is less than our initial reading (lightCal) minus 50 it is dark and
  //turn pin 9 HIGH. The (-50) part of the statement sets the sensitivity. The smaller
  //the number the more sensitive the circuit will be to variances in light.
  while (count<8){
  if (lightVal < lightCal - 50)
  {
    digitalWrite(9, HIGH);
  }

  else
  {
    digitalWrite(9, LOW);
    result[count] = '1';
  }
  if (lightVal2 < lightCal2 - 50)
  {
    digitalWrite(10, HIGH);
    
  }
  else
  {
    digitalWrite(10, LOW);
    result[count] = '0';
  }
  count++;
  }
  Serial.println(result);
  delay(100);
  count=0;
  loop();
}
