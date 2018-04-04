/*
 todo
  */
#define INIT_TEMP 153 // inital set up temperature 25C, 153 in sensor value
#define CRIT_TEMP 300 // critical temperature ~100C
#define CRIT_TEMP_DIFF 100 // critical temperature difference
#define BLINK_DUR 10 // blink duration ~20s, or 10 blinks

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

int lastTemperSensorValue = INIT_TEMP;
int blinkCt12 = 0;
int blinkCt13 = 0;

void loop()
{
  // Temperature sensor get the value 
  int temperSensorValue = analogRead(A0);
  Serial.println(temperSensorValue);
  Serial.println(lastTemperSensorValue); 
  if (temperSensorValue > CRIT_TEMP )
    blinkCt12 = BLINK_DUR; 
  if (temperSensorValue - lastTemperSensorValue > CRIT_TEMP_DIFF)
    blinkCt13 = BLINK_DUR; 
  lastTemperSensorValue = temperSensorValue;
  // polling rate 0.5/s
  if (blinkCt12 > 0 || blinkCt13 > 0)
    ledBlink();
  else
    delay(2000);
}

void ledBlink()
{
  // turn the LED on (HIGH is the voltage level)
  if ( blinkCt12 > 0 )
    digitalWrite(12, HIGH);
  if ( blinkCt13 > 0 )
    digitalWrite(13, HIGH);
  delay(1000);// Wait for 1000 millisecond(s)
  // turn the LED off by making the voltage LOW
  if ( blinkCt12 > 0 )
  {
    digitalWrite(12, LOW);
    blinkCt12--;
  }
  if ( blinkCt13 > 0 )
  {
    digitalWrite(13, LOW);
    blinkCt13--;
  }
  delay(1000); // Wait for 1000 millisecond(s)
}