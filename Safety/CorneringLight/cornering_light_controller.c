#include <avr/io.h> 
#include <avr/delay.h> 
#include <util/delay.h> 

/* cycle length 40 000 ticks of Clock/8 using prescaler code  of 100 */
#define CYCLE_LENGTH 39999
#define MOVE_MOTOR_DEFAULT_POS(INDEX) INDEX==1?OCR1A=3604:OCR1B=3604;
#define MOVE_MOTOR_LIGHTING_POS(INDEX)  INDEX==1?OCR1A=2698:OCR1B=4600;

/* Macros to set, reset, and get a bit*/
#define SET_BIT(PORT,BIT) PORT|=(1<<BIT);
#define CLR_BIT(PORT,BIT) PORT&=~(1<<BIT);
#define GET_BIT(PORT,BIT) (PORT>>BIT)&1;

/* Constants definition*/
#define ANALOG_SENSORS_DDR  DDRC
#define LIGHT_SENSOR_PIN    PC0
#define STEERING_WHEEL_PIN  PC1

#define DIGITAL_IN_OUT_DDR  DDRD
#define DIGITAL_OUT_PORT    PORTD
#define DIGITAL_IN_PIN      PIND
#define DIRECTION_SIGANL_R  PD2
#define DIRECTION_SIGANL_L  PD4
#define HEAD_BEAM_LED       PD7

#define PWM_DDR             DDRB
#define RIGHT_SIDE_SERVO    PB1
#define LEFT_SIDE_SERVO     PB2

struct
{
  unsigned int CHECK_ONE:1;
  unsigned int CHECK_TWO:1;
  unsigned int CHECK_THREE:1;
  
}CASES_CHECK;


float ConvertToVolts(float number);
float ADC_START_CONV(int pinNumber);
void  ADC_Init(void); 


void fast_PWM_Tim1_Init();


int main() 
{
  uint8_t leftBlinkingRead=0;
  uint8_t rightBlinkingRead=0;
  float lightSensorRead=0.0f;
  float steeringWheelRead=0.0f;
  
  /* Set pins for input and output mode */
  CLR_BIT(DIGITAL_IN_OUT_DDR,DIRECTION_SIGANL_R)
  CLR_BIT(DIGITAL_IN_OUT_DDR,DIRECTION_SIGANL_L)
  
  SET_BIT(DIGITAL_IN_OUT_DDR,HEAD_BEAM_LED)
  
  CLR_BIT(ANALOG_SENSORS_DDR,LIGHT_SENSOR_PIN)
  CLR_BIT(ANALOG_SENSORS_DDR,STEERING_WHEEL_PIN)
  
  /* Initiate Fast PWM on timer1 to control servo motors */
  fast_PWM_Tim1_Init();
  
  
  CASES_CHECK.CHECK_ONE=0;
  CASES_CHECK.CHECK_TWO=0;
  CASES_CHECK.CHECK_THREE=1;
  MOVE_MOTOR_DEFAULT_POS(1)
  MOVE_MOTOR_DEFAULT_POS(2)
  _delay_ms(1000);  
 
  while(1)
  {
    
    rightBlinkingRead=GET_BIT(DIGITAL_IN_PIN,DIRECTION_SIGANL_R);
    leftBlinkingRead=GET_BIT(DIGITAL_IN_PIN,DIRECTION_SIGANL_L);
    ADC_Init();
    lightSensorRead=ConvertToVolts(ADC_START_CONV(LIGHT_SENSOR_PIN));
    ADC_Init();
    steeringWheelRead=ConvertToVolts(ADC_START_CONV(STEERING_WHEEL_PIN));
    if(lightSensorRead<0.9)
    {
      if(steeringWheelRead<1.75 && leftBlinkingRead==1)
         
      {
        if(CASES_CHECK.CHECK_ONE==0)
        {
          
          CASES_CHECK.CHECK_ONE=1;
          CASES_CHECK.CHECK_TWO=0;
          CASES_CHECK.CHECK_THREE=0;
          SET_BIT(DIGITAL_OUT_PORT,HEAD_BEAM_LED)
          MOVE_MOTOR_LIGHTING_POS(2);
           _delay_ms(1000); 
        }
        
      }
      
      else if(steeringWheelRead>3.25 && rightBlinkingRead==1)
      {
        if(CASES_CHECK.CHECK_TWO==0)
        {
          
          
          CASES_CHECK.CHECK_ONE=0;
          CASES_CHECK.CHECK_TWO=1;
          CASES_CHECK.CHECK_THREE=0;
          SET_BIT(DIGITAL_OUT_PORT,HEAD_BEAM_LED)
          MOVE_MOTOR_LIGHTING_POS(1);
           _delay_ms(1000); 
        }
       
      }
      
      else
      {
        if(CASES_CHECK.CHECK_THREE==0)
        {
          CASES_CHECK.CHECK_ONE=0;
          CASES_CHECK.CHECK_TWO=0;
          CASES_CHECK.CHECK_THREE=1;
          
          CLR_BIT(DIGITAL_OUT_PORT,HEAD_BEAM_LED)
          MOVE_MOTOR_DEFAULT_POS(1)
          MOVE_MOTOR_DEFAULT_POS(2)
          _delay_ms(1000); 
          
        }
        
       
      }
    }
    else
    {
      if(CASES_CHECK.CHECK_THREE==0)
        {
          CASES_CHECK.CHECK_ONE=0;
          CASES_CHECK.CHECK_TWO=0;
          CASES_CHECK.CHECK_THREE=1;
          
          CLR_BIT(DIGITAL_OUT_PORT,HEAD_BEAM_LED)
          MOVE_MOTOR_DEFAULT_POS(1)
          MOVE_MOTOR_DEFAULT_POS(2)
          _delay_ms(1000); 
          
        }
    }
  }
  return 0;
}

float ConvertToVolts(float num)
{    
  float voltage=(num/1024)*5.0;     
  return voltage;
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





static void ADC_Init(void)  
{    
  ADMUX=0x00;  
  ADMUX|=_BV(REFS0)|_BV(MUX3)|_BV(MUX2)|_BV(MUX1)|_BV(MUX0);
  ADCSRA=0x00;     
  ADCSRB=0x00;     
  ADCSRA |=_BV(ADEN) | _BV(ADPS2) |_BV(ADPS1) | _BV(ADPS0);
  ADCSRA |= _BV(ADSC);     
  while ( (ADCSRA & _BV(ADSC)) );  
}




void fast_PWM_Tim1_Init()
{
  /* Set ICR to number of ticks per pulse*/
  ICR1 = CYCLE_LENGTH;
  /* Set clock prescaler to CLK/8*/
  TCCR1B |= (1<<CS11);
  
  /* Set the wave generator to Fast PWM mode (mode 14)*/
  TCCR1B |= (1<<WGM13) |(1<<WGM12);
  TCCR1A |= (1<<WGM11);
  
  /* Set non-inverting mode for OC1A & OC1B*/
  TCCR1A |= (1<<COM1A1) |(1<<COM1B1);
  TCCR1A &= ~((1<<COM1A0) |(1<<COM1B0));
  
  /* Reset the timer */
  TCNT1 = 0;

  /* Set pins on PORTB for output mode */
  SET_BIT(PWM_DDR,RIGHT_SIDE_SERVO);
  SET_BIT(PWM_DDR,LEFT_SIDE_SERVO);
  
 
  
}