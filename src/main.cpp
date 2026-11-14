// cpp version
// includes traffic light core class
// for previous versions prior to github look in the /archive/ folder

#include <Arduino.h>
#include <TrafficSignal.h>
using namespace std;

/* ideal setup */
// we don't use int main/return 0 in here because it loops repeatedly

// you MUST declare objects outside the typical setup/loop functions for persistance
TrafficSignal signalOne(14, 27, 26, true, 15000, 5000, 30000);

void setup() {
    // settings must be initialized during setup
    signalOne.SetCurrentPhase(2); // anything <=0 or >=2 will trigger flashing fallback
    signalOne.Initialize();
}

void loop() {
    signalOne.Update();
}