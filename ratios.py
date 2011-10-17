#!/usr/bin/env python2
# -*- coding: utf-8 -*-

# ratios.py - Interactive script to calculate gear time/teeth ratios
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

import os
os.system("clear")

print "Calculate Gear Ratios with Specificied Tolerance:\n"
gears = int(raw_input("Number of gears: "))
tol = float(raw_input("Percentage of tolerance: "))
crown = int(raw_input("Number of teeth in front gear: "))
min = float(crown*(1-tol/100))
max = float(crown*(1+tol/100))
l=[]
l1=[]
l2=[]

for i in range(gears):
	j = int(raw_input("Number of teeth in sprocket %d: " % int(i+1) ) )
	l.append(j)

for i in l:
	l1.append(min/i)
	l2.append(max/i)

if tol != 0:
	print "\nRatios range:"
	for i in range(0,gears):
		print "%sst sprocket:" % int(i+1)
		print "(ratio > %s ) && (ratio < %s)\n" % (l1[i], l2[i])
else:
	print "\nRatios vector:"
	for i in l1:
		print round(i,4)

print "\nDON'T FORGET TO APPLY CHANGES TO C++ CODE!"
