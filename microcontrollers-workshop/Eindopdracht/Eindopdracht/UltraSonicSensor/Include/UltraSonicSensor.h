/*
 * UltraSonicSensor.h
 *
 * Created: 20/3/2021 3:03:44 PM
 *  Author: Nic
 */ 

#ifndef UltraSonicSensor_H_
#define UltraSonicSensor_H_

#include <avr/io.h>
#include <util/delay.h>

void ussensor_init(void);
void ussensor_pulse_signal(void);

#endif /* UltraSonicSensor_H_ */