#include <Arduino.h>
#include "Intersection.h"

/*
# THINGS TO KNOW #

> assume the signal already exists
    // traffic signal class already defines pins and behavior
    // intersection class is responsible for managing the behavior

> trafficsignal class counts on its own time, 
we need to copy that counting to the intersection class
either by an additional mode the traffic lights can use
i.e. individually controlled vs intersection mode

safety wise this could work for temporary traffic control 
(e.g. road work, emergencies), but it sucks if it isn't protected
there's a reason why physical switches exist and can be preferred over digital logic

tl;dr part of the code we want already exists in the trafficsignal class
so we'll phase out the traffic signal millis timing there and bring it
into here.

replace the traffic signal phase changing with individual phase changes
(e.g. trafficsignal.turnred();)


*/

Intersection::Intersection(TrafficSignal signalOne, TrafficSignal signalTwo) {
    
}