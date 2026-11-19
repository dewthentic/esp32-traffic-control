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
TrafficSignal signalTwo(15, 4, 5, false, 15000, 5000, 30000);

void setup() {
    // settings must be initialized during setup
    signalOne.SetCurrentPhase(5); // anything <=0 or >=2 will trigger flashing fallback
    signalTwo.SetCurrentPhase(4); // not yet ready (one buzzer on two signals is not good)
    signalOne.Initialize();
    signalTwo.Initialize();
}

void loop() {
    signalOne.Update();
    signalTwo.Update();
}