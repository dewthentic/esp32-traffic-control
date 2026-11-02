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
        void TriggerPulse(); // one beep per second
        void TriggerBurst(); // 8-10 beeps per second with pause

    private:
        unsigned long m_buzzerTriggeredAt = 0;
        int m_isBuzzing = false;

};

#endif