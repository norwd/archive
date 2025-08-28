#!/usr/bin/python
# encoding: utf-8
# du-diff - Disk Usage Differentiator
# LICENSE
# Copyright (C) 2006 Lluís Batlle i Rossell
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

import sys,string

if len(sys.argv) != 3:
	print "usage: " + sys.argv[0] + " <file1> <file2>"
	sys.exit()


du_first =  open(sys.argv[1],"r")
du_second = open (sys.argv[2],"r")

usage_first= {}

for line in du_first:
	elements = line.rstrip().split("\t",1)
	usage_first[elements[1]] = int(elements[0])

du_first.close()


usage_second = usage_first
for line in du_second:
	elements = line.rstrip().split("\t",1)
	elements[0] = int(elements[0])
	if usage_first.has_key(elements[1]):
		if usage_first[elements[1]] > elements[0]:
			print "-\t%d\t%d\t%s" % ( usage_first[elements[1]] - elements[0],elements[0], elements[1] )
		elif usage_first[elements[1]] < elements[0]:
			print "+\t%d\t%d\t%s" % ( elements[0] - usage_first[elements[1]], elements[0], elements[1] )

		del usage_second[elements[1]]
	else:
			print "N+\t%d\t%d\t%s" % ( elements[0] , elements[0] ,elements[1] )

du_second.close()
for key in usage_second.keys():
			print "D+\t%d\t%d\t%s" % ( usage_second[key] , 0, key )

