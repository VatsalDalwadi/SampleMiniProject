/*
  This program simulate Air Outlet Control.
  Input: Air Outlet Modes Knob
  Output: LEDs simulation of air outlets
  - YuPui 4-10-2018
*/

#include<stdint.h>
#include<avr/io.h>
#include<util/delay.h>

#define SET_BIT(PORT,BIT) PORT|= (1<<BIT)
#define CLR_BIT(PORT,BIT) PORT&= ~(1<<BIT)
# define F_CPU 16000000UL

int main()
{
  //Set up port C pin 0 as analog output
  DDRC=(0<<0);
  PORTC=(0<<0);
  
  //Analog input initializtion
  ADMUX=0x00;
  ADMUX |=_BV(REFS0)|_BV(MUX3)|_BV(MUX2)|_BV(MUX1)|_BV(MUX0);

  ADCSRA=0x00;
  ADCSRB=0x00;
  ADCSRA |=_BV(ADEN) | _BV(ADPS2) |_BV(ADPS1) | _BV(ADPS0);
  ADCSRA |= _BV(ADSC);
  
  //Set up port D pin 5,6,and 7 as digital output
  SET_BIT(DDRD,PD5);
  SET_BIT(DDRD,PD6);
  SET_BIT(DDRD,PD7);
  CLR_BIT(PORTD,PD5); 
  CLR_BIT(PORTD,PD6); 
  CLR_BIT(PORTD,PD7);
  
  while(1) //super loop
  {
    //Start reading value from port C pin 0
    ADMUX &= 0xf0;
    ADMUX |= 0X0;   // port C pin 0
    ADCSRA |= _BV(ADSC);
  
    if(ADC<200)
    {
      SET_BIT(PORTD,PD5);
      CLR_BIT(PORTD,PD6); 
      CLR_BIT(PORTD,PD7);
    }
    if(ADC<400 && ADC>=200)
    {
      CLR_BIT(PORTD,PD5); 
      SET_BIT(PORTD,PD6);
      CLR_BIT(PORTD,PD7);
    }
    if(ADC<600 && ADC>=400)
    {
      SET_BIT(PORTD,PD5);
      SET_BIT(PORTD,PD6); 
      CLR_BIT(PORTD,PD7);
    }
    if(ADC<800 && ADC>=600)
    {
      SET_BIT(PORTD,PD5); 
      CLR_BIT(PORTD,PD6);
      SET_BIT(PORTD,PD7);
    }
    if(ADC>800)
    {
      CLR_BIT(PORTD,PD5); 
      CLR_BIT(PORTD,PD6);
      SET_BIT(PORTD,PD7);
    }

    _delay_ms(100);  
  }
}