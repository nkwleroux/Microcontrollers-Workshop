/*
 * UltraSonicSensor.h
 *
 * Created: 20/3/2021 3:03:44 PM
 *  Author: Nic & Jorn
 */ 

#ifndef UltraSonicSensor_H_
#define UltraSonicSensor_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void ussensor_init(void);
void ussensor_pulse_signal(void);
int calculate_distance(void);
int get_i(void);

#endif /* UltraSonicSensor_H_ */