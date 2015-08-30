#!/bin/bash
#
# Given a list of files, generate a simple pd patch containing 
# tables with the same filenames (minus extension).
# This does not yet support filenames with spaces.
#
# Use it like this:
#
# $ table_patch.sh sounds/*.wav > my_tables_abs.pd
#

list=""
for f in $@ ; do
	f=`basename $f .wav`
	list="$f $list"
done

echo '#N canvas 637 404 776 670 10;'
echo '#X text 26 2 generated file \, do not edit!;'
echo '#X obj 279 20 inlet;'
echo "#X msg 279 52 list $list;"
echo '#X obj 279 300 outlet;'
echo '#X connect 2 0 3 0;'
echo '#X connect 1 0 2 0;'

y=22
for f in $@ ; do
	f=`basename $f .wav`
	echo "#X obj 26 $y table $f;"
	y=$((y+20))
done

