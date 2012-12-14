/*
 * Main.pde - Main file to control a bicycle derailleur
 * Version 0.1
 *
 * This is file is part of a my final graduation work.
 * This code is intended to be used with an arduino to
 * automatically control gear changes of a commom
 * bicycle derailleur.
 *
 * Variables prefixed with "w" are referenced to wheel
 * Variables prefixed with "c" are referenced to the cadence
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

#include <LiquidCrystal.h>
#include <BikeTransmission.h>
#include <Servo.h>



// Objects instatiation
Servo motor;
Derailleur trocador;
// lcd(RS,ENABLE,D4,D5,D6,D7)
LiquidCrystal lcd ( 7, 6, 5, 4, 8, 10 );
RearWheel roda ( 0.65 );  

// Constants
const int b0Pin = 11;   // K-
const int b1Pin = 12;   // K+
const int r0Pin = 3;    // Wheel
const int r1Pin = 2;    // Cadence
const int pwmPin = 9;   // PWM pin
const unsigned int CADENCE_MIN = 3000;  // MIN SPEED = MAX TIME coasting
const unsigned long RESET_TIMEOUT = 3000; // Timeout for reset timers
const int debugLevel = 2; // Set debug verbosity in serial

const int TOTAL_GEARS=6;
const int TOLERANCE=5;
const float validratios[TOTAL_GEARS]={1.0769, 1.2174, 1.4, 1.6471, 1.8667, 2.1538};

// Variables
unsigned int wspeed, state=1;
int gear=6;
float K=1.00;

float ratio;

// Interrupt used variables
volatile boolean w=false;
volatile boolean c=false;
volatile unsigned long ctime=0;
volatile unsigned long wtime=0;
volatile unsigned long ctimeLog[2];
volatile unsigned long wtimeLog[2];

/*
 * General pins and startup routine
 */
void setup() {
  Serial.begin ( 9600 );
  lcd.begin ( 16,2 ); 
  lcd.print( "start up..." );
  delay(2000); 
  lcd.clear(); 
  lcd.print ( "Vel:" );
  lcd.setCursor ( 8,0 ); 
  lcd.print ( "kmph" );
  lcd.setCursor ( 0,1 ); 
  lcd.print ( "Marcha:" );
  lcd.setCursor ( 10,1 ); 
  lcd.print ( "K:" );
  motor.attach ( pwmPin );
  pinMode ( b0Pin, INPUT );
  pinMode ( b1Pin, INPUT );
  pinMode ( r0Pin, INPUT );
  pinMode ( r1Pin, INPUT );
  attachInterrupt ( 1, wheel_monitor, FALLING );
  attachInterrupt ( 0, cadence_monitor, FALLING );
}

/*
 * Display refresh routine
 */
void update_lcd() {
  lcd.setCursor ( 4,0 );
  lcd.print("    ");
  lcd.setCursor ( 4,0 );
  lcd.print ( wspeed );
  lcd.setCursor ( 7,1 );
  lcd.print ( gear );
  lcd.setCursor ( 12,1 );
  lcd.print ( K );
}

/*
 * Serial debug output routine
 */
void update_serial() {
  if (debugLevel == 2) {
    Serial.print ( "Velocidade: " );    Serial.print ( wspeed ); Serial.println (" kmph");
    Serial.print ( "Marcha: " );        Serial.println ( gear );
    Serial.print ( "Tempo roda: " );    Serial.print ( wtime ); Serial.println ( " ms" );
    Serial.print ( "Tempo cadencia: " );Serial.print ( ctime ); Serial.println ( " ms" );
    Serial.print ("K: ");               Serial.println (K);     Serial.println ("");
  }
}

/*
 * Main loop
 */
void loop() {
  ratio=float(ctime)/wtime;
  for (int i=0;i<6;i++) {
      if (closeto(ratio,validratios[i],TOLERANCE)) {
          gear = i+1;
      }
  }
  
  // check if coasting
  if (( ctime < CADENCE_MIN ) && ( ctime != 0)) {
    // if not act over transmission
    trocador.set_gear ( motor, gear, ctime, wtime, K );
  }
  /*
   * Refresh displays
   */ 
  wspeed = roda.get_lspeed ( wtime );
  update_lcd();
  update_serial();
  /*
   * Button 1 read, k++
   */
  if ( digitalRead ( b1Pin ) == HIGH ) {
    K=K+0.01;
    if ( K >= 1.5 ) {
      K = 1.5;
    }
  }
  /*
   * Button 0 read, k--
   */
  if ( digitalRead ( b0Pin ) == HIGH ) {
    K=K-0.01;
    if ( K <= 0.5 ) {
      K = 0.5;
    }
  }
  delay ( 600 );
  reset_timers();
}

/*
 * wheel time interrupt
 * routine
 */
void wheel_monitor() {
  // first time log
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

/*
 * cadence time interrupt
 * routine
 */
void cadence_monitor() {
  // first time log
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

/*
 * timers reset routine
 */
void reset_timers() {
  unsigned long now = millis();
  if (now - wtimeLog[0] > RESET_TIMEOUT) {
    wtime = 0;
  }
  if (now - ctimeLog[0] > RESET_TIMEOUT) {
    ctime = 0;
  }
}

/*
 * Return true if param is within
 * tolerance [%] of reference:
 */
boolean closeto(float param, float reference, float tolerance) {
    return ( (param >= (reference*(100-tolerance)/100) ) &&
      (param <= (reference*(100+tolerance)/100) ) );
}

