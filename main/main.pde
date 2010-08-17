/*
 * Main.pde - Main file to control a bicycle derailleur
 * Version 0.1
 *
 * This is file is part of a my final graduation work.
 * This code is intended to be used with an arduino to
 * automatically control gear changes of a commom
 * bicycle derailleur.
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

#include <LiquidCrystal.h>
#include <BikeTransmission.h>
#include <Servo.h>


// Objects instatiation
Servo motor;
Derailleur trocador;
LiquidCrystal lcd ( 7, 6, 5, 4, 1, 0 );
RearWheel roda ( 0.65 );
//FrontGear pedivela;

// Constants
const int b0Pin = 11; // K-
const int b1Pin = 12; // K+
const int r0Pin = 3; //Roda
const int r1Pin = 2; //Cadencia
const int pwmPin = 9;
const unsigned int CADENCE_MIN = 2000; // MIN SPEED = MAX TIME

// Variables
unsigned int marcha, wspeed, state=1;
float K=1.00;

// Interrupt used variables
volatile boolean w=false;
volatile boolean c=false;
volatile unsigned long ctime=0;
volatile unsigned long wtime=0;
volatile unsigned long ctimeLog[2];
volatile unsigned long wtimeLog[2];




void setup() {
    //Serial.begin ( 9600 );
    lcd.begin ( 16,2 ); lcd.print( "start up..." );
    delay(2000); lcd.clear(); lcd.print ( "Vel:" );
    lcd.setCursor ( 8,0 ); lcd.print ( "kmph" );
    lcd.setCursor ( 0,1 ); lcd.print ( "Marcha:" );
    lcd.setCursor ( 10,1 ); lcd.print ( "K:" );
    //lcd.setCursor ( 14,0 );
    //lcd.print ( "S" );
    motor.attach ( pwmPin );
    pinMode ( b0Pin, INPUT );
    pinMode ( b1Pin, INPUT );
    pinMode ( r0Pin, INPUT );
    pinMode ( r1Pin, INPUT );
    attachInterrupt ( 1, wheel_monitor, FALLING );
    attachInterrupt ( 0, cadence_monitor, FALLING );
}

void update_lcd() {
    lcd.setCursor ( 4,0 );
    lcd.print("    ");
    lcd.setCursor ( 4,0 );
    lcd.print ( wspeed );
    lcd.setCursor ( 7,1 );
    lcd.print ( marcha );
    lcd.setCursor ( 12,1 );
    lcd.print ( K );
}

void update_serial() {
    Serial.print ( "Velocidade: " ); Serial.print ( wspeed );
    Serial.print ("kmph"); Serial.println ( " " );
    Serial.print ( "Marcha: " ); Serial.print ( marcha ); Serial.println ( " " );
    Serial.print ( "Tempo roda: " ); Serial.print ( wtime );
    Serial.print ( " ms" ); Serial.println ( " " );
    Serial.print ( "Tempo cadencia: " ); Serial.print ( ctime );
    Serial.print ( " ms" ); Serial.println ( " " );
    Serial.print (K); Serial.println ( " " );
    Serial.print (state); Serial.println ( " " );
    Serial.println ( " " );
}

void loop() {
    switch ( state ) {
    case 1:
        update_lcd();
        //update_serial();
        state++;
        break;
    case 2:      
        if (( ctime > CADENCE_MIN ) || ( ctime == 0)) {
            state = 1;
        } else {
            state++;
        }
        break;
    case 3:
        //noInterrupts();
        marcha=trocador.get_gear ( ctime, wtime );
        trocador.set_gear ( motor, marcha, ctime, wtime, K );
        //interrupts();
        state=1;
        break;
    }

    //wspeed = roda.get_lspeed ( wtime );
    wspeed = int( (3.6*3.1416*0.65)/(wtime*0.001) );
    if ( digitalRead ( b1Pin ) == HIGH ) {
        //Serial.print ( "B1" );
        //Serial.println ( " " );
        K=K+0.01;
        if ( K >= 1.5 ) {
            K = 1.5;
        }
    }
    if ( digitalRead ( b0Pin ) == HIGH ) {
        //Serial.print ( "B0" );
        //Serial.println ( " " );
        K=K-0.01;
        if ( K <= 0.5 ) {
            K = 0.5;
        }
    }
    delay ( 500 );

}

void wheel_monitor() {
    if ( w == false ) {
        wtimeLog[0] = millis();
        w=true;
    }
    else {
        wtimeLog[1] = millis();
        wtime = wtimeLog[1] - wtimeLog[0];
        wtimeLog[0] = wtimeLog[1];
    }
}

void cadence_monitor() {
    if ( c == false ) {
        ctimeLog[0] = millis();
        c=true;
    }
    else {
        ctimeLog[1] = millis();
        ctime = ctimeLog[1] - ctimeLog[0];
        ctimeLog[0] = ctimeLog[1];
    }
}
