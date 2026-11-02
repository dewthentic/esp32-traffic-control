#ifndef TRAFFIC_SIGNAL
#define TRAFFIC_SIGNAL

#include <Arduino.h>
using namespace std;

class TrafficSignal {

    public:
        // TrafficSignal constructor:
        // pass the pin numbers in on object creation
        TrafficSignal(int r, int y, int g); 

        void begin(); // equivalent to setup() in arduino
        void update(); // equivalent to loop() in arduino

        // pins
        void SetRedPin(int redPin);
        void SetYellowPin(int yellowPin);
        void SetGreenPin(int greenPin);

        

    private:
        int PIN_RED;
        int PIN_YELLOW;
        int PIN_GREEN;

        int currentPhase;
        bool invalidFallback;

};

#endif

