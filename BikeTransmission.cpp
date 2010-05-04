/* 
 * BikeTransmission.cpp - Bycicle Modeling Classes for Arduino
 * Version 0.1
 *
 * This is file is part of a my final graduation work.
 * This code is intended to be used with an arduino to 
 * automatically control gear changes of a commom 
 * bycicle derailleur.
 *
 * Author: Paulo S. Machado
 * Date: April 2010
 *
 * Release under de GNU Public License v3.0 or greater
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include "WProgram.h"
#include "BikeTransmission.h"
#include <Servo.h>

#define GEAR_MAX 7
#define GEAR_MIN 1

#define FULLCURSO 180
#define TOTAL_GEARS 6
// definir limites mínimo e máximo
// para velocidade de cadência
#define CADENCE_MIN 

/********* Constructors implementation ************/
front_gear::front_gear(int i){
	_size = i;	
}

rear_gear::rear_gear(int i){
	_size = i;
}

derailleur::derailleur(int slots){
	_slots = slots;
}

/********* Functions implementation ************
 * prototype:
 * type class_name::function_name(type parameters and parameters if any)
 * {
 * 		code;
 * }
 */

float front_gear::read_cadence_sensor(){
	// TODO actually reads sensor and
	// and return a integer value
	// return n;
}

bool front_gear::get_state(){ 
	if (this->read_cadence_sensor() != 0.0) { // very poor approach. 
		return true;
	}
	else { return false; }
}

int rear_gear::get_state(){ // is this really necessary?
	return state;
}

float rear_wheel::read_wspeed_sensor()
{
	// TODO
	// Implement read from sensor!
}



int derailleur::get_gear(rear_wheel wheel, front_gear fgear){
	// FIXME This function must calculate the 
	// speed ratio between cadence/wheel_speed
	// and return the
	float ratio, rs, fs;
	rs=wheel.read_wspeed_sensor();
	fs=fgear.read_cadence_sensor();
	if (fs != 0) {
		ratio=fs/rs;
		//These are invariant relations between the bycicle
		// teeth ratios. 
		// TODO:
		// * Find out the right relations
		// * (beyond TG) configurable ratios
		if (ratio < 1) {
			return(1);
		}
		else if (ratio < 2) {
			return(2);
		}
		else if (ratio < 3) {
			return(3);
		}
		else if (ratio < 4) {
			return(4);
		}
		else if (ratio < 5) {
			return(5);
		}
		else {
			return(6);
		}
	}
	else { return 0; } // Return code when coasting
}

void derailleur::set_gear (Servo motor)
{
	// TODO
	// pwm write position motor.write(pos)
	int gear;
	gear = this->get_gear();
	
}











