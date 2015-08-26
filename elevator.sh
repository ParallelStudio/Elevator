#!/bin/bash
#
# pd startup script for the elevator project
#

PD=`which pd`
if [ "" == "${PD}" ] ; then
	echo Cannot find pd in the path.
	exit 1
fi

MYDIR=`dirname $0`
PDDIR=${MYDIR}/pd
ABS=${PDDIR}/abs
SOUNDS=${MYDIR}/sounds
EXT=/usr/local/lib/pd-externals
PDMICRO=${MYDIR}/microserver-pd
PDEXT=${EXT}/osc:${EXT}/net

# TODO: Customize the commandline here
${PD} -verbose \
	-lib zexy \
	-font-face "Lucida Console" -font-size 10 -font-weight normal \
	-path ${PDDIR} \
	-path ${ABS} \
	-path ${SOUNDS} \
	-path ${EXT} \
	-path ${PDEXT} \
	-path ${PDMICRO} \
	-send "pd dsp 1" \
	$@
