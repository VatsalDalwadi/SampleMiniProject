#include <avr/io.h>
#include <util/delay.h>
 
#define BLINK_DELAY_MS 1000


#include "wiring_private.h"
#include "pins_arduino.h"

uint8_t analog_reference = DEFAULT;

void analogReference(uint8_t mode)
{
	// can't actually set the register here because the default setting
	// will connect AVCC and the AREF pin, which would cause a short if
	// there's something connected to AREF.
	analog_reference = mode;
}

 
int main (void)
{
  Serial.begin(9600);
 /* set pin 7,4and 2 of PORTD for output*/ 
 DDRD |= _BV(DDD7)|_BV(DDD4)|_BV(DDD2);
  
 /* set pin 0 as input*/
 DDRC = DDRC & 0x00;
 uint16_t Potent_value =0;
 uint8_t pin = 0; 
  
 while(1) {
   
   initialize();
   
   // using analog read function 
  
   Potent_value = ReadADC(pin);
   //Serial.println(Potent_value);
   Warning(Potent_value); 
 }
}


void initialize()
{  
  ADMUX = 0x00;
  ADMUX |= _BV(REFS0)|_BV(MUX3)|_BV(MUX2)|_BV(MUX1)|_BV(MUX0);
  ADCSRA = 0x00;
  ADCSRB = 0x00;
  ADCSRA |= _BV(ADEN)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);
  ADCSRA |= _BV(ADSC);
  while((ADCSRA & _BV(ADSC)));
}
 
uint16_t ReadADC(uint8_t pin)
{
    uint16_t readVal = 0; 
               
               DDRC = (0<<pin);
               PORTC = (0<<pin);
               ADMUX &= 0xf0;
               ADMUX |= pin;
               ADCSRA |= _BV(ADSC);
               while (ADCSRA & _BV(ADSC));
               readVal=ADC;
               return readVal;
}
 
void Warning(uint16_t P_value){

  /* set pin 7 high to turn led on */
   if (P_value <= 400){
     PORTD |= _BV(PORTD7);
    _delay_ms(BLINK_DELAY_MS);
  /* set pin 7 low to turn led off */
     PORTD &= ~_BV(PORTD7);
    _delay_ms(BLINK_DELAY_MS);
    }
   if(P_value >400 && P_value < 800){
   /* set pin 4 high to turn led on */
     PORTD |= _BV(PORTD4);
    _delay_ms(BLINK_DELAY_MS);
  /* set pin 4 low to turn led off */
     PORTD &= ~_BV(PORTD4);
    _delay_ms(BLINK_DELAY_MS);
   }
   if(P_value >= 800){
   /* set pin 2 high to turn led on */
     PORTD |= _BV(PORTD2);
    _delay_ms(BLINK_DELAY_MS);
  /* set pin 2 low to turn led off */
     PORTD &= ~_BV(PORTB2);
    _delay_ms(BLINK_DELAY_MS);
   }

}