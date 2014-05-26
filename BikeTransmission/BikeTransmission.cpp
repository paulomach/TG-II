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
const float validratios[TOTAL_GEARS]={1.0769, 1.2174, 1.4, 1.6471, 1.8667, 2.1538};

// Time limits (milliseconds)

const int CADENCE_MIN=1600;
/// 90RPM - 667ms
const int CADENCE_MAX=667;

// Offset in the derailleur moviment to engage next gear
const float UP_OFFSET=0.9;
const float DOWN_OFFSET=1.1;

/********* Constructors implementation ************/
RearWheel::RearWheel ( float _diameter ) {
    this->diameter = _diameter;
}


/*********** Methods implementation **************/


/**
 * Linear wheel speed calculated with: \n
 * \f$V = \omega r = 2\pi fr \f$\n
 * \f$V = \frac{\pi*D}{T} [m/ms] \f$\n
 * \f$V = \frac{3.6*1000*\pi*D}{T} [km/h] \f$
 */
int RearWheel::get_lspeed ( unsigned long T ) {
    int lspeed;
    // condition to speed less than 1km/h
    if ( ( T > 7350 ) || ( T == 0 ) ) return 0;
    lspeed = round( (1000*3.6*3.1416*(this->diameter))/T );
    return( lspeed );
}

/**
 * Return true if param is within
 * tolerance [%] of reference:
 */
boolean closeto2(float param, float reference, float tolerance) {
    return (( param >= (reference*(1.00-tolerance)) ) &&
      ( param <= (reference*(1.00+tolerance)) ));
}

/**
 * Return the current gear based on known
 * gear ratios and revoltion times. \n
 * TODO: Discover why this dont work
 *      inside the library
 */
int Derailleur::get_gear ( unsigned long c_t, unsigned long w_t ) {
    float ratio;
    ratio=float(c_t)/w_t;
    for (int i=0;i<TOTAL_GEARS;i++) {
        if (closeto2(ratio,validratios[i],TOLERANCE)) {
            return(i+1);
        }
    }
}

/*
 * Class core method. Choose whatever the gear should be changed. 
 */
void Derailleur::set_gear ( Servo motor, int gear, long int c_t, long int w_t, float K ) {
    int cur_position = motor.read();
    int target_positon = round(STEP*gear);
    // make sure that derailleur is at expected position
    if (cur_position != target_positon) {
        motor.write(target_positon);
    }
    else {
        if ( ( c_t > CADENCE_MIN*K ) && ( gear != GEAR_MIN ) ) {
            // Hold position a little lower for a little time
            motor.write (round( STEP* ( gear - 1 ) *UP_OFFSET ));
            Serial.println("Mais torque!");
            delay(700);
            // and then leave in best position
            motor.write ( STEP* ( gear - 1 ) );
        } else if ( ( c_t < CADENCE_MAX*K ) && ( gear != GEAR_MAX ) ) {
            // Hold position a little higher for a little time
            motor.write (round( STEP* ( gear + 1 ) *DOWN_OFFSET ));
            Serial.println("Mais velocidade...");
            delay(700);
            // and then leave in best position
            motor.write ( STEP* ( gear + 1 ) );
        }
    }
}
