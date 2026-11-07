#ifndef PED_BUTTON
#define PED_BUTTON

#include <Arduino.h>
using namespace std;

// a traffic signal has-a button (composition)
// traffic signal changes phases after button is pushed
// provided the minimum time (of the phase) has passed

// adapted from https://esp32io.com/tutorials/esp32-button into a class

class PED_Button {

    public:
        PED_Button(int buttonPin);
        void Initialize();
        void Update();

    private:
        int PIN_BUTTON;
        const int DEBOUNCE_TIME = 50; // time to wait after a button press (in ms)
        // unsigned long m_buttonPressedAt = 0; // millis()
        unsigned long m_lastDebounceTime = 0; // the last time the output pin was toggled
        
        // tracking button state without micro oscillation effect
        int m_lastSteadyState = 0;
        int m_lastFlickerState = 0;
        int m_currentState = 0;

        int m_amtPressed = 0; // used for the WAIT

};

#endif