/* 
 * BikeTransmission.h - Bycicle Modeling Classes for Arduino
 * Version 0.1
 *
 * This is file is part of a my final graduation work.
 * This code is intended to be used with an arduino to 
 * automatically control gear changes of a commom 
 * bycicle derrailleur.
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


/********* Classes (models of fisical entities) *************/

class front_gear {
	int speed;							// could be the time per revolution (1)
	bool state;							// spinning or not
	public:
		front_gear();					// class constructor
		int read_speed_sensor();		// function to read from sensor
		bool get_state()
};

class rear_gear {
	bool state;							// gear engadged or desengadged
	int size;							// which gear I'am
	public:
		rear_gear();					// class constructor
		int get_state();
		void set_state();
};

class rear_wheel {
	int speed;							// idem comment (1)
	public:
		rear_wheel();					// class constructor
		int get_speed();
};

class derailleur {
	int gear;
	public:
		derailleur(int slots);			// class constructor - # of gears
		int get_gear();
		void set_gear(int pos);
};

