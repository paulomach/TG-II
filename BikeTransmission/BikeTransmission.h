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
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <Servo.h>


#ifndef BikeTransmission_h
#define BikeTransmission_h

#endif



/* FrontGear - front sprocket model
 * attributes:
 *
 * methods:
 *	read_cadence_sensor - update period of sprocket cycle
 */
class FrontGear {
public:
    //unsigned long read_cadence_sensor ( int c_reedPin );
};

/* RearWheel - rear wheel model
 * attributes:
 *	diameter - wheel diameter in meters
 * methods:
 *	read_wspeed_sensor - update period of wheel cycle
 *	get_lspeed - calculate and return linear speed
 */
class RearWheel {
public:
    float diameter;
    RearWheel ( float _diameter );
    //unsigned long read_wspeed_sensor ( int w_reedPin );
    int get_lspeed ( long unsigned int T );
};

/* Derailleur - derailleur model
 * attributes:
 *
 * methods:
 *	get_gear - calculate the engaged gear from cycle time ratio
 *	set_gear - decide and move derailleur to appropriate gear
 */
class Derailleur {
public:
    int get_gear ( unsigned long c_t, unsigned long w_t );
    void set_gear ( Servo motor, int gear, long int c_t, long int w_t, float K );
};

