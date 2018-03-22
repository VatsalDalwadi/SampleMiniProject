
void setup()
{
	pinMode(5, OUTPUT);
	pinMode(7, INPUT);
	Serial.begin(9600);
}

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

int main(void)
{
	int inches = 0;
	int cm = 0;
	setup();
	for (;;) 
	{
		  // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");
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
	return 0;
}
