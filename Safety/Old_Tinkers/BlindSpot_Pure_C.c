#include <avr/io.h> 
#include <util/delay.h> 

#define POTENTIOMETER_PIN    0
#define DistancePOTENTIOMETER_PIN    1

float ADC_START_CONV(int pinNumber);
static void  ADC_init(void); 
static void  ADC_pin(int pinNumber);

int main() 
{
  int inches = 0;
  int cm = 0;
  DDRD |= (1<<PD5);
  DDRB |= (1<<PB0);
  DDRD &= ~(1<<PD7);
  DDRD &= ~(1<<PD4);
  Serial.begin(9600);
  ADC_pin(POTENTIOMETER_PIN);
  ADC_pin(DistancePOTENTIOMETER_PIN);
  while(1)
  {
    ADC_init();
    float speed_1=ADC_START_CONV(POTENTIOMETER_PIN);
  float distance=ADC_START_CONV(DistancePOTENTIOMETER_PIN);
  Serial.println(speed_1);
  Serial.println(distance);
  if((speed_1 > 500) && (distance > 500))
  {
      PORTD |= (1<<PD5);
      if((((PIND>>4)&0x01)) == 0x01)    
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