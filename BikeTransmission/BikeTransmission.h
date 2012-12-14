/*
 * BikeTransmission.h - Bicycle Modeling Classes for Arduino
 * Version 0.1
 *
 * This is file is part of a my final graduation work.
 * This code is intended to be used with an arduino to
 * automatically control gear changes of a commom
 * bycicle derailleur.
 *
 * Author: Paulo S. Machado
 * Date: October 2011
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
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <Servo.h>

#ifndef BikeTransmission_h
#define BikeTransmission_h
#endif

/** 
 * Rear wheel model
 */
class RearWheel {
public:
 	/// Wheel diameter in meters
    float diameter;
	/// Constructor
    RearWheel ( float _diameter );
	/// Calculate and return linear speed
    int get_lspeed ( long unsigned int T );
};

/** 
 * Derailleur class representation
 */
class Derailleur {
public:
	/// Calculate the engaged gear from cycle time ratio
    int get_gear ( unsigned long c_t, unsigned long w_t );
 	/// Decide and move derailleur to appropriate gear
    void set_gear ( Servo motor, int gear, long int c_t, long int w_t, float K );
};

