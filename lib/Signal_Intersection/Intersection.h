#include <Arduino.h>
#include "TrafficSignal.h"
using namespace std;

// intersection class:
// assume an intersection contains (has-a) traffic signals
// and can contain buttons, buzzers, cameras, whatever
class Intersection {
    // create an intersection with one signal
    // real life application (metered highway entry e.g. I-270, I-66)
    Intersection();
    // create an intersection with two signals
    Intersection(TrafficSignal signalOne, TrafficSignal signalTwo);
    // create an intersection with three signals
    Intersection();

};