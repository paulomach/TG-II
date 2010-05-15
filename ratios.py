#!/usr/bin/env python
# -*- coding: utf-8 -*-


print "Calculate gear limits with specific tolerance"
gears = int(raw_input("Number of gears: "))
tol = float(raw_input("Percentage of tolerance: "))
crown = int(raw_input("Number of teeth in front gear: "))

l=[]
for i in range(gears):
	j = int(raw_input("Number of teeth in sprocket %d: " % int(i+1) ) )
	l.append(j)

 
l1=[]
l2=[]
min = float(crown*(1-tol/100))
max = float(crown*(1+tol/100))
for i in l:
	l1.append(min/i)
	l2.append(max/i)

print "Low limits: "
print l1
print "High limits: "
print l2

