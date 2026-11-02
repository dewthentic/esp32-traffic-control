#ifndef TRAFFIC_SIGNAL
#define TRAFFIC_SIGNAL

#include <Arduino.h>
using namespace std;

class TrafficSignal {

    public:
        // TrafficSignal constructor:
        // pass the pin numbers in on object creation
        TrafficSignal(int r, int y, int g);
        // TrafficSignal overloaded constructor
        // pass pin numbers AND interval time in advance
        TrafficSignal(int r, int y, int g, int r_time, int y_time, int g_time);

        // # arduino-compatible setup and loop
        void Initialize(); // equivalent to setup() in arduino
        void Update(); // equivalent to loop() in arduino

        // # pins
        // void SetRedPin(int redPin);
        // void SetYellowPin(int yellowPin);
        // void SetGreenPin(int greenPin);
        // int GetRedPin();
        // int GetYellowPin();
        // int GetGreenPin();

        // # intervals
        void RedInterval();
        void YellowInterval();
        void GreenInterval();
        

    private:
        // we're using unsigned variables because we can't (and shouldn't) count negative time
        // # esp32 gpio pin management
        unsigned int PIN_RED;
        unsigned int PIN_YELLOW;
        unsigned int PIN_GREEN;

        // # signal interval time
            // time is measured in milliseconds
            // (1000ms = 1 second)
        unsigned int RED_INT_TIME;
        unsigned int YELLOW_INT_TIME;
        unsigned int GREEN_INT_TIME;

        // used for fallback flashing 
        // (red or yellow depending on primary signal bool)
        int FLASH_INT_TIME = 500;
        unsigned long m_flashStartedAt = 0;

        // # timestamp tracking
        // think of it like a stopwatch with laps
        unsigned long m_redStartedAt = 0;
        unsigned long m_yellowStartedAt = 0;
        unsigned long m_greenStartedAt = 0;

        // # signal identifiers
        int m_currentPhase;
        bool m_invalidFallback;
        bool IS_PRIM_SIGNAL;

};

#endif

