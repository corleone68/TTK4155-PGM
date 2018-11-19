
#include "PID.h"
#include "motor.h"

#define F_CPU 16000000UL
#include <util/delay.h>


ISR(TIMER2_OVF_vect){
	timer_flag = 1;
}

void initializePID(void){

	cli(); // Disable global interrupts
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22); // start timer2 with /1024 prescaler
	TIMSK2=(1<<TOIE2); // enable timer overflow interrupt for Timer2
	sei(); // Enable global interrupts
}

void calibratePosition(void){
	setDirection(LEFT);
	PIDcontroller(50);
	int16_t current_pos = readEncoder();//reads current position
	int16_t previous_pos = current_pos+200; //initialize previous position
	
	
	
	while(previous_pos != current_pos){
		previous_pos = current_pos;
		_delay_ms(40);
		current_pos = readEncoder();
	}
	
	setSpeed(0);//stop the motor
	_delay_us(500);
	resetEncoder();

	setDirection(RIGHT);
	PIDcontroller(40);
	current_pos = 0;
	previous_pos = current_pos-200;

	
	while(previous_pos != current_pos){
		previous_pos = current_pos;
		_delay_ms(50);
		current_pos = readEncoder();
	}
	setSpeed(0);
	position_max = current_pos;
	
}
void PID(uint8_t ref){

        int16_t output = 0;
		uint8_t out_abs = 0;
	   if (timer_flag){
		TIMSK2 &= ~(1 << TOIE2); //disable interrupt while handling PID 
		
		int16_t measurement  = readEncoder();
		double  position = map((double) measurement,0.0, pos_max,0.0,255.0);


		/*//Saturation of position
		if(pos_ref >240){
			pos_ref = 240;
		} else if(pos_ref<10){
			pos_ref = 10;
		}*/
		
		int16_t error = ref - (int)position;
		integral = integral + (error * SampleTime);

	    if(abs(integral) < outMin){
             integral = outMin;
        } 
        else if(abs(integral) > outMax){
            if(integral > 0)
                integral = outMax;
            else
                integral = -outMax;
        }
	
		double derivative = (error - last_error)/SampleTime;
		
		int16_t u = Kp*error + Ki*integral + Kd*derivative;
		last_error = error;
        
        
          if (abs(u) > outMax)
          { 

            if( u > 0)
                output = outMax;
            else
                output = -outMax;
         
          }
          else if( abs(u) <= outMin)
          {
            if( u > 0)
                output = outMin;
            else
                output = -outMin;
            
          }
          else
          {
            output = u;
          }
		if (output < 0){
			setDirection(LEFT);
			out_abs = -speed;
		}
		else{
			setDirection(RIGHT);
			out_abs = speed;
		}

		PIDcontroller(out_abs);
		timer_flag = 0;
		TIMSK2 |= (1 << TOIE2); //Enable timer interrupt again 
	}
}

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

