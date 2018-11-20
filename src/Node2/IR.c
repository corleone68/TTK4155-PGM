#include <avr/io.h>
#include "adc.h"
#include "ir.h"

static uint16_t filter_limit = 100;


uint8_t ir_get(void){
	#define FILT_ORD 4
	
	// Check if value is below threshold
	#if FILTER_ORDER == 1
	return analogRead(0) < filter_limit;
	#else
	static uint16_t filter[FILT_ORD-1];

	uint16_t ir_val = analogRead(0);
	uint16_t avg = ir_val;

	// Use average value with higher order filter
	for(uint8_t i = 0; i < FILT_ORD-2; i++){
		avg += filter[i];
		filter[i] = filter[i+1];
	}
	avg += filter[FILT_ORD-2];
	filter[FILT_ORD-2] = ir_val;
	
	// Returns 1 if obstructed
	return avg/FILT_ORD < filter_limit;
	#endif
}
