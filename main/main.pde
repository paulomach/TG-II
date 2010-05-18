/* 
 * Main.pde
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

#include <LiquidCrystal.h>
#include <BikeTransmission.h>
#include <Servo.h>


// Objects instatiation
Servo motor;
derailleur dera;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
rear_wheel roda(0.26);
front_gear pedivela;

// Constants


// Variables
long int wheel_speed, cadencia;
int marcha, speed;
float K=1.00;
int buttonstate = 0;

void setup() {
	motor.attach(9);
	lcd.begin(16,2);
	lcd.print("Vel:");
	lcd.setCursor(7,0);
	lcd.print("kmph");
	lcd.setCursor(0,1);
	lcd.print("Marcha: ");
        pinMode(1, INPUT);
}


void loop() {
	wheel_speed = roda.read_wspeed_sensor();
	cadencia = pedivela.read_cadence_sensor();
	marcha = dera.get_gear(cadencia, wheel_speed);
	dera.set_gear(motor, marcha, cadencia, wheel_speed, K);
	
	// Linear speed. To show in display
	speed = roda.get_lspeed();
	lcd.setCursor(5,0);
	lcd.print(speed);
	
	lcd.setCursor(8,1);
	lcd.print(marcha);

        buttonstate = digitalRead(1);
        if (buttonstate == HIGH) {
          K=K+0.001;
          if ( K >= 1.5 ) {K = 1.5;}
        }
        
        lcd.setCursor(11,1);
        lcd.print("K:");
        lcd.setCursor(13,1);
        lcd.print(K);
}


