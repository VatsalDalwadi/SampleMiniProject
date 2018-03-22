/*
  Blind spot assistance Safety Feature.

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

   In this implementation if any other car in side lane comes with in blind spot which is less then 31.0 inches closer  to our car then it will give LED warning light o alert driver not to change lane.
   31.0 inches is taken just for the demonstration, It will be more then it depending on actual senario and respective sensors.
*/

int inches = 0;

int cm = 0;

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
  Serial.begin(9600);
  
}

void loop()
{
  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
//  Serial.print(inches);
//  Serial.print("in, ");
//  Serial.print(cm);
//  Serial.println("cm");
  delay(100); // Wait for 100 millisecond(s)
  if(inches < 31.0)
  {
  	digitalWrite(5, HIGH);
  }
  else
  {
  	digitalWrite(5, LOW);
  }
}