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
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
RearWheel roda(0.52);
FrontGear pedivela;

// Constants
const int b0Pin = 6;
const int b1Pin = 7;
const int r0Pin = 8;
const int r1Pin = 10;
const int pwmPin = 9;
const int CADENCE_MIN = 2000;

// Variables
int marcha, wspeed, state=1;
float K=1.00;
unsigned long c_t, w_t;

void setup() {
	lcd.begin(16,2);
	lcd.print("Vel:");
	lcd.setCursor(7,0);
	lcd.print("kmph");
	lcd.setCursor(0,1);
	lcd.print("Marcha:");
        lcd.setCursor(11,1);
        lcd.print("K:");
        motor.attach(pwmPin);
	pinMode(b0Pin, INPUT);
	pinMode(b1Pin, INPUT);
	pinMode(r0Pin, INPUT);
	pinMode(r1Pin, INPUT);
}

void update_lcd(){
        lcd.setCursor(5,0);
	lcd.print(wspeed);
	lcd.setCursor(8,1);
	lcd.print(marcha);
        lcd.setCursor(13,1);
        lcd.print(K);
}

void loop() {
  
        switch(state){
          case 1:
            update_lcd();
            state++;
            break;
          case 2:
            w_t = roda.read_wspeed_sensor(r1Pin);
            c_t = pedivela.read_cadence_sensor(r0Pin);
            if (c_t > CADENCE_MIN) {
               state = 1;
            }
            else { state++; }
            break;
          case 3:
            marcha=trocador.get_gear(c_t, w_t);
            trocador.set_gear(motor, marcha, c_t, w_t, K);
            state=1;
            break;
        }


	wspeed = roda.get_lspeed();	
        if (digitalRead(b1Pin) == HIGH) {
          K=K+0.001;
          if ( K >= 1.5 ) {K = 1.5;}
        }        
        if (digitalRead(b0Pin) == HIGH) {
          K=K-0.001;
          if ( K <= 0.5 ) {K = 0.5;}
        }
        
}


