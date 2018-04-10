#include <avr/io.h> 


#define TPMS_SENSORS_PIN             PC4
#define TPMS_SENSORS_ENCODER_PIN_1   PD6
#define TPMS_SENSORS_ENCODER_PIN_2   PD7
#define TPMS_SENSORS_INDICATOR_PIN   PD0
#define TIRE_PSI                     3.5
#define PERIOD_TO_CHECK              3000

#define SET_BIT(PORT,BIT) PORT|= (1<<BIT)
#define CLR_BIT(PORT,BIT) PORT&= ~(1<<BIT)
#define TOGGLE_BIT(PORT, BIT) PORT^=(1<<BIT)

volatile uint16_t counter=0x0;
struct 
{
  volatile unsigned int FLAG_ISR1:1;
}FLAG_BIT;

void delay_Tim0_Init();
ISR(TIMER0_OVF_vect);
float ConvertToVolts(float number);
float ADC_START_CONV(int pinNumber);
void  ADC_init(void); 






int main() 
{
  float frontRightTireRead;
  float frontLeftTireRead;
  float rearRightTireRead;
  float rearLeftTireRead;
  
  /* Initate timer0 for the use of counting delay time*/
  delay_Tim0_Init();
  
  
  /* Set pins PD0,PD6,PD7 in output mode for encoder and LED*/
  SET_BIT(DDRD,TPMS_SENSORS_ENCODER_PIN_1);
  SET_BIT(DDRD,TPMS_SENSORS_ENCODER_PIN_2);
  SET_BIT(DDRD,TPMS_SENSORS_INDICATOR_PIN);
  
  /* Clear PC4 to set the pin into input mode for analog sensors*/
  CLR_BIT(DDRC,TPMS_SENSORS_PIN);
  
 
  while(1)
  {
    if(FLAG_BIT.FLAG_ISR1==1)
    {
      FLAG_BIT.FLAG_ISR1=0; 
      /*Set the code to 00 to read the front right tire sensor*/
      CLR_BIT(PORTD,TPMS_SENSORS_ENCODER_PIN_1);
  	  CLR_BIT(PORTD,TPMS_SENSORS_ENCODER_PIN_2);
      ADC_init();
      frontRightTireRead=ConvertToVolts(ADC_START_CONV(TPMS_SENSORS_PIN));
    
      /*Set the code to 01 to read the front left tire sensor*/
      SET_BIT(PORTD,TPMS_SENSORS_ENCODER_PIN_1);
  	  CLR_BIT(PORTD,TPMS_SENSORS_ENCODER_PIN_2);
      ADC_init();
      frontLeftTireRead=ConvertToVolts(ADC_START_CONV(TPMS_SENSORS_PIN));
      
      //Set the code to 10 to read the rear right tire sensor
      CLR_BIT(PORTD,TPMS_SENSORS_ENCODER_PIN_1);
  	  SET_BIT(PORTD,TPMS_SENSORS_ENCODER_PIN_2);
      ADC_init();
      rearRightTireRead=ConvertToVolts(ADC_START_CONV(TPMS_SENSORS_PIN));
      
      /*Set the code to 11 to read the rear left tire sensor*/
      SET_BIT(PORTD,TPMS_SENSORS_ENCODER_PIN_1);
      SET_BIT(PORTD,TPMS_SENSORS_ENCODER_PIN_2);
      ADC_init();
      rearLeftTireRead=ConvertToVolts(ADC_START_CONV(TPMS_SENSORS_PIN));  
    
      /*check if the pressure less than TIRE_PSI in any tire*/
      if(frontRightTireRead<TIRE_PSI ||frontLeftTireRead <TIRE_PSI || 
         rearRightTireRead <TIRE_PSI ||rearLeftTireRead  <TIRE_PSI )
      {
        SET_BIT(PORTD,TPMS_SENSORS_INDICATOR_PIN);
      }
      else
      {
        CLR_BIT(PORTD,TPMS_SENSORS_INDICATOR_PIN);
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

void delay_Tim0_Init()
{
  TCCR0A|=0x00;
  TCNT0=0x00;
  TCCR0B|=((1<<CS00)|(1<<CS01));
  TCCR0B&=~(1<<CS02);
  TIMSK0|=(1<<TOIE0);
  SREG|=0x80;
  
}


ISR(TIMER0_OVF_vect)
{
  
  SREG&=~(0x80);
  CLR_BIT(SREG,0x80);
  counter++; 
  
  if (counter>=PERIOD_TO_CHECK)
  {
    FLAG_BIT.FLAG_ISR1=1;
    counter=0; 
  }
  sei(); 
}



