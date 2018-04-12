/*
  This program simulate HAVC Control.
  Input: Ventilation Knob, Temperature Knob, A/C switch
  Output: Fans and LEDs simulation of HVAC
  -YuPui 4-10-2018
*/
#include<stdint.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define SET_BIT(PORT,BIT) PORT|= (1<<BIT)
#define CLR_BIT(PORT,BIT) PORT&= ~(1<<BIT)
# define F_CPU 16000000UL

volatile uint16_t ventIn = 0;
volatile uint16_t tempIn = 0;

void setup()
{
  //Set up port C pin 0 as analog output
  //Ventilation Knob
  DDRC=(0<<0);
  PORTC=(0<<0);

  //Set up port C pin 0 as analog output
  //Temperature Knob
  DDRC=(0<<1);
  PORTC=(0<<1);
  
  //Analog input initializtion
  ADMUX=0x00;
  ADMUX |=_BV(REFS0)|_BV(MUX3)|_BV(MUX2)|_BV(MUX1)|_BV(MUX0);

  ADCSRA=0x00;
  ADCSRB=0x00;
  ADCSRA |=_BV(ADEN) | _BV(ADPS2) |_BV(ADPS1) | _BV(ADPS0);
  ADCSRA |= _BV(ADSC);
  
  //Set port D pin 7 as digital input
  // A/C on/off switch
  CLR_BIT(PORTD,PD7);
  
  // Set up pin 9, 10, 11 as output
  SET_BIT(DDRB,PB3);
  SET_BIT(DDRB,PB2);
  SET_BIT(DDRB,PB1);
  CLR_BIT(PORTB,PB3); 
  CLR_BIT(PORTB,PB2); 
  CLR_BIT(PORTB,PB1); 
  
  // Set up timer 1 channel A for PWM output on pin 9
  sbi(TCCR1A, COM1A1);
  // Set up timer 1 channel B for PWM output on pin 10
  sbi(TCCR1A, COM1B1);
  // Set up timer 2 channel A for PWM output on pin 11
  sbi(TCCR2A, COM2A1);
}

void loop()
{
  // read the analog in value:
  //Start reading value from port C pin 0
  ADMUX &= 0xf0;
  ADMUX |= 0X0;   // port C pin 0
  ADCSRA |= _BV(ADSC);
  
  _delay_ms(10);
  ventIn = ADC;
  
  //Start reading value from port C pin 0
  ADMUX &= 0xf0;
  ADMUX |= 0X1;   // port C pin 1
  ADCSRA |= _BV(ADSC);
  
  _delay_ms(10);
  tempIn = ADC;
    
  // analog output to pin 9 drive the fans
  OCR1A = ventIn/4;
  
  // determine heating or cooling
  if (tempIn>600) 
  // Heating
  {
    // analog output to pin 10 and 11
  	OCR1B = (tempIn-600)/2;
    OCR2A = 0;
  }
  if (tempIn<=600 && tempIn>400)
  // Off
  {
    OCR1B = 0;
    OCR2A = 0;
  }
  if (tempIn<400)
  // Cooling, A/C on depend on switch input
  {
    OCR1B = 0;
  	OCR2A = (200-tempIn/2)*(PIND>>7);
  }
}

int main()
{
  setup();
  while(1) //super loop
  {
    loop();
  }
}