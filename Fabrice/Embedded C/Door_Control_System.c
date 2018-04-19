"Copyright 2018 <Fabrice Kamaha>"
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
#define LED1 PORTD4
#define LED2 PORTB0
#define LED3 PORTB2
#define LED4 PORTB3
#define SET_BIT(PORT, BIT) PORT |=  (1 << BIT)
#define CLR_BIT(PORT, BIT) PORT &= ~(1 << BIT)
#define TEST_BIT(PORT, BIT)PORT & (1 << BIT)
#define BLINK_DELAY_MS 1000

int main(void) {
  unsigned int mask, extract_bit;
  Serial.begin(9600);
  SET_BIT(DDRB, PORTB0);
  SET_BIT(DDRB, PORTB2);
  SET_BIT(DDRB, PORTB3);  // Set PIN 0 2 and 3 of PORTB as output
  SET_BIT(DDRD, PORTD4);  // Set Pin4 of PORTD output
  while (1) {
// mask = (1<<PORTD2);
// PORTD |= (1<<PORTD4);
// PORTB |= (1<<PORTB0)|(1<<PORTB2)|(1<<PORTB3);
// PORTB |= (1<<PORTB4);
// extract_bit = PORTD & mask;
  if (TEST_BIT(PIND, PIND2)) {  // Check if the input on PORTD2 is set to 1
  CLR_BIT(PORTD, LED1);  // Turn off LED1
  } else {
  SET_BIT(PORTD, LED1);
  }
  if (TEST_BIT(PIND, PIND7)) {  // Check if the input on PORTD7 is set to 1
  CLR_BIT(PORTB, LED2);  // Turn off LED2
  } else {
  SET_BIT(PORTB, LED2);  // Otherwise turn it on
  }
  if (TEST_BIT(PINB, PINB4)) {  // Check if the input on PORTD7 is set to 1
  CLR_BIT(PORTB, LED3);  // Turn off LED3
  } else {
  SET_BIT(PORTB, LED3);  // Otherwise turn it on
  if (TEST_BIT(PINB, PIND5)) {  // Check if the input on PORTD7 is set to 1
  CLR_BIT(PORTB, LED4);  // Turn off LED2
  } else {
  SET_BIT(PORTB, LED4);  // Otherwise turn it on
  }
  return 0;
}
