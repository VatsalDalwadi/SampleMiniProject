/*
  Forward Collision Assistance.

  This implementation reads a PING))) ultrasonic
  rangefinder and returns the distance to the
  closest object in range. To do this, it sends a
  pulse to the sensor to initiate a reading, then
  listens for a pulse to return.  The length of
  the returning pulse is proportional to the
  distance of the object from the sensor.

  The circuit:
   * +V connection of the PING))) attached to +5V
   * GND connection attached to ground
   * SIG connection attached to digital pin 7

   In this implementation if any obstacle comes with in the 100 inches range of our car in front end it will turn on the warning which can be implemented for auto braking system.
*/

int inches1 = 0;
int inches2 = 0;
int inches3 = 0;

int cm1 = 0;
int cm2 = 0;
int cm3 = 0;

long readUltrasonicDistance(int pin)
{
  pinMode(pin, OUTPUT);  // Clear the trigger
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  // Sets the pin on HIGH state for 10 micro seconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  // Reads the pin, and returns the sound wave travel time in microseconds
  return pulseIn(pin, HIGH);
}

void setup()
{
  pinMode(5, OUTPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(4, INPUT);
  Serial.begin(9600);
  
}

void loop()
{
  // measure the ping time in cm
  cm1 = 0.01723 * readUltrasonicDistance(7);
  cm2 = 0.01723 * readUltrasonicDistance(6);
  cm3 = 0.01723 * readUltrasonicDistance(4);
  // convert to inches by dividing by 2.54
  inches1 = (cm1 / 2.54);
  inches2 = (cm2 / 2.54);
  inches3 = (cm3 / 2.54);
//  Serial.print(inches);
//  Serial.print("in, ");
//  Serial.print(cm);
//  Serial.println("cm");
  delay(100); // Wait for 100 millisecond(s)
  if((inches1 < 100.0) || (inches2 < 100.0) || (inches3 < 100.0))
  {
  	digitalWrite(5, HIGH);
  }
  else
  {
  	digitalWrite(5, LOW);
  }
}