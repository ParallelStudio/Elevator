
# Elevator

4 elevator cars with composed stereo sound.

## Sensors:

* Floor passing sensor
* Door opening sensor

## Hardware:

* http://www.ontrak.net/ADU208.htm

Elevators

Two Signals From Each Car…

FULL SIGNAL
0:00 Full signal triggered and Voice announcement triggered “Floor 1"
0:05 Doors begin opening
0:06 Doors Finish opening
0:11 Doors Close 

SHORT SIGNAL

0:00 Doors begin opening and Short Signal Triggered
0:01 Doors Finish opening
0:06 Doors Close 

Rules

Signals
-When Full Signal is triggered the entire envelope will fire
-When Short Signal is triggered the truncated envelope will fire (truncate first 5 seconds)

Soundfiles

Bass 
* triggers every time

LowMids  
* triggers every time

highMids_(1-4) 
* play each one in numbered sequence over and over again so that the four files are triggered sequentially

highs (1-3) 
* play each one in numbered sequence over and over again so that the three files are triggered sequentially

Plucks (1-2)
* play randomly and intersperse with not playing any plucks on some triggers (trigger one of the pluck sound every other or every third time)
