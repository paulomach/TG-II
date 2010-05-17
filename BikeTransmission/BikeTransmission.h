/* 
 * BikeTransmission.h - Bycicle Modeling Classes for Arduino
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


#ifndef BikeTransmission_h
#define BikeTransmission_h

#endif

/********* Classes (models of fisical entities) *************/

class front_gear {
	public:
		bool state;				// spinning or not
		long int read_cadence_sensor();		// function to read from sensor
		bool get_state();
		int _size;
};



class rear_wheel {					// doens't need a class constructor
	public:
		float diameter;				// wheel diameter
		rear_wheel(float _diameter);
		long int read_wspeed_sensor();
};

class derailleur {
	public:
		int get_gear(long int fs, long int rs);
		void set_gear(Servo motor, int gear, long int fs, float K);
};

