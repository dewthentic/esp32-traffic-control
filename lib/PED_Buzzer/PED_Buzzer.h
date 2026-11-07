#ifndef PED_BUZZER
#define PED_BUZZER

#include <Arduino.h>
using namespace std;

// a traffic signal has-a buzzer (composition)
// buzzer is intended to ping when a light is green
// after the button is pushed

class PED_Buzzer {

    public:
        PED_Buzzer(int buzzerPin);
        void Initialize();
        void Update();
        void TriggerPing(); // one beep per second
        void TriggerBurst(); // 8-10 beeps per second with pause

    private:
        // state and mode tracking
        enum BuzzerState {OFF, BURST, COUNTDOWN, AUTO};
        BuzzerState m_currentState = OFF;

        // timing variables
        unsigned long m_nextEventTime = 0; // absolute deadline (millis() + interval) for when the next ping or burst plays
        unsigned long m_pulseOffTime = 0; // absolute time when an active beep (HIGH) must stop (LOW)

        // constants (configuration)
        const int BURST_INTERVAL = 111; // time in ms between burst pings (~9 pings per second)
        const int COUNT_INTERVAL = 1000; // time in ms between one second beeps (1 ping per second)
        const int PULSE_DURATION = 40; // time in ms the buzzer stays active (beeping)

        // private helper functions
        void BurstHandler();
        void CountHandler();

        unsigned long m_buzzerTriggeredAt = 0;
        int m_isBuzzing = false;
        int PIN_BUZZER; // buzzer pin
};

#endif