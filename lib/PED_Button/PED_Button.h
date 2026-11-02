#ifndef PED_BUTTON
#define PED_BUTTON

#include <Arduino.h>
using namespace std;

// a traffic signal has-a button (composition)
// traffic signal changes phases after button is pushed
// provided the minimum time (of the phase) has passed

class PED_Button {

    public:
        PED_Button(int buttonPin);

    private:
        unsigned long m_buttonPressedAt = 0;
        bool m_isPressed = false;

};

#endif