/*
 * BikeTransmission.cpp - Bicycle Modeling Classes for Arduino
 * Version 0.1
 *
 * This is file is part of a my final graduation work.
 * This code is intended to be used with an arduino to
 * automatically control gear changes of a commom
 * bicycle Derailleur.
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
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */



#include "BikeTransmission.h"
#include <Servo.h>
#include <WProgram.h>
#include <math.h>

const int GEAR_MAX=6;
const int GEAR_MIN=1;
const int TOTAL_PATH=180;
const int TOTAL_GEARS=6;
const int STEP=TOTAL_PATH/TOTAL_GEARS;
const int TOLERANCE=0.05;
const float validratios[TOTAL_GEARS]={ 1.6428, 1.9166, 2.2999, 2.5555, 2.875, 3.2857 };

// Time limits (milliseconds)
// 30RPM - 2000ms
const int CADENCE_MIN=3000;
// 90RPM - 667ms
const int CADENCE_MAX=100;

// Offset in the derailleur moviment to engage next gear
const float UP_OFFSET=1.3;
const float DOWN_OFFSET=1.3;

/*
 * Debounce time for reed switch.
 * This approach limits wheel speed
 * to V = pi*D*3.6*1000/T (T stands for
 * period in milliseconds
 */ 
const int DEBOUNCE=70;// 84 kmph


/*
 * Time variables for speed reading:
 * c_t - cadence time
 * w_t - wheel time
 */
unsigned long c_t1, c_t2, w_t1, w_t2;



/********* Constructors implementation ************/
RearWheel::RearWheel ( float _diameter ) {
    this->diameter = _diameter;
}


/*********** Methods implementation **************/


/*
 * Linear wheel speed:
 * V = w*r -> V = 2*pi*f*r
 * V = pi*D/T [m/ms]
 * V = (3.6*1000*pi*D)/T [km/h]
 */
int RearWheel::get_lspeed ( unsigned long T ) {
    int lspeed;
    // condition to speed less than 1km/h
    if ( ( T > 7350 ) || ( T == 0 ) ) return 0;
    lspeed = round( (1000*3.6*3.1416*(this->diameter))/T );
    return( lspeed );
}

/*
 * Return true if param is within
 * tolerance [%] of reference:
 */
boolean closeto2(float param, float reference, float tolerance) {
    return (( param >= (reference*(1.00-tolerance)) ) &&
      ( param <= (reference*(1.00+tolerance)) ));
}

int Derailleur::get_gear ( unsigned long c_t, unsigned long w_t ) {
    float ratio;

    // * Find out the right relations
    // * [beyond TG] configurable ratios
    ratio=float(c_t)/w_t;
    Serial.println(ratio);
    for (int i=0;i<TOTAL_GEARS;i++) {
        if (closeto2(ratio,validratios[i],TOLERANCE)) {
            return(i+1);
        }
    }
}

/*
 * Core method of the library. responsable
 * for choosing and setting a new gear
 * position
 */
void Derailleur::set_gear ( Servo motor, int gear, long int c_t, long int w_t, float K ) {
    if ( ( c_t < CADENCE_MIN*K ) && ( gear != GEAR_MIN ) ) {
        motor.write (int( STEP* ( gear + 1 ) *UP_OFFSET ));
        //while ( gear == this->get_gear ( c_t, w_t ) ) {
        //Serial.print("Subindo marcha...");
        delay(1000);
        //}
        motor.write ( STEP* ( gear + 1 ) );
    } else if ( ( c_t > CADENCE_MAX*K ) && ( gear != GEAR_MAX ) ) {
        motor.write (int( STEP* ( gear - 1 ) *DOWN_OFFSET ));
        //while ( gear == this->get_gear ( c_t, w_t ) ) {
          //Serial.print("Descendo marcha...");
        delay(1000);
        //}
        motor.write ( STEP* ( gear - 1 ) );
    }
}
