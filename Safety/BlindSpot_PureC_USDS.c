#include <avr/io.h> 
#include <avr/delay.h> 
#include <util/delay.h> 

#define POTENTIOMETER_PIN    0

float ADC_START_CONV(int pinNumber);
void  ADC_init(void); 
void  ADC_pin(int pinNumber);
long DistanceReading(int pin);

int main() 
{
  int inches = 0;
  int cm = 0;
  DDRD |= (1<<PD5);
  DDRB |= (1<<PB0);
  DDRD &= ~(1<<PD7);
  DDRD &= ~(1<<PD4);
  ADC_pin(POTENTIOMETER_PIN);
  while(1)
  {
	cm = 0.01723 * DistanceReading(7);
	// convert to inches by dividing by 2.54
	inches = (cm / 2.54);
    ADC_init();
    float speed=ADC_START_CONV(POTENTIOMETER_PIN);
	if((speed > 500) && (inches < 31.0))
	{
		PORTD |= (1<<PD5);
        if(((PIND>>PD4)&&1) == HIGH)
		{
			PORTB |= (1<<PB0);
		}
      	else
		{
			PORTB &= ~(1<<PB0);  
		}
	}
  	else
  	{
  		PORTD &= ~(1<<PD5);
  	}
  }
  return 0;
}

long DistanceReading(int pin)
{
  int i = 0;
  DDRD |= (1<<PD7);  // Clear the trigger
  PORTD &= ~(1<<PD7);
  for(i=2; i>0; i--);
  // Sets the pin on HIGH state for 10 micro seconds
  PORTD |= (1<<PD7);
  for(i=5; i>0; i--);
  PORTD &= ~(1<<PD7);
  DDRD &= (0<<PD7);
  // Reads the pin, and returns the sound wave travel time in microseconds
  return pulseIn(pin, HIGH);
}

float ADC_START_CONV(int pinNumber)
{
  ADMUX &= 0xf0;  
  ADMUX |= pinNumber;  
  ADCSRA |= _BV(ADSC);  
  while ( (ADCSRA & _BV(ADSC)) );  
  float fb=ADC;  
  return fb;
}
static void ADC_pin(int pinNumber)  
{      
  DDRC=(0<<pinNumber);      
  PORTC=(0<<pinNumber);  
} 
static void ADC_init(void)  
{    
  ADMUX=0x00;  
  ADMUX|=_BV(REFS0)|_BV(MUX3)|_BV(MUX2)|_BV(MUX1)|_BV(MUX0);
  ADCSRA=0x00;     
  ADCSRB=0x00;     
  ADCSRA |=_BV(ADEN) | _BV(ADPS2) |_BV(ADPS1) | _BV(ADPS0);
  ADCSRA |= _BV(ADSC);     
  while ( (ADCSRA & _BV(ADSC)) );  
}
float ADC_start(int pinNumber)  
{     
  ADMUX &= 0xf0;     
  ADMUX |= pinNumber;     
  ADCSRA |= _BV(ADSC);     
  while ( (ADCSRA & _BV(ADSC)) );    
  unsigned int fb=ADC;     
  return fb;  
} 