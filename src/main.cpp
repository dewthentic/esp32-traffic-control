// cpp version
// includes traffic light core class
// for previous versions prior to github look in the /archive/ folder

#include <Arduino.h>
#include <TrafficSignal.h>
using namespace std;

// you MUST declare objects outside the typical setup/loop functions for persistance
TrafficSignal signalOne(18, 21, 22);

void setup() {
    signalOne.Initialize();
}

void loop() {
    signalOne.Update();
}
