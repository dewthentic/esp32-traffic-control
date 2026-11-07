#include "PED_Button.h"
#include <Arduino.h>
using namespace std;

// adapted from https://esp32io.com/tutorials/esp32-button-debounce

PED_Button::PED_Button(int buttonPin) {
    PIN_BUTTON = buttonPin;
}

void PED_Button::Initialize() {
    Serial.begin(9600); // initialize serial at 9600 bits per second?
    
    // init push button pin as a pullup input
    // input pin will be HIGH (1) when switch is open 
    // low (0) when switch is closed
    pinMode(PIN_BUTTON, INPUT_PULLUP); // define button input
}

void PED_Button::Update() {
    // read the state of the button
    m_currentState = digitalRead(PIN_BUTTON);

    // check to see if button was just pressed (by you)
    // e.g. input went from low to high and debounce passed
    // debounce = wait period to prevent spam. in this case, flickering states

    if (m_currentState != m_lastFlickerState) {
        // the button is pressed, reset the debounce timer
        m_lastDebounceTime = millis();
        // save the last flicker state
        m_lastFlickerState = m_currentState;
    }

    if ((millis() - m_lastDebounceTime) > DEBOUNCE_TIME) {
        // if the current time - last timestamp from debounce surpasses the wait requirement
        // take it as the current state

        // if button state changed
        if (m_lastSteadyState == HIGH and m_currentState == LOW) {
            // the button was pressed
            // execute code here (check traffic signal time and change the phase)
            // perhaps pass something into the update function?
        } else if (m_lastSteadyState == LOW and m_currentState == HIGH) {
            // the button was released
            // optional: execute code here too, or let it pass
        }

        // save the last steady state
        m_lastSteadyState = m_currentState;
    }


}