
#pragma once

#define SETT_JOY_GUN 1
#define SETT_SINGLE_AUTO 0

void scoretimer_init();
void system_loop();
ISR(TIMER1_OVF_vect);

