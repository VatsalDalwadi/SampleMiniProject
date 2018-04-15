#include<stdint.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

//Use for efficiently allocated the memory
#pragma pack(1)

// Define Macros
#define SET_BIT(PORT,BIT) PORT|= (1<<BIT)
#define CLR_BIT(PORT,BIT) PORT&= ~(1<<BIT)
#define TOGGLE_BIT(PORT, BIT) PORT^=(1<<BIT)
 
#define BLINK_DELAY_MS 1000


 
int main (void)
{
  Serial.begin(9600);
 /* set pin 7,4and 2 of PORTD for output*/ 

 SET_BIT(DDRD,PORTD2);
 SET_BIT(DDRD,PORTD4); 
 SET_BIT(DDRD,PORTD7);
 /* set pin 0 as input*/
 CLR_BIT(DDRC,PORTC0);
 
 uint16_t Potent_value =0;
 uint8_t pin = 0; 
  
 while(1) {
   
   initialize();
   
   // using analog read function 
   Potent_value = ReadADC(pin);
   // Signaling to the driver
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
     SET_BIT(PORTD,PORTD7);;
    _delay_ms(BLINK_DELAY_MS);
  /* set pin 7 low to turn led off */
     CLR_BIT(PORTD,PORTD7);
    _delay_ms(BLINK_DELAY_MS);
    }
   if(P_value >400 && P_value < 800){
   /* set pin 4 high to turn led on */
     SET_BIT(DDRD,PORTD4);
    _delay_ms(BLINK_DELAY_MS);
  /* set pin 4 low to turn led off */
     CLR_BIT(PORTD,PORTD4);
    _delay_ms(BLINK_DELAY_MS);
   }
   if(P_value >= 800){
   /* set pin 2 high to turn led on */
     SET_BIT(PORTD,PORTD2);
    _delay_ms(BLINK_DELAY_MS);
  /* set pin 2 low to turn led off */
     CLR(PORTD,PORTB2);
    _delay_ms(BLINK_DELAY_MS);
   }

}