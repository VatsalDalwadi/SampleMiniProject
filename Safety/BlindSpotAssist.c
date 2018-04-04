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
#define NOTE_C4  262
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int inputPin = A0;
int inches = 0;
int cm = 0;
int melody[] = {NOTE_C4};
int noteDurations[] = {4};
int switch_1 = 0;

long readUltrasonicDistance(int pin)
{
	pinMode(pin, OUTPUT);  // Clear the trigger
	digitalWrite(pin, LOW);
	delayMicroseconds(2);
		// Sets the pin on HIGH state for 10 micro seconds
	digitalWrite(pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pin, LOW);
	pinMode(pin, INPUT);
		// Reads the pin, and returns the sound wave travel time in microseconds
	return pulseIn(pin, HIGH);
}
void setup()
{
	pinMode(5, OUTPUT);
	pinMode(7, INPUT);
	pinMode(4, INPUT);
	Serial.begin(9600);
		// initialize all the readings to 0:
	for (int thisReading = 0; thisReading < numReadings; thisReading++) 
	{
		readings[thisReading] = 0;
	}
}

void loop()
{
		// measure the ping time in cm
	cm = 0.01723 * readUltrasonicDistance(7);
		// convert to inches by dividing by 2.54
	inches = (cm / 2.54);
	delay(10); // Wait for 100 millisecond(s)
		// subtract the last reading:
	total = total - readings[readIndex];
		// read from the sensor:
	readings[readIndex] = analogRead(inputPin);
		// add the reading to the total:
	total = total + readings[readIndex];
		// advance to the next position in the array:
	readIndex = readIndex + 1;
		// if we're at the end of the array...
	if (readIndex >= numReadings) 
	{
		// ...wrap around to the beginning:
	readIndex = 0;
	}
		// calculate the average:
	average = total / numReadings;
		// send it to the computer as ASCII digits
	Serial.println(average);
	delay(1);        // delay in between reads for stability
	if(average >= 600)
	{
		if(inches < 31.0)
		{
			digitalWrite(5, HIGH);
			switch_1 == digitalRead(4);
			if(switch_1 == HIGH)
			{
              	int noteDuration = 1000 / 4;
				digitalWrite(8, HIGH);

			}
          	if(switch_1 == LOW)
			{
				digitalWrite(8, LOW);  
			}
		}
	}
  	else
  	{
  		digitalWrite(5, LOW);
  	}    
}