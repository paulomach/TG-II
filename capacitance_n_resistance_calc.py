#!/usr/bin/env python
# -*- coding: utf-8 -*-

# capacitence_n_resistance_calc.py - Interactive script to calculate
# values to a low pass passive filter
# Version 0.1
#
# This is file is part of a my final graduation work.
# This code is intended to be used with an arduino to
# automatically control gear changes of a commom
# bycicle derailleur.
#
# Author: Paulo S. Machado
# Date: April 2010
#
# Release under de GNU Public License v3.0 or greater
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation; either
# version 3.0 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

from decimal import *
import os
os.system("clear")

print "Capacitor and/or Resistor value to reach cutoff frequency"
print "in a simple RC low pass filter. Choose:"

print "1 - Capacitor (resistence input value)"
print "2 - Resistor (capacitance input value)"

i = int(raw_input("Choice [1/2]: "))

if i in [1,2]:
	if i == 1:
		fc = float(raw_input("Cutoff frequency[Hz]: "))
		r = float(raw_input("Resistance [ohm]: "))
		
		print "You need a", Decimal(str(1/(2*3.1416*fc*r))).to_eng_string() ,"F capacitor"
	else:
		fc = float(raw_input("Cutoff frequency[Hz]: "))
		c = float(raw_input("Capacitance [F]: "))
		print "You need a", Decimal(str(1/(2*3.1416*fc*c))).to_eng_string() ,"ohm resistor"
else:
	print "Invalid option", i, ". Exiting...\n"

