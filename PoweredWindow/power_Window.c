//File Name:Powered_Window.c
//Author:Jedidiah Oyeyemi
//Company: KPIT Infosytems
//Project: Novi Traning mini project
//Tinkercad Schematic pathe:https://www.tinkercad.com/things/cNWSK3EJvSL-sizzling-amur/editel

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>    //file to be included if using interrupts
#include <inttypes.h>
#include <avr/eeprom.h>

/*Initilizing contants*/
#define F_CPU 16000000L
#define POT_STEP 170
#define TASK_UNIT_STEP_10_MS 10//wait time to update the PWM frequencty after reading from the ADC
#define XTAL    16000000L    // Crystal frequency in Hz
#define PRE_SCALE  64//prescale 
#define PWM_FREQUENCY    50
#define PWM_TASK_STEPS 10//the number of unit time steps before the potentiometer values are read 
#define SAFETY_TASK_STEPS 5//
#define BUTTON_SAMPLE_TIME 10//unit 10ms
#define SAFETY_THRESHOLD 300//
#define UP_BTN_LEFT  4
#define DOWN_BTN_LEFT  3
#define UP_BTN_RIGHT  2
#define DOWN_BTN_RIGHT  1
#define MAX_POS 40
#define LEFT_NVM   0x1000
#define RIGHT_NVM  0x1001


/* define all function prototypes */
void ADC_init();
uint16_t ADC_read(uint8_t);
void PWM16_init();
unsigned uint8_t pinMask(int pinOut);
void performWindowControl_ADC(void);
void recoverPositions(void);

/* Initialize Global variables*/
const float PWM_RANGE[MAX_POS+1]= {3,3.25,3.5,3.75,4,4.25,4.5,4.75,5,5.25,5.5,5.75,6,6.25,6.5,6.75,7,7.25,7.5,7.75,8,8.25,8.5,8.75,9,9.25,9.5,9.75,10,10.25,10.5,10.75,11,11.25,11.5,11.75,12,12.25,12.5,12.75,13};
uint8_t up_L,down_L,up_R,down_R;
uint8_t posL=0;
uint8_t posR=0;
int led=0;
boolean safetyDisable=false;
boolean driverAutoClose=false;
unsigned int pwmStepCounter=0;
//index 0 is left and index 1 is rights
int ICRVal=((F_CPU/PRE_SCALE/PWM_FREQUENCY) - 1 );
unsigned int initLeft=(unsigned int)(ICRVal*PWM_RANGE[0]/100);
unsigned int initRight=(unsigned int)(ICRVal*PWM_RANGE[0]/100);
volatile unsigned int pwmDutyCycle[]={initLeft,initRight};



uint8_t pinMask(int pinOut)
{
 //this function calculates the mask for a pin on an 8 pin port 
 
 uint8_t pinMaskVal=1;
 pinMaskVal=pinMaskVal<<pinOut;
 return pinMaskVal;
} 
void PWM_initialize(void)
{

 DDRB |= (1 << DDB1)|(1 << DDB2);
 //set clock speed
 ICR1=ICRVal; 
 //set pre scale to 64
 TCCR1B |= _BV(CS10)|_BV(CS11);  
 // Set wave generation mode for ICR1 fast pwm 
 TCCR1B|=_BV(WGM13)|_BV(WGM12);
 TCCR1A |=_BV(WGM11);
 //enable pwm on PB9 and PB10
 TCCR1A |=_BV(COM1A1)|_BV(COM1B1);
 //innitialize all counters to 0
 TCNT1=0;
 OCR1A =0 ;
 OCR1B= 0  ;  

 
}

static void ADC_pin(int adcpin)

{

DDRC=(0<<adcpin);

PORTC=(0<<adcpin);

}

static void ADC_initialize(void)

{

ADMUX=0x00;

ADMUX |=_BV(REFS0)|_BV(MUX3)|_BV(MUX2)|_BV(MUX1)|_BV(MUX0);

ADCSRA=0x00;

ADCSRB=0x00;

ADCSRA |=_BV(ADEN) | _BV(ADPS2) |_BV(ADPS1) | _BV(ADPS0);

ADCSRA |= _BV(ADSC);

while ( (ADCSRA & _BV(ADSC)) ); //sample not used

}

float ADC_start(int adcpin)

{

ADMUX &= 0xf0;

ADMUX |= adcpin;

ADCSRA |= _BV(ADSC);

while ( (ADCSRA & _BV(ADSC)) );

float fb=ADC;

return fb;

}

float ADC_read(int adcpin)

{

ADC_pin(adcpin);

ADC_initialize();

float adl=ADC_start(adcpin);

float v=((float)adl/1024)*5;

_delay_ms(10);

return adl;

}
float getDutyCycle(uint16_t posVal)
{   
  float dutyCycle=PWM_RANGE[posVal];
  return dutyCycle;  
}



void performSafeyCheck(void)
{
 uint16_t sensorValue = ADC_read(2); 
 if(sensorValue<SAFETY_THRESHOLD)
  {
    safetyDisable=true;
  }
  else
  {
    safetyDisable=false;
  }  
  }
boolean checkPinState(int pinNum)
{
 return (boolean)((PIND>>pinNum)&1);
}
uint8_t calcPos(boolean up,boolean down, uint8_t pos, boolean isLeftSide)
{
  if(down==true)
  {
    if(isLeftSide==true)
    {
      driverAutoClose=false;
      }
   
    if((up==false)&&(pos>0))
    { 
       pos=pos-1;
      
      }    
    }
  else if((pos<MAX_POS)&&(((up==true)&&(down==false))||((driverAutoClose==true)&&(isLeftSide==true))) )
  {
    pos=pos+1;
    if(isLeftSide==true)
    {
      driverAutoClose=true;
    }
   }


   //no change for invalid inputs
  return pos;
  }
void storePositions(int pos, uint16_t address)
{
  /* Wait for completion of previous write */  
  while(EECR & (1<<EEPE));
  /* Set up address and Data Registers */    
  EEAR = address;    
  EEDR = pos;    
  /* Write logical one to EEMPE */    
  EECR |= (1<<EEMPE); 

  
  }
void recoverPositions(void) 
{
  
  } 
void updateTargePosition(void)
{
  boolean lu,ld,ru,rd;
  lu=checkPinState(UP_BTN_LEFT);
  ld=checkPinState(DOWN_BTN_LEFT);
  ru=checkPinState(UP_BTN_RIGHT);
  rd=checkPinState(DOWN_BTN_RIGHT);  
  posL=calcPos(lu,ld,posL,true);
  posR=calcPos(ru,rd,posR,false);
}

void updatePWM(void)
{
  //pin 10 is left and pin 9 is right	
  OCR1B =(int)((ICRVal*(PWM_RANGE[posL]))/100);
  OCR1A=(int) ((ICRVal*(PWM_RANGE[posR]))/100);  
}

int main (void)
{
 /*Get the mask values of all the pins being used*/ 
 up_L=    _BV(UP_BTN_LEFT);
 down_L=  _BV(DOWN_BTN_LEFT);
 up_R=    _BV(UP_BTN_RIGHT);
 down_R=  _BV(DOWN_BTN_RIGHT);
 //Set  Input Pins DDRD
 DDRD &= ~(up_L|down_L|up_R|down_R);
 // Initialize the PWM pins 9 and 10 
 PWM_initialize(); 
 unsigned long unitTaskCount = 0;
 _delay_ms(TASK_UNIT_STEP_10_MS*10);
 while(1) {
   //Perform hand safety check before attempting to wind up the car window   
  if((unitTaskCount%SAFETY_TASK_STEPS)==0)
  {    
     performSafeyCheck();
    } 
  //Check button states   
  if((unitTaskCount%BUTTON_SAMPLE_TIME)==0)
  {
    updateTargePosition();
    }
  //Check for potentiometer changes every (PWM_TASK_STEPS *10) ms
  if((unitTaskCount%PWM_TASK_STEPS)==0)
  {
    updatePWM();          
  }

  //Other Changes for Feature 2 to detect kill switch button press
  //detect auto button and provide a safety feature to prevent the user's hand from getting hurt
  _delay_ms(TASK_UNIT_STEP_10_MS);
  unitTaskCount =unitTaskCount+1;
 }
}
