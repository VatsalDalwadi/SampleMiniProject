"Copyright 2018 <Fabrice Kamaha>"
#include<stdint.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#pragma pack(1)
// Define Macros
#define SET_BIT(PORT, BIT) PORT |= (1 << BIT)
#define CLR_BIT(PORT, BIT) PORT &= ~(1 << BIT)
#define TOGGLE_BIT (PORT, BIT) PORT ^= (1 << BIT)
// assigne different ports
#define SystemOn         PORTB1  // Green LED
#define StartButton      PORTB5  // Push Button
#define BatteryPower     PORTC0  // Potentiometer 1
#define ConsumePower     PORTC1  // Potentiometer 2
#define RecoverdPower    PORTC2  // Potentiometer 3
#define SystemOff        PORTD2  // System runing out of power
#define ChargerOn        PORTD4  // Charging system On
#define RecoveringPower  PORTD7  // Energy is being recover
#define BLINK_DELAY_MS 1000
#define Treshold    300
uint16_t Battery, PowerR, PowerC, CurrentP;
uint8_t pinC0 = 0;
uint8_t pinC1 = 1;
uint8_t pinC2 = 2;
volatile int Flag = 0;

int main(void) {
  Serial.begin(9600);
  SET_BIT(DDRB, PORTB1);  // Set PORTB1 as output
  CLR_BIT(DDRB, PORTB5);  // Set PORTB1 as input
/* set pin 7,4and 2 of PORTD for output*/
  SET_BIT(DDRD, SystemOff);
  SET_BIT(DDRD, ChargerOn);
  SET_BIT(DDRD, RecoveringPower);
/* set pin 0 , 1 and 2 of PORTC as input*/
  CLR_BIT(DDRC, PORTC0);
  CLR_BIT(DDRC, PORTC1);
  CLR_BIT(DDRC, PORTC2);
  while (1) {
  initialize();
  if (!(PINB & (~(1 << StartButton)) )) {  // The car system is on
// 1 ---Checking if the initial power in the battery is enough
  if (0 == Flag) {
  Flag = 1;
  do {
  Battery = ReadADC(pinC0);
  } while (Battery < 300);
  SET_BIT(DDRB, SystemOn);  // Turn on Green LED
  } else {  // The car is already runing
  Battery  =  ReadADC(pinC0);
  PowerR   =  ReadADC(pinC1);
  PowerC   =  ReadADC(pinC2);
  if (PowerR > 0) {
  SET_BIT(PORTD, ChargerOn);  // Charging
  } else {
  CLR_BIT(PORTD, ChargerOn);
  }
  CurrentP = Battery + PowerR - PowerC;
  while (CurrentP < 0) {
  // Too much energy is being consumed
  // CLR_BIT(DDRB,SystemOn); Turning off the green LED
  CLR_BIT(DDRD, RecoveringPower);  // Turning Blue LED Off
  SET_BIT(PORTD, SystemOff);
  _delay_ms(50);
  CLR_BIT(PORTD, SystemOff);
  _delay_ms(50);
  CurrentP = ReadADC(pinC0) + ReadADC(pinC2)- ReadADC(pinC1);
  }
  CLR_BIT(PORTD, SystemOff);
  if (ReadADC(pinC1) >= ReadADC(pinC2)) {
  SET_BIT(DDRD, RecoveringPower);  // Energy is being recovered
  } else {
  CLR_BIT(DDRD, RecoveringPower);  // No recovering
  }
  }
// Make sure we have enough energy in the battery to drive
  } else {  // Car system is off
  SET_BIT(PORTD, SystemOff);
  _delay_ms(50);
  CLR_BIT(PORTD, SystemOff);
  _delay_ms(50);
  SET_BIT(PORTD, SystemOff);
  _delay_ms(50);
  CLR_BIT(PORTD, SystemOff);
  _delay_ms(50);
  SET_BIT(PORTD, SystemOff);
  _delay_ms(50);
  CLR_BIT(PORTD, SystemOff);
  _delay_ms(50);
  CLR_BIT(PORTB, PORTB1);
  }
  }
}
void initialize() {
  ADMUX = 0x00;
  ADMUX |= _BV(REFS0)|_BV(MUX3)|_BV(MUX2)|_BV(MUX1)|_BV(MUX0);
  ADCSRA = 0x00;
  ADCSRB = 0x00;
  ADCSRA |= _BV(ADEN)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);
  ADCSRA |= _BV(ADSC);
  while ((ADCSRA & _BV(ADSC))) {}
}
uint16_t ReadADC(uint8_t pin) {
  uint16_t readVal = 0;
  DDRC = (0 << pin);
  PORTC = (0 << pin);
  ADMUX &= 0xf0;
  ADMUX |= pin;
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC)) {}
  readVal = ADC;
  return readVal;
}
}
