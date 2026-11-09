#ifndef PED_BUZZER
#define PED_BUZZER

#include <Arduino.h>
using namespace std;

// a traffic signal has-a buzzer (composition)
// buzzer is intended to ping when a light is green
// after the button is pushed

class PED_Buzzer {

    public:
        PED_Buzzer();
        // PED_Buzzer(int buzzerPin);
        void Initialize();
        void Update();
        void ChangeState(int state);
        void TriggerPing(); // one beep per second
        void TriggerBurst(int amt); // 8-10 beeps per second with pause

    private:
        // state and mode tracking
        enum BuzzerState {OFF, BURST, COUNTDOWN, IDLE};
        BuzzerState m_currentState = OFF;

        // timing variables
        unsigned long m_burstStartedAt = 0; // tracks timestamp when entire burst started
        unsigned long m_buzzerStartedAt = 0; // tracks timestamp when one ping started
        unsigned long m_nextEventTime = 0; // absolute deadline (millis() + interval) for when the next ping or burst plays
        unsigned long m_pulseOffTime = 0; // absolute time when an active beep (HIGH) must stop (LOW)

        // configuration (constants)
        const int BURST_INTERVAL = 111; // time in ms between burst pings (~9 pings per second)
        const int COUNT_INTERVAL = 1000; // time in ms between one second beeps (1 ping per second)
        const int PULSE_DURATION = 40; // time in ms the buzzer stays active (beeping)
        
        const int MAX_BURSTS = 3; // customizable number of bursts for each signal (take into account intersection size)
        const int BURST_PAUSE_INT = 500; // delay time (low) after one burst wave finishes
        const int BURST_ACTIVE_INT = 1000; // total time an active burst should take

        // configuration (variables)
        unsigned long m_burstTimer = 0; // true = rapid ticks, false = silent pause
        int m_burstCycleCt = 0; // counts completed bursts (resettable)
        int m_isBurstActive = false; // tracks active window or pause time
        // int m_accessibilityMode = true;
        int m_countdownTime = 0; // used for ping and burst
        int PIN_BUZZER; // buzzer pin

        // private helper functions
        void BurstHandler();
        void PingHandler();

        
};

#endif